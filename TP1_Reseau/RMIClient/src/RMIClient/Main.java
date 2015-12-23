package RMIClient;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;
import Client.controller.Chat_controller;
import RMIClient.RMI_DAL;

public class Main extends Application {
	@Override
	public void start(Stage primaryStage) throws Exception {
		FXMLLoader loader = new FXMLLoader(getClass().getResource("../Client/view/chat_view.fxml"));
		Parent root = (Parent)loader.load();
        primaryStage.setTitle("Chat app");
        primaryStage.setScene(new Scene(root, 300, 275));
        
		RMI_DAL chatDAL = new RMI_DAL((Exception e) -> {
			// TODO: show error message and/or goto main connection page ?
		});
        
        Chat_controller controller = loader.<Chat_controller>getController();
       	controller.setDAL(chatDAL);
        
        primaryStage.show();
        
        // TODO: faire une vue pour la connexion et tout et tout...
     //   chatDAL.Connect("localhost");
	}
	
	static void main(String[] args)
	{
		launch(args);
	}
}
