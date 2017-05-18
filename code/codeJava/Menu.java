import java.util.Scanner;

public class Menu {
    private static String answer;
    private static Scanner input = new Scanner(System.in);

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

    public static int confirmOrQuitMenu() {
        int choice;
        System.out.println("\n*------------------------------------------*");
        System.out.println("* Do you want to change your mind or quit? *");
        System.out.println("* 1 : To change position.                  *");
        System.out.println("* 2 : To confirm your position.            *");
        System.out.println("* 3 : If you want to quit.                 *");
        System.out.println("*------------------------------------------*");
        choice = input.nextInt();
        input.nextLine();
        return choice;
    }

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
