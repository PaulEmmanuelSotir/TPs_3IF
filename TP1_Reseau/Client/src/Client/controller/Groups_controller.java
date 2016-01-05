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

public class Groups_controller {

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
    public void setNavigator(Navigator nav) { m_navigator = nav; }

    public void setUser(User user) {
        m_user = user;
    }

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
