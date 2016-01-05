package Server;

import shared.AppendingObjectOutputStream;
import shared.Group;
import shared.Message;
import shared.User;

import java.io.*;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.function.Consumer;
import java.util.Map;

/**
 * Data acess layer permettant le stoquage et le chargement de l'état du serveur grâce à la serialisation des objets du model vers des
 * fichiers binaires (liste des utilisateurs, liste des groupes et liste des messages associés à leur groupes respectifs).
 * Cette classe assume que les informations données en paramètre sont correctes (les validations sont assumées par
 * ClientConnexion et Server). Par exemple, pour append message, on assume que le groupe a déjà été crée.
 */
public class StorageDAL {
    public StorageDAL(String history_directory, Consumer<Exception> error_callback) {
        m_error_callback = error_callback;
        m_history_dir = history_directory;
    }

    /**
     * Obtient une map associant à chaque groupe sa liste de message
     * @return Une map associant à chaque groupe sa liste de message (liste vide si aucun messages)
     */
    public Map<Group, List<Message>> GetStoredGroups() {
        HashMap<Group, List<Message>> result = new HashMap<>();

        // Open files and create Object streams
        ObjectInputStream group_ios = null, messages_ios = null;
        try {
            FileInputStream group_fin = new FileInputStream(m_history_dir + "groups");
            FileInputStream messages_fin = new FileInputStream(m_history_dir + "messages");

            group_ios = new ObjectInputStream(group_fin);
            messages_ios = new ObjectInputStream(messages_fin);
        }
        catch(FileNotFoundException e) { return null; }
        catch(IOException e) {
            try {
                if(group_ios != null)
                    group_ios.close();
                if(messages_ios != null)
                    messages_ios.close();
            } catch (IOException ex) { }
            if(m_error_callback != null)
                m_error_callback.accept(e);
            return null;
        }

        // Read groups file until end of file (EOFException)
        try {
            while(true) {
                Object obj = group_ios.readObject();
                if(obj instanceof Group)
                    result.put((Group)obj, new ArrayList<>());
            }
        }
        catch(IOException|ClassNotFoundException e) { }

        // Read messages file until end of file (EOFException)
        try {
            while(true) {
                Object obj = messages_ios.readObject();
                if(obj instanceof MessageWithGroup) {
                    MessageWithGroup message = (MessageWithGroup)obj;
                    List<Message> group_messages = result.get(message.group);
                    if(group_messages != null)
                        group_messages.add(message.message);
                }
            }
        }
        catch(IOException|ClassNotFoundException e) { }
        finally {
            try {
                if(group_ios != null)
                    group_ios.close();
                if(messages_ios != null)
                    messages_ios.close();
            } catch (IOException e) { }
        }

        return result;
    }

    /**
     * Obtient la liste des utilisateurs stockée dans le fichier binaire correspondant
     * @return La liste des utilisateurs stockée
     */
    public List<User> GetStoredUsers() {
        List<User> users = new ArrayList<>();

        // Open files and create Object streams
        ObjectInputStream users_ios = null;
        try {
            FileInputStream users_fin = new FileInputStream(m_history_dir + "users");
            users_ios = new ObjectInputStream(users_fin);
        }
        catch(FileNotFoundException e) { return null; }
        catch(IOException e) {
            try {
                if(users_ios != null)
                    users_ios.close();
            } catch (IOException ex) { }
            if(m_error_callback != null)
                m_error_callback.accept(e);
            return null;
        }

        // Read users file until end of file (EOFException)
        try {
            while(true) {
                Object obj = users_ios.readObject();
                if(obj instanceof User)
                    users.add((User)obj);
            }
        }
        catch(IOException|ClassNotFoundException e) { }
        finally {
            try {
                if(users_ios != null)
                    users_ios.close();
            } catch (IOException e) { }
        }

        return users;
    }

