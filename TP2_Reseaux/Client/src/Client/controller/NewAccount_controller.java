package Client.controller;

import Client.Navigator;
import javafx.application.Platform;
import javafx.fxml.FXML;
import Client.Socket_DAL;
import javafx.event.ActionEvent;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.scene.layout.HBox;

import java.util.HashSet;
import java.util.concurrent.RunnableFuture;

public class NewAccount_controller {
	public void setDAL(Socket_DAL dal) { m_dal = dal; }
    public void setNavigator(Navigator nav) { m_navigator = nav; }

    @FXML protected void SubmitUsername(ActionEvent event) {
        String username = UsernameTextField.getText();

        if(!username.equals("")) {
            ErrorMessageLabel.setVisible(false);
            GeneratedPasswordMessageLabel.setVisible(false);
            GeneratedPasswordTextArea.setVisible(false);

            m_dal.CreateUserName(username, user -> {
                Platform.runLater(() -> {
                    if (user != null)
                    {
                        // Show generated password (and ok button)
                        UsernameTextField.setDisable(true);
                        SumbitButtons.setVisible(false);
                        OkButton.setVisible(true);
                        ErrorMessageLabel.setVisible(false);
                        GeneratedPasswordMessageLabel.setVisible(true);
                        GeneratedPasswordTextArea.setText(user.Id.toString());
                        GeneratedPasswordTextArea.setVisible(true);
                    }
                    else
                    {
                        // Show error message
                        UsernameTextField.setDisable(false);
                        OkButton.setVisible(false);
                        GeneratedPasswordMessageLabel.setVisible(false);
                        GeneratedPasswordTextArea.setVisible(false);
                        SumbitButtons.setVisible(true);
                        ErrorMessageLabel.setVisible(true);
                    }
                });
            });
        }
    }

    @FXML protected void GoBack(ActionEvent event) {
        m_navigator.showLoginPage(m_dal);
    }

    @FXML protected TextField UsernameTextField;
    @FXML protected Label GeneratedPasswordMessageLabel;
    @FXML protected TextArea GeneratedPasswordTextArea;
    @FXML protected Label ErrorMessageLabel;
    @FXML protected Button OkButton;
    @FXML protected HBox SumbitButtons;

    private Navigator m_navigator = null;
    private Socket_DAL m_dal;
}
