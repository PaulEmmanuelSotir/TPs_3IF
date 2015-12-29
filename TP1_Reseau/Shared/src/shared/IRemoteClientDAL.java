package shared;

import java.rmi.Remote;
import java.rmi.RemoteException;

/*GROUP_CREATION_ERROR,
		GROUP_CREATION_SUCCESS,
		GROUP_JOIN_ERROR,
		SEND_GROUP_LIST,
		SEND_MESSAGE,
		CREATE_USERNAME_ERROR,
		CREATE_USERNAME_SUCCESS */
		
public interface IRemoteClientDAL extends Remote {
	void receiveMessage (Message message ) throws RemoteException;
	
}
