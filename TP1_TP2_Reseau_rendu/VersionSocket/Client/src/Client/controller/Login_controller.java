package Client.controller;

import Client.Navigator;
import javafx.fxml.FXML;
import Client.Socket_DAL;
import javafx.event.ActionEvent;
import javafx.scene.control.Label;
import javafx.application.Platform;
import javafx.scene.control.TextField;

/**
 * Controlleur correspondant à la vue Login_view.fxml.
 * Cette classe utilise le DAL pour permettre à l'utilisateur de se connecter.
 * Ce controlleur vérifie, grâce au DAL, si le mots de passe ou le nom d'utilisateur est correct et déclenche l'affichage d'un message d'erreur dans ce cas.
 * Si l'utilisateur parvient a se connecter, ce controlleur navige vers la vue Groups_view et si l'utilisateur veux créer un nouveau compte, il navige vers la vue NewAccountView.
 */
public class Login_controller {

    /**
     * Fournit le DAL et le navigateur qui seront utilisés par le controlleur.
     * @param nav L'objet de type Navigator permettant de naviger facilement d'une vue à l'autre
     * @param dal Le DAL que le controlleur utilisera pour comuniquer avec le serveur
     */
    public void init(Navigator nav, Socket_DAL dal) {
        m_navigator = nav;

        if(dal == null) {
            m_dal = new Socket_DAL("localhost", 1001, (Exception e) -> {
                // TODO: show popup with connection retry
            });

            m_dal.open();
            m_dal.start();
        }
        else {
            m_dal = dal;
        }
    }

    @FXML protected void FocusOnPasswordTextField(ActionEvent event) {
        //TODO: focus on password text field
    }

    /**
     * Méthode appelée par la vue pour essayer de se connecter avec le nom d'utilisateur et le mots de passe donnés dans les TextBox correspondantes.
     * Cette méthode est appelée lorsque l'utilisateur appuie sur le boutton 'Login' ou appuie sur 'Enter' pendent que le focus est sur la TextBox du mots de passe.
     */
    @FXML protected void  SubmitCredentials(ActionEvent event) {
        String password = PasswordTextField.getText();
        String username = UsernameTextField.getText();

        if(!username.equals("") && !password.equals(""))
            ErrorMessageLabel.setVisible(false);

            m_dal.SubmitCredentials(username, password, user -> {
                Platform.runLater(() -> {
                    if(user != null) {
                        // Goto Groups_view
                        ErrorMessageLabel.setVisible(false);
                        m_dal.setErrorCallback(null);
                        m_navigator.showGroupsPage(m_dal, user);
                    }
                    else
                        // Show error message
                        ErrorMessageLabel.setVisible(true);
                });
            });
    }

    /**
     * Méthode appelée par la vue pour naviger vers la vue NewAccount_view.
     * Cette méthode est appelée lorsque l'utilisateur appuie sur le boutton 'Create new account'.
     */
    @FXML protected void  CreateNewAccount(ActionEvent event) {
        m_dal.setErrorCallback(null);
        m_navigator.showNewAccountPage(m_dal);
    }

    @FXML protected TextField UsernameTextField;
    @FXML protected TextField PasswordTextField;
    @FXML protected Label ErrorMessageLabel;

    private Navigator m_navigator = null;
    private Socket_DAL m_dal;
}
