import java.util.Scanner;

/**
 * @class Menu
 * @brief this class contains all the menus to be shown through the interface
 * @var answer the answer to the questions asked in the menus
 */
public class Menu {
    private static String answer;
    private static Scanner input = new Scanner(System.in);

    /**
     * @brief asks the players if they want to start a new game, load, or quit
     * @return letterAnswer equal to N (new), L (load) or Q (quit)
     */
    public static char newLoadQuitMenu(){
        char letterAnswer;
        System.out.println("\n*-----------------------------------------*");
        System.out.println("* New game?  -> please type N             *");
        System.out.println("* Load game? -> please type L             *");
        System.out.println("* Quit game? -> please type Q             *");
        System.out.println("*-----------------------------------------*");
        System.out.print("choice : ");
        answer = input.nextLine();
        letterAnswer = answer.toUpperCase().charAt(0);
        return letterAnswer;
    }

    /**
     * @brief asks the player or players to confirm his or their choice
     * @return letterAnswer equal to Y (yes) or N (no)
     */
    public static char finalChoice(){
        char finalChoice;
        System.out.println("\n*-----------------------------------------*");
        System.out.println("* Is this your final choice?              *");
        System.out.println("* To confirm -> please type Y             *");
        System.out.println("* To return  -> please type N             *");
        System.out.println("*-----------------------------------------*");
        System.out.print("choice : ");
        answer = input.nextLine();
        finalChoice = answer.toUpperCase().charAt(0);
        return finalChoice;
    }

    /**
     * @brief asks the player if the game is multiplayer or not
     * @return letterAnswer equal to Y (yes) or N (no)
     */
    public static char aiOrHuman() {
        char letterAnswer;
        System.out.println("\n*-----------------------------------------*");
        System.out.println("* Game mode?                              *");
        System.out.println("* AI vs Human     -> please type A        *");
        System.out.println("* Human vs Human  -> please type H        *");
        System.out.println("*-----------------------------------------*");
        System.out.print("choice : ");
        answer = input.nextLine();
        letterAnswer = answer.toUpperCase().charAt(0);
        return letterAnswer;
    }

    /**
     * @brief asks the players if they want to enter a size or use the default
     * @return letterAnswer equal to Y (yes, enter a size) or N (no, use default)
     */
    public static char sizeOrDefaultMenu(){
        char letterAnswer;
        System.out.println("\n*-----------------------------------------*");
        System.out.println("* Would you like to choose the board's    *");
        System.out.println("* size?                                   *");
        System.out.println("* Yes? Enter size? -> please type Y       *");
        System.out.println("* No? (default = 11) -> please type N     *");
        System.out.println("*-----------------------------------------*");
        System.out.print("choice : ");
        answer = input.nextLine();
        letterAnswer = answer.toUpperCase().charAt(0);
        return letterAnswer;
    }

    /**
     * @brief asks the players to enter the board size they want to play on
     * @return size the size entered by the players
     */
    public static int enterSizeMenu() {
        int size;
        System.out.println("\n*-----------------------------------------*");
        System.out.println("* What size board do you wish to play on? *");
        System.out.println("* Please enter a size between 3 and 14    *");
        System.out.println("*-----------------------------------------*");
        System.out.print("size = ");
        size = input.nextInt();
        input.nextLine();
        return size;
    }

    /**
     * @brief asks the players to enter the letter of the player who will start
     * @return letterAnswer equal to B (black) or W (white)
     */
    public static char firstPlayerMenu() {
        char color;
        System.out.println("\n*-----------------------------------------*");
        System.out.println("* Who will play first?                    *");
        System.out.println("* BLACK (*) -> please type B              *");
        System.out.println("* WHITE (o) -> please type W              *");
        System.out.println("*-----------------------------------------*");
        System.out.print("first player : ");
        answer = input.nextLine();
        color = answer.toUpperCase().charAt(0);
        return color;
    }

    /**
     * @brief asks the player to confirm or undo their move or quit the game
     * @return choice equals 1 (undo move), 2 (confirm their move) or 3 (quit)
     */
    public static int confirmOrQuitMenu() {
        int choice;
        System.out.println("\n*------------------------------------------*");
        System.out.println("* Do you want to change your mind or quit? *");
        System.out.println("* 1 : To change position.                  *");
        System.out.println("* 2 : To confirm your position.            *");
        System.out.println("* 3 : If you want to quit.                 *");
        System.out.println("*------------------------------------------*");
        System.out.print("choice : ");
        choice = input.nextInt();
        input.nextLine();
        return choice;
    }

    /**
     * @brief asks the players want to save their game or not
     * @return choice equals 1 (save the game) or 2 (discard the game)
     */
    public static int quitMenu() {
        int choice;
        System.out.println("\n*------------------------------------------*");
        System.out.println("* What do you want to do?                  *");
        System.out.println("* 1 : Quit and save.                       *");
        System.out.println("* 2 : Quit and not save.                   *");
        System.out.println("*------------------------------------------*");
        System.out.print("choice = ");
        choice = input.nextInt();
        input.nextLine();
        return choice;
    }
}
