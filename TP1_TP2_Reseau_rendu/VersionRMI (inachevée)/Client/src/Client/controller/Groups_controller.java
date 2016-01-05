package Client.controller;

import Client.Navigator;
import Client.RMI_DAL;
import javafx.application.Platform;
import javafx.beans.value.ObservableValue;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;

import javafx.scene.control.ListView;
import javafx.scene.control.TextField;
import javafx.scene.layout.Priority;
import javafx.scene.layout.VBox;
import shared.*;

import java.util.HashSet;
import java.util.Set;

/**
 * Controlleur correspondant à la vue Groups_view.fxml.
 * Cette classe utilise le DAL pour obtenir la liste des groupe, créer des groupes et en rejoindre.
 * Ce controlleur écoute également les notifications du DAL mettant à jour la liste des groupes.
 */
public class Groups_controller {

    /**
     * Fournit le DAL qui sera utilisé par le controlleur pour comuniquer avec le serveur.
     * @param dal Le DAL que le controlleur utilisera pour comuniquer avec le serveur
     */
	public void setDAL(RMI_DAL dal) {
		m_dal = dal;
        m_groups = new HashSet<>();

        dal.GetGroups((Group[] groups) -> {
            if(groups != null) {
                // TODO: customize ListView to display groups instead of strings
                Platform.runLater(() -> {
                    for (Group group : groups) {
                        if (m_groups.add(group))
                            m_groups_names.add(group.groupName);
                    }
                });
            }
        });

        dal.setGroupListUpdateCallback(group -> {
            if (m_groups.add(group))
                Platform.runLater(() -> m_groups_names.add(group.groupName));
        });

        ListView<String> GroupsListView = new ListView<>();
        GroupsListView.setItems(m_groups_names);
        GroupsListView.setPrefHeight(405);
        GroupsListView.setPrefWidth(720);
        GroupsListView.getSelectionModel().selectedItemProperty().addListener((ObservableValue<? extends String> ov, String old_val, String new_val) -> {
            for (Group group : m_groups) {
                if(group.groupName.equals(new_val))
                    JoinGroup(group);
            }
        });

        Platform.runLater(() -> {
            GroupsListViewParent.getChildren().add(0, GroupsListView);
            GroupsListViewParent.setVgrow(GroupsListView, Priority.ALWAYS);
        });
	}

    /**
     * Fournit le navigator au controlleur
     * @param nav L'objet de type Navigator permettant de naviger facilement d'une vue à l'autre
     */
    public void setNavigator(Navigator nav) { m_navigator = nav; }

    /**
     * Fournit l'identité de l'utilisateur connecté au controlleur
     * @param user L'objet de type User représentant l'utilisateur (pseudo et mots de passe)
     */
    public void setUser(User user) {
        m_user = user;
    }

    /**
     * Méthode permettant à l'utilisateur de rejoindre un groupe.
     * Navigue vers la vue Chat_view si l'utilisateur a réussit a rejoindre le groupe (réponse du serveur appelant une callback).
     * Cette méthode est appelée lorsque l'utilisateur clique sur un groupe de la liste (ListView) des groupes/rooms.
     * @param group L'objet de type Group représentant le groupe que l'utilisateur veux rejoindre
     */
    @FXML protected void JoinGroup(Group group) {
        m_dal.JoinGroup(m_user, group, (Group cb_group, Pair<String[], Message[]> group_data) -> {
            Platform.runLater(() -> {
                if(cb_group != null) {
                    m_dal.setGroupListUpdateCallback(null);
                    m_navigator.showChatPage(m_dal, m_user, group, group_data.first, group_data.second);
                }
                else {
                    // TODO: show error message or logout
                }
            });
        });
    }

    /**
     * Méthode permettant à l'utilisateur de créer un groupe.
     * Navigue vers la vue Chat_view dans le groupe crée si le groupe a put être crée (réponse du serveur appelant une callback).
     * Cette méthode est appelée lorsque l'utilisateur clique sur le boutton 'Create group' et récupère le nom du groupe depuis le TextBox correspondant.
     */
    @FXML protected void CreateGroup(ActionEvent event) {
       String group_name = GroupNameTextField.getText();
       if(m_user != null && m_dal != null && group_name != null)
           if(!group_name.equals(""))
               m_dal.CreateGroup(m_user, group_name, group -> {
                   Platform.runLater(() -> {
                       if(group != null) {
                           String[] usernames = {m_user.Name};
                           m_dal.setGroupListUpdateCallback(null);
                           m_navigator.showChatPage(m_dal, m_user, group, usernames, null);
                       }
                       //else
                           // TODO: show error message
                    });
               });
    }

    @FXML protected VBox GroupsListViewParent;
    @FXML protected TextField GroupNameTextField;

    private ObservableList<String> m_groups_names = FXCollections.observableArrayList(); // TODO : ObservableList<Group> et customiser la listView
    private Set<Group> m_groups;

    private Navigator m_navigator = null;
    private RMI_DAL m_dal = null;
    private User m_user = null;
}
