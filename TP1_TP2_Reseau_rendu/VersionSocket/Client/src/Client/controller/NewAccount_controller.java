package Client.controller;

import Client.Navigator;
import javafx.fxml.FXML;
import Client.Socket_DAL;
import javafx.scene.layout.HBox;
import javafx.event.ActionEvent;
import javafx.scene.control.Label;
import javafx.application.Platform;
import javafx.scene.control.Button;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;

/**
 * Controlleur correspondant à la vue NewAccount_view.fxml.
 * Cette classe utilise le DAL pour créer une nouveau compte et déclanche l'afffichage de messages d'erreur si la création du compte est impossible.
 * Si la création du compte a réussie, le controlleur déclanche l'affichage du mots de passe généré par le serveur et permet à l'utilisateur d'appuyer
 * sur un boutton 'Ok' pour retourner à la vue Login_view pour se connecter.
 */
public class NewAccount_controller {

    /**
     * Fournit le DAL qui sera utilisé par le controlleur pour comuniquer avec le serveur.
     * @param dal Le DAL que le controlleur utilisera pour comuniquer avec le serveur
     */
	public void setDAL(Socket_DAL dal) { m_dal = dal; }

    /**
     * Fournit le navigator au controlleur
     * @param nav L'objet de type Navigator permettant de naviger facilement d'une vue à l'autre
     */
    public void setNavigator(Navigator nav) { m_navigator = nav; }

    /**
     * Méthode appelée par la vue pour essayer de se créer un nouveau compte avec pour nom d'utilisateur celui spécifié dans la TextBox correspondante.
     * Cette méthode est appelée lorsque l'utilisateur appuie sur le boutton 'Create account'.
     * La méthode déclanche l'affichage d'un message d'erreur si le compte ne peut pas être crée (de manière asynchrone)
     */
    @FXML protected void SubmitUsername(ActionEvent event) {
        String username = UsernameTextField.getText();

        if(!username.equals("")) {
            ErrorMessageLabel.setVisible(false);
            GeneratedPasswordMessageLabel.setVisible(false);
            GeneratedPasswordTextArea.setVisible(false);

            m_dal.CreateUserName(username, user -> {
                Platform.runLater(() -> {
                    if (user != null)
                    {
                        // Show generated password (and ok button)
                        UsernameTextField.setDisable(true);
                        SumbitButtons.setVisible(false);
                        OkButton.setVisible(true);
                        ErrorMessageLabel.setVisible(false);
                        GeneratedPasswordMessageLabel.setVisible(true);
                        GeneratedPasswordTextArea.setText(user.Id.toString());
                        GeneratedPasswordTextArea.setVisible(true);
                    }
                    else
                    {
                        // Show error message
                        UsernameTextField.setDisable(false);
                        OkButton.setVisible(false);
                        GeneratedPasswordMessageLabel.setVisible(false);
                        GeneratedPasswordTextArea.setVisible(false);
                        SumbitButtons.setVisible(true);
                        ErrorMessageLabel.setVisible(true);
                    }
                });
            });
        }
    }

    /**
     * Méthode appelée par la vue pour naviger vers la vue 'Login_view'
     * Cette méthode est appelée lorsque l'utilisateur appuie sur le boutton 'Cancel'.
     */
    @FXML protected void GoBack(ActionEvent event) {
        m_navigator.showLoginPage(m_dal);
    }

    @FXML protected TextField UsernameTextField;
    @FXML protected Label GeneratedPasswordMessageLabel;
    @FXML protected TextArea GeneratedPasswordTextArea;
    @FXML protected Label ErrorMessageLabel;
    @FXML protected Button OkButton;
    @FXML protected HBox SumbitButtons;

    private Navigator m_navigator = null;
    private Socket_DAL m_dal;
}
