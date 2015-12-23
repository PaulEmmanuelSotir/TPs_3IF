package shared;

import java.rmi.Remote;
import java.rmi.RemoteException;

public interface IServerReception extends Remote {
	
	void receiveMessage (Message message ) throws RemoteException;
	
}
