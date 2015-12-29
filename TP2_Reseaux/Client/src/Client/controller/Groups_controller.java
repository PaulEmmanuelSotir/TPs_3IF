package Client.controller;

import Client.Socket_DAL;
import shared.*;

public class Groups_controller {

	public void setDAL(Socket_DAL dal) {
		m_dal = dal;
        dal.GetGroups((Group[] groups) -> m_groups = groups);
	}

    public void setUser(User user) {
        m_user = user;
    }

    private Socket_DAL m_dal;
    private User m_user;
    private Group[] m_groups;
}
