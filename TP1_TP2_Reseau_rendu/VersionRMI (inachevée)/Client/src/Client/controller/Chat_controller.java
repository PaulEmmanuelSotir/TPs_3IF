package Client.controller;

import java.util.Date;
import java.util.TreeMap;

import Client.RMI_DAL;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.event.ActionEvent;
import javafx.application.Platform;
import javafx.scene.control.*;
import javafx.collections.FXCollections;

import Client.Navigator;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Priority;
import javafx.scene.layout.VBox;
import javafx.scene.text.Font;
import shared.*;

/**
 * Controlleur correspondant à la vue Chat_view.fxml.
 * Cette classe utilise le DAL pour envoyer et recevoir des messages.
 * Ce controlleur écoute également les notifications du DAL mettant à jour la liste des utilisateurs du groupe.
 */
public class Chat_controller {

    public Chat_controller() {
        ListView<Message> MessagesListView = new ListView<>();
        MessagesListView.setItems(m_messages);
        MessagesListView.setCellFactory((ListView<Message> l) -> new MessageListViewCell());

        Platform.runLater(() -> {
            MessagesListViewParent.getChildren().add(0, MessagesListView);
            MessagesListViewParent.setVgrow(MessagesListView, Priority.ALWAYS);
        });
    }

    /**
     * Fournit le DAL qui sera utilisé par le controlleur pour comuniquer avec le serveur
     * @param dal Le DAL que le controlleur utilisera pour comuniquer avec le serveur
     */
	public void setDAL(RMI_DAL dal) {
        m_dal = dal;
        m_dal.setMessageCallback((message -> {
            Platform.runLater(() -> {
                m_messages.add(message);
            });
        }));
        m_dal.setGroupUserListCallback( (is_joining, new_username) -> {
            Platform.runLater(() -> {
                if(!is_joining)
                    m_group_users.remove(new_username);
                else if (!m_group_users.contains(new_username))
                    m_group_users.add(new_username);

            });
        });
    }

    /**
     * Fournit l'identité de l'utilisateur connecté au controlleur
     * @param user L'objet de type User représentant l'utilisateur (pseudo et mots de passe)
     */
    public void setUser(User user) { m_user = user; }

    /**
     * Fournit le groupe dans le quel l'utilisateur se trouve au controlleur
     * @param group L'objet de type Group représentant le groupe dans le quel l'utilisateur se trouve
     */
    public void setGroup(Group group) { m_group = group; }

    /**
     * Fournit le navigator au controlleur
     * @param nav L'objet de type Navigator permettant de naviger facilement d'une vue à l'autre
     */
    public void setNavigator(Navigator nav) { m_navigator = nav; }

    /**
     * Fournit les noms d'utilisateurs présents dans le groupe au controlleur
     * @param usernames Les noms d'utilisateurs sous forme de tableau de String
     */
    public void setGroupUsers(String[] usernames) {
        m_group_users.clear();
        m_group_users.addAll(usernames);

        Platform.runLater(() -> {
            UsersListView.setItems(m_group_users);
        });
    }

    /**
     * Fournit l'historique des messages du groupe au controller
     * @param history L'historique des messages sous forme de tableau de Message
     */
    public void setMessages(Message[] history) {
        if(history != null)
            m_messages.addAll(history);
    }

    /**
     * Méthode appelée pour envoyer un message au groupe.
     * Cette méthode est appellée lorsque l'utilisateur appuie sur le boutton 'Send' ou sur la touche Entrer dans la TextBox du message.
     */
    @FXML protected void SendMessage(ActionEvent event) {
        String text = MessageTextField.getText();
        if (text.length() > 0)
            m_dal.SendMessage(new Message(MessageTextField.getText(), new Date(), m_user.Name));
        MessageTextField.clear();
    }

    /**
     * Méthode appelée pour quitter le groupe et retourner à la vue des groupes (liste des groupes).
     * Cette méthode est appellée lorsque l'utilisateur appuie sur le boutton 'Quit group'.
     */
    @FXML protected void QuitGroup(ActionEvent event) {
        m_dal.QuitGroup(m_user, m_group, success -> {
            Platform.runLater(() -> {
                if (success) {
                    m_dal.setMessageCallback(null);
                    m_dal.setGroupUserListCallback(null);
                    m_navigator.showGroupsPage(m_dal, m_user);
                }
                //else
                // TODO: can't quit group ?! -> disconnect and goto login page ?
            });
        });
    }

    @FXML protected TextField MessageTextField;
    @FXML protected VBox MessagesListViewParent;
    @FXML protected ListView UsersListView;

    private Navigator m_navigator = null;
    private RMI_DAL m_dal;
    private User m_user;
    private Group m_group;
    private ObservableList<Message> m_messages = FXCollections.observableArrayList(); // TODO: sort messages by date to prevent bad message order when simultaneous sending occurs ??
    private ObservableList<String> m_group_users = FXCollections.observableArrayList();

    /**
     * Classe permettant de personnaliser l'affichage des cellules de la ListView contenant les messages
     */
    static class MessageListViewCell extends ListCell<Message> {
        /**
         * Méthode appelée pour mettre à jour (afficher) la cellule de la ListView à partir d'un message.
         * @param item Message à afficher dans la cellule
         */
        @Override
        public void updateItem(Message item, boolean empty) {
            super.updateItem(item, empty);
            if (item != null) {
                HBox message_node = new HBox();

                Label username_label = new Label(item.userName);
                username_label.setFont(new Font("Gill Sans MT", 12));

                Label message_label = new Label(item.data);
                message_label.setFont(new Font("Gill Sans MT", 12));

                Label timestamp_label = new Label(item.timestamp.toString());
                timestamp_label.setFont(new Font("Gill Sans MT", 8));

                message_node.getChildren().add(username_label);
                message_node.getChildren().add(message_label);
                message_node.getChildren().add(timestamp_label);

                setGraphic(message_node);
            }
            else
                setGraphic(null);
        }
    }
}
