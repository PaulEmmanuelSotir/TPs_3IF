package Client.controller;

import java.util.Date;
import java.util.TreeMap;

import javafx.fxml.FXML;
import javafx.event.ActionEvent;
import javafx.scene.control.TextField;

import Client.Socket_DAL;
import shared.*;

public class Chat_controller {
	public void setDAL(Socket_DAL dal) { m_dal = dal; }
    public void setUser(User user) { m_user = user; }
    public void setGroup(Group group) { m_group = group; }

    @FXML protected  void SendMessage(ActionEvent event) {
        String text = MessageTextField.getText();
        if (text.length() > 0)
            m_dal.SendMessage(new Message(MessageTextField.getText(), new Date(), m_user.Name));
        MessageTextField.clear();
    }

    @FXML protected TextField MessageTextField;

    private Socket_DAL m_dal;
    private User m_user;
    private Group m_group;
    private TreeMap<Date, Message> m_messages; // sort messages by date to prevent bad message order when simultaneous sending occurs
}
