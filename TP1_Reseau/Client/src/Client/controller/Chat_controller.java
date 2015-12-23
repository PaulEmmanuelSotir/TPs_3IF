package Client.controller;

import shared.IChatDAL;
import javafx.event.ActionEvent;
import javafx.scene.control.Label;
import javafx.scene.text.Text;
import javafx.fxml.FXML;

public class Chat_controller {
	
	public void setDAL(IChatDAL dal) {
		m_dal = dal;
	}
	
    @FXML protected void SendMessage_action(ActionEvent event) {
        SendMessage_Text.setText("Sign in button pressed");
        SendMessage_Label.setText("Yo !!");
    }
    
    @FXML private Text SendMessage_Text;
    @FXML private Label SendMessage_Label;
    
    private IChatDAL m_dal;
}
