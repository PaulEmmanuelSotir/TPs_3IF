package Client;

import Client.controller.Chat_controller;
import Client.controller.Groups_controller;
import Client.controller.Login_controller;
import Client.controller.NewAccount_controller;
import javafx.fxml.FXMLLoader;
import java.io.IOException;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;
import shared.Group;
import shared.Message;
import shared.User;

public class Navigator {
    Navigator(Stage primaryStage) {
        m_primaryStage = primaryStage;
    }

    public Stage getPrimaryStage() { return m_primaryStage; }

    public void showLoginPage(RMI_DAL dal) {
        if(dal != null)
            m_dal = dal;
        try {
            // Load view
            FXMLLoader loader = new FXMLLoader();
            loader.setLocation(Main.class.getResource("../Client/view/login_view.fxml"));
            Parent content = (Parent)loader.load();

            // Set controller parameters
            Login_controller controller = loader.getController();
            controller.init(this, dal);

            // Create new scene and show it
            changeScene(content);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void showNewAccountPage(RMI_DAL dal) {
        if(dal != null)
            m_dal = dal;
        try {
            // Load view
            FXMLLoader loader = new FXMLLoader();
            loader.setLocation(Main.class.getResource("../Client/view/newAccount_view.fxml"));
            Parent content = (Parent)loader.load();

            // Set controller parameters
            NewAccount_controller controller = loader.getController();
            controller.setDAL(dal);
            controller.setNavigator(this);

            // Create new scene and show it
            changeScene(content);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void showGroupsPage(RMI_DAL dal, User user) {
        if(dal != null)
            m_dal = dal;
        try {
            // Load view
            FXMLLoader loader = new FXMLLoader();
            loader.setLocation(Main.class.getResource("../Client/view/groups_view.fxml"));
            Parent content = (Parent)loader.load();

            // Set controller parameters
            Groups_controller controller = loader.getController();
            controller.setDAL(dal);
            controller.setUser(user);
            controller.setNavigator(this);

            // Create new scene and show it
            changeScene(content);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void showChatPage(RMI_DAL dal, User user, Group group, String[] usernames, Message[] message_history) {
        if(dal != null)
            m_dal = dal;
        try {
            // Load view
            FXMLLoader loader = new FXMLLoader();
            loader.setLocation(Main.class.getResource("../Client/view/chat_view.fxml"));
            Parent content = (Parent)loader.load();

            // Set controller parameters
            Chat_controller controller = loader.getController();
            controller.setDAL(dal);
            controller.setUser(user);
            controller.setGroup(group);
            controller.setNavigator(this);
            controller.setGroupUsers(usernames);
            controller.setMessages(message_history);

            // Create new scene and show it
            changeScene(content);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void disposeDAL() {
        if(m_dal != null)
            m_dal.dispose();
    }

    private void changeScene(Parent content) {
        if(m_primaryStage != null) {
            m_primaryStage.setTitle("Chat app");
            m_primaryStage.setMinWidth(720);
            m_primaryStage.setMinHeight(405);
            m_primaryStage.setScene(new Scene(content, 864, 486));
            m_primaryStage.show();
        }
    }

    private Stage m_primaryStage;
    private RMI_DAL m_dal = null;
}
