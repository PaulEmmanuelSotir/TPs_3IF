package Client;

import java.rmi.RemoteException;
import java.util.function.BiConsumer;
import java.util.function.Consumer;

import shared.*;

/**
 * Data access layer donnat accès au serveur gèrant le chat.
 * Gère les appels des méthodes distantes (chaqune des RMI est executée dans son propre thread
 * pour évititer tout appel bloquant et permettre des notofocations des controlleurs asynchrones).
 * PAS FINIS
 */
public class RMI_DAL implements IRemoteClientDAL {

	public RMI_DAL(String host_name, Consumer<Exception> connection_error_callback) {
		reset_callbacks();
		m_error_callback = connection_error_callback;
		m_host_name = host_name;
	}

	public void open() {

	}

	@Override
	public void finalize() throws Throwable {
		super.finalize();
		dispose();
	}

	/**
	 * Modifie la callback appelée si un message est recu
	 * @param message_callback Callback appelée si un message est recu
	 */
	public void setMessageCallback(Consumer<Message> message_callback) { m_message_callback = message_callback; }

	/**
	 * Modifie la callback appelée si une erreur se produit
	 * @param connection_error_callback Callback appelée si une erreur se produit
	 */
	public void setErrorCallback(Consumer<Exception> connection_error_callback) { m_error_callback = connection_error_callback; }

	/**
	 * Modifie la callback appelée si un groupe est crée (permet de mettre à jour la vue affichant la liste des groupes)
	 * @param group_list_update_callback Callback appelée si un groupe est crée
	 */
	public void setGroupListUpdateCallback(Consumer<Group> group_list_update_callback) { m_group_list_update_callback = group_list_update_callback; }

	/**
	 * Modifie la callback appelée si un utilisateur quitte ou rejoint le groupe dans lequel l'utilisateur est présent (permet de mettre à jour la vue affichant la liste des utilisateur du groupe)
	 * @param group_user_list_update_callback Callback appelée si un utilisateur quitte ou rejoint le groupe dans lequel l'utilisateur est présent
	 */
	public void setGroupUserListCallback(BiConsumer<Boolean, String> group_user_list_update_callback) { m_group_user_list_update_callback = group_user_list_update_callback; }

	public void CreateGroup(User user, String name, Consumer<Group> group_callback) {

	}

	public void JoinGroup(User user, Group group, BiConsumer<Group, Pair<String[], Message[]>> group_join_callback) {

	}

	public void QuitGroup(User user, Group group, Consumer<Boolean> group_quit_callback) {

	}

	public void GetGroups(Consumer<Group[]> group_list_callback) {

	}

	public void SendMessage(Message message) {

	}

	/**
	 * Essaye de créer un nouveau compte avec le nom d'utilisateur donné en paramètre.
	 * La callback spécifiée sera appellée avec null en paramètre si l'utilisateur n'a
	 * pas pu être crée et avec l'objet User correspondant à l'utilisateur si la création a réussie.
	 * @param name Nom du nouvel utilisateur
	 * @param username_callback Callback appelée lors de la réponse du serveur
	 */
	public void CreateUserName(String name, Consumer<User> username_callback) {
		// TODO Auto-generated method stub
	}


	public void SubmitCredentials(String username, String password, Consumer<User> login_callback) {

	}

	public void Logout() {

	}

	public void dispose() {

	}

	// IRemoteClientDAL ...

	@Override
	public void OnUserLoggedIn(User user) throws RemoteException {

	}

	@Override
	public void OnGroupCreated(Group group) throws RemoteException {

	}

	@Override
	public void OnGroupJoined(Group group, String[] usernames, Message[] history) throws RemoteException {

	}

	@Override
	public void OnGroupExit(Boolean success) throws RemoteException {

	}

	@Override
	public void OnSendGroupList(Group[] groups) throws RemoteException {

	}

	@Override
	public void OnSendMessage(Message message) throws RemoteException {

	}

	@Override
	public void OnUserCreated(User user) throws RemoteException {

	}

	@Override
	public void OnGroupListUpdated(Group new_group) throws RemoteException {

	}

	@Override
	public void OnGroupUserListUpdated(Boolean is_joining, String new_username) throws RemoteException {

	}

	private void reset_callbacks() {
		m_group_creation_callback = null;
		m_group_join_callback = null;
		m_group_quit_callback = null;
		m_group_list_callback = null;
		m_username_callback = null;
		m_login_callback = null;

		m_sending_request = false;
	}

	private Consumer<Exception> m_error_callback = null;
	private Consumer<Message> m_message_callback = null;
	private BiConsumer<Boolean, String> m_group_user_list_update_callback = null;
	private Consumer<Group> m_group_list_update_callback = null;

	private Consumer<Group> m_group_creation_callback;
	private BiConsumer<Group, Pair<String[], Message[]>> m_group_join_callback;
	private Consumer<Boolean> m_group_quit_callback;
	private Consumer<Group[]> m_group_list_callback;
	private Consumer<User> m_username_callback;
	private Consumer<User> m_login_callback;

	private boolean m_sending_request;

	private String m_host_name;
}
