package Client.controller;

import Client.Navigator;
import javafx.application.Platform;
import javafx.fxml.FXML;
import Client.Socket_DAL;
import javafx.event.ActionEvent;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.stage.Popup;

public class Login_controller {
    public void init(Navigator nav, Socket_DAL dal) {
        m_navigator = nav;

        if(dal == null) {
            m_dal = new Socket_DAL("localhost", 1001, (Exception e) -> {
                // TODO: show popup with connection retry
            });

            m_dal.open();
            m_dal.start();
        }
        else {
            m_dal = dal;
        }
    }

    @FXML protected void FocusOnPasswordTextField(ActionEvent event) {
        //TODO: focus on password text field
    }

    @FXML protected void  SubmitCredentials(ActionEvent event) {
        String password = PasswordTextField.getText();
        String username = UsernameTextField.getText();

        if(!username.equals("") && !password.equals(""))
            ErrorMessageLabel.setVisible(false);

            m_dal.SubmitCredentials(username, password, user -> {
                Platform.runLater(() -> {
                    if(user != null) {
                        // Goto Groups_view
                        ErrorMessageLabel.setVisible(false);
                        m_dal.setErrorCallback(null);
                        m_navigator.showGroupsPage(m_dal, user);
                    }
                    else
                        // Show error message
                        ErrorMessageLabel.setVisible(true);
                });
            });
    }

    @FXML protected void  CreateNewAccount(ActionEvent event) {
        m_dal.setErrorCallback(null);
        m_navigator.showNewAccountPage(m_dal);
    }

    @FXML protected TextField UsernameTextField;
    @FXML protected TextField PasswordTextField;
    @FXML protected Label ErrorMessageLabel;

    private Navigator m_navigator = null;
    private Socket_DAL m_dal;
}
