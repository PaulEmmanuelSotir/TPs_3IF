package Client;

import javafx.application.Application;
import javafx.stage.Stage;

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

	private Navigator m_page_navigator;

	public static void main(String[] args)
	{
		launch(args);
	}
}
