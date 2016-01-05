package Client.controller;

import java.util.Date;
import java.util.TreeMap;

import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.event.ActionEvent;
import javafx.application.Platform;
import javafx.geometry.HPos;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.control.*;
import javafx.collections.FXCollections;

import Client.Socket_DAL;
import Client.Navigator;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Priority;
import javafx.scene.layout.VBox;
import javafx.scene.text.Font;
import javafx.scene.text.FontWeight;
import shared.*;

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

	public void setDAL(Socket_DAL dal) {
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
    public void setUser(User user) { m_user = user; }
    public void setGroup(Group group) { m_group = group; }
    public void setNavigator(Navigator nav) { m_navigator = nav; }
    public void setGroupUsers(String[] usernames) {
        m_group_users.clear();
        m_group_users.addAll(usernames);

        Platform.runLater(() -> {
            UsersListView.setItems(m_group_users);
        });
    }
    public void setMessages(Message[] history) {
        if(history != null)
            m_messages.addAll(history);
    }

    @FXML protected void SendMessage(ActionEvent event) {
        String text = MessageTextField.getText();
        if (text.length() > 0)
            m_dal.SendMessage(new Message(MessageTextField.getText(), new Date(), m_user.Name));
        MessageTextField.clear();
    }

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
    private Socket_DAL m_dal;
    private User m_user;
    private Group m_group;
    private ObservableList<Message> m_messages = FXCollections.observableArrayList(); // TODO: sort messages by date to prevent bad message order when simultaneous sending occurs ??
    private ObservableList<String> m_group_users = FXCollections.observableArrayList();

    static class MessageListViewCell extends ListCell<Message> {
        @Override
        public void updateItem(Message item, boolean empty) {
            super.updateItem(item, empty);
            if (item != null) {
                HBox message_node = new HBox();

                Label username_label = new Label(item.userName + ": ");
                username_label.setFont(Font.font("Gill Sans MT", FontWeight.EXTRA_BOLD, 12));

                Label message_label = new Label(item.data);
                message_label.setFont(new Font("Gill Sans MT", 12));

                Label timestamp_label = new Label(item.timestamp.toString());
                timestamp_label.setFont(new Font("Gill Sans MT", 9));
                timestamp_label.setAlignment(Pos.CENTER_RIGHT);

                message_node.getChildren().add(username_label);
                message_node.getChildren().add(message_label);
                message_node.getChildren().add(timestamp_label);
                message_node.setHgrow(message_label, Priority.ALWAYS);
                message_node.setMargin(timestamp_label, new Insets(6, 0, 0, 0));
                message_node.setMargin(username_label, new Insets(5, 0, 0, 0));
                message_node.setMargin(message_label, new Insets(5, 40, 0, 5));

                setGraphic(message_node);
            }
            else
                setGraphic(null);
        }
    }
}