    /**
     * Initialise les stream permettant l'écriture vers les fichiers binaires stoquant l'état du serveur.
     * Si les fichiers existent déjà, des AppendingObjectOutputStream sont crées.
     */
    public void InitStorageWriting() {
        boolean appending_to_users = new File(m_history_dir + "users").exists();
        boolean appending_to_groups = new File(m_history_dir + "groups").exists();
        boolean appending_to_messages = new File(m_history_dir + "messages").exists();
        try {
            m_users_fout = new FileOutputStream(m_history_dir + "users", true);
            m_group_fout = new FileOutputStream(m_history_dir + "groups", true);
            m_messages_fout = new FileOutputStream(m_history_dir + "messages", true);
        } catch(FileNotFoundException e) {
            if(m_error_callback != null)
                m_error_callback.accept(e);
        }

        try {
            if(appending_to_users)
                m_users_oos = new AppendingObjectOutputStream(m_users_fout);
            else
                m_users_oos = new ObjectOutputStream(m_users_fout);

            if(appending_to_groups)
                m_group_oos = new AppendingObjectOutputStream(m_group_fout);
            else
                m_group_oos = new ObjectOutputStream(m_group_fout);

            if(appending_to_messages)
                m_messages_oos = new AppendingObjectOutputStream(m_messages_fout);
            else
                m_messages_oos = new ObjectOutputStream(m_messages_fout);
        } catch(IOException e) {
            if(m_error_callback != null)
                m_error_callback.accept(e);
        }
    }

    /**
     * Ajoute un message au fichier stoquant les messages
     * @param message Message à enregister
     */
    public void AppendMessage(Group group, Message message) {
        SerializeObject(new MessageWithGroup(group, message), m_messages_oos);
    }

    /**
     * Ajoute un groupe au fichier stoquant les groupes
     * @param group Groupe à enregister
     */
    public void AppendGroup(Group group) {
        SerializeObject(group, m_group_oos);
    }

    /**
     * Ajoute un utilisateur au fichier stoquant les utilisateurs
     * @param user Utilisateur à enregister
     */
    public void AppendUser(User user) {
        SerializeObject(user, m_users_oos);
    }

    public void CloseStorage() {
        try {
            if (m_group_oos != null)
                m_group_oos.flush();
            if(m_group_fout != null)
                m_group_fout.close();
            if (m_group_oos != null)
                m_group_oos.close();

            if (m_users_oos != null)
                m_users_oos.flush();
            if(m_users_fout != null)
                m_users_fout.close();
            if (m_users_oos != null)
                m_users_oos.close();

            if (m_messages_oos != null)
                m_messages_oos.flush();
            if(m_messages_fout != null)
                m_messages_fout.close();
            if (m_messages_oos != null)
                m_messages_oos.close();
        } catch (IOException e) {
            if(m_error_callback != null)
                m_error_callback.accept(e);
        }

        m_group_fout = null;
        m_users_fout = null;
        m_messages_fout = null;
        m_group_oos = null;
        m_users_oos = null;
        m_messages_oos = null;
        m_error_callback = null;
    }

    @Override
    public void finalize() throws Throwable {
        super.finalize();
        CloseStorage();
    }

    private void SerializeObject(Object obj, ObjectOutputStream stream) {
        if(stream != null) {
            try {
                stream.writeObject(obj);
            } catch (IOException e) {
                if (m_error_callback != null)
                    m_error_callback.accept(e);
            }
        }
    }

    private FileOutputStream m_group_fout;
    private ObjectOutputStream m_group_oos;

    private FileOutputStream m_users_fout;
    private ObjectOutputStream m_users_oos;

    private FileOutputStream m_messages_fout;
    private ObjectOutputStream m_messages_oos;

    private Consumer<Exception> m_error_callback;
    private String m_history_dir;

    /**
     * Classe permettant d'associer un message à son groupe lors de la serialisation
     */
    static class MessageWithGroup implements Serializable {
        MessageWithGroup(Group group, Message message) {
            this.group = group;
            this.message = message;
        }

        public Message message;
        public Group group;

        @Override
        public boolean equals(Object other) {
            if(other instanceof MessageWithGroup) {
                MessageWithGroup mess = (MessageWithGroup)other;
                if(message == null) {
                    if (mess.message != null)
                        return false;
                }
                else if(!message.equals(mess.message))
                    return false;

                if(group == null) {
                    if (mess.group != null)
                        return false;
                }
                else if(!group.equals(mess.group))
                    return false;
                return true;
            }
            return false;
        }
    }
}
