package TP1_SI.Utils;

import java.io.InputStreamReader;
import java.io.BufferedReader;
import java.util.HashMap;
import java.util.Map;

/**
 * Classe aidant à la création d'un menu sur console.
 * Un choix est ajouté au menu en fournissant un nom de l'option et une fonction à appeler
 * si cette option est choisie (class implémentant l'interface 'Callable').
 * @author B3330
 */
public class ConsoleMenu {

    /**
     * Constructeur de la classe 'ConsoleMenu'
     * @param menu_name nom du menu
     */
    public ConsoleMenu(String menu_name) {
        menu_choices = new HashMap<>();
        this.menu_name = menu_name;
        this.exit_function = null;
    }

    /**
     * Constructeur de la classe permmettant de specifier une fonction à appeler pour quitter le menu
     * @param menu_name nom du menu
     * @param exit_function fonction à appeler si l'utilisateur veux quitter le menu
     */
    public ConsoleMenu(String menu_name, Callable exit_function) {
        menu_choices = new HashMap<>();
        this.menu_name = menu_name;
        this.exit_function = exit_function;
    }

    /**
     * Ajoute un choix au menu
     * @param function fonction à appeler si le l'option est choisie
     * @param choice_name nom de l'option affiché dans le menu
     */
    public void addChoice(Callable function, String choice_name) {
        menu_choices.put(menu_choices.size(), new menu_choice(choice_name, function));
    }

    /**
     * Affiche le menu
     */
    public void runMenu() {
        while (true) {
            System.out.println("\n############## " + menu_name + " ##############");
            int i = 0;
            for (Map.Entry<Integer, menu_choice> entry : menu_choices.entrySet()) {
                System.out.println("\t" + i + ":\t" + entry.getValue().name);
                i++;
            }

            if(exit_function != null)
                System.out.println("\t  \tType any other number to exit menu");

            while(true)
            {
                int num = ConsoleUtils.lireInteger("Enter your choice: ");
                if(num >= menu_choices.size() || num < 0)
                {
                    if(exit_function != null)
                    {
                        System.out.println();
                        exit_function.call();
                        return;
                    }
                }
                else
                {
                    menu_choice choice = menu_choices.get(num);
                    System.out.println();
                    choice.callback.call();
                    break;
                }
            }
        }
    }

    private static class menu_choice
    {
        public menu_choice(String name, Callable callback)
        {
            this.name = name;
            this.callback = callback;
        }

        public String name;
        public Callable callback;
    }

    private HashMap<Integer, menu_choice> menu_choices;
    private Callable exit_function;
    private String menu_name;
}
