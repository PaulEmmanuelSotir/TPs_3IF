package Client;

import javafx.application.Application;
import javafx.stage.Stage;

/**
 * Classe principale de l'application client de chat.
 */
public class Main extends Application {
	@Override
	public void start(Stage primaryStage) throws Exception {
		m_page_navigator = new Navigator(primaryStage);
		m_page_navigator.showLoginPage(null);
	}

	@Override
	public void stop() {
		if(m_page_navigator != null)
			m_page_navigator.disposeDAL();
	}

	/**
	 * Méthode main, point d'entrée du programme lançant l'application
	 */
	private Navigator m_page_navigator;

	public static void main(String[] args)
	{
		launch(args);
	}
}
