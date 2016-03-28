package TP1_SI.Utils;

import java.util.HashMap;
import java.util.Map;

/**
 * @author B3330
 */
public class ConsoleMenu {

    public ConsoleMenu(String menu_name) {
        this.menu_name = menu_name;
        exit_function = null;
    }

    public ConsoleMenu(String menu_name, Callable exit_function) {
        this.menu_name = menu_name;
        this.exit_function = exit_function;
    }

    public void addChoice(Callable function, String choice_name) {
        menu_choices.put(choice_name, function);
    }

    public void runMenu() {
        int selected_choice = 0;

        while (true) {
            System.out.println(ANSI_RESET + "############## " + menu_name + " ##############\n");
            int i = 0;
            for (Map.Entry<String, Callable> entry : menu_choices.entrySet()) {
                i++;
                if (selected_choice == i)
                    System.out.println(ANSI_RESET + "\t" + ANSI_GREEN + entry.getKey() + ANSI_RESET);
                else
                    System.out.println(ANSI_RESET + "\t" + entry.getKey());
            }
        }
    }

    private HashMap<String, Callable> menu_choices;
    private Callable exit_function;
    private String menu_name;

    private static final String ANSI_RESET = "\u001B[0m";
    private static final String ANSI_WHITE = "\u001B[37m";
    private static final String ANSI_BLACK = "\u001B[30m";
    private static final String ANSI_GREEN = "\u001B[32m";
}
