package Client.controller;

import javafx.fxml.FXML;
import Client.Socket_DAL;
import javafx.event.ActionEvent;
import javafx.scene.control.TextField;

import shared.*;

public class Login_controller {
	public void setDAL(Socket_DAL dal) { m_dal = dal; }

    @FXML protected void FocusOnPasswordTextField(ActionEvent event) {

    }

    @FXML protected void  SubmitCredentials(ActionEvent event) {

    }

    @FXML protected void  CreateNewAccount(ActionEvent event) {

    }

    @FXML protected TextField UsernameTextField;
    @FXML protected TextField PasswordTextField;

    private Socket_DAL m_dal;
}
