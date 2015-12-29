package Client.controller;

import Client.Socket_DAL;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;

public class NewAccount_controller {
	public void setDAL(Socket_DAL dal) { m_dal = dal; }

    @FXML protected void  SubmitUsername(ActionEvent event) {
        // TODO: request username and display generated password if succeeded
    }

    @FXML protected void  GoBack(ActionEvent event) {
        // TODO: goto login_view
    }

    @FXML protected TextField UsernameTextField;
    @FXML protected Label GeneratedPasswordLabel;

    private Socket_DAL m_dal;
}
