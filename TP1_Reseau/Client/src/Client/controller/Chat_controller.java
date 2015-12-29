package Client.controller;

import java.util.Date;
import java.util.TreeMap;

import javafx.fxml.FXML;
import javafx.event.ActionEvent;
import javafx.scene.control.TextField;

import shared.*;

public class Chat_controller {

	public void setDAL(IChatDAL dal) {
		m_dal = dal;
        if(Main.using_socket)
            dal.GetGroups(/*TODO: give callback giving groups ((Group[] groups) -> m_groups = groups;)*/);
	}

    public void setUser(User user) {
        m_user = user;
    }

    @FXML protected  void SendMessage(ActionEvent event) {
        String text = MessageTextField.getText();
        if (text.length() > 0)
            m_dal.SendMessage(m_user, new Date(), new Message(MessageTextField.getText(), m_user.Name));
        MessageTextField.clear();
    }

    @FXML protected TextField MessageTextField;

    private IChatDAL m_dal;
    private User m_user;
    private Group[] m_groups;
    private TreeMap<Date, Message> m_messages;
    /*TODO: sort messages by date to prevent bad message order if almost simultaneous sending*/
}
