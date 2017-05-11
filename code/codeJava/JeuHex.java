import java.util.*;
import java.io.*;

public class JeuHex {
    // private static final int nbJoueurs = 2;
    private String answer; //answer of questions asked through interface
    private Board board; //board of the game
    private boolean joueur; //true = black, false = white
    private Scanner input = new Scanner(System.in);
    private Player b, w;

    //makes the save file directory if it does not already exist
    public void makeSaveDirectory(){
    	File dir = new File("../../SaveFiles");
    	boolean successful = dir.mkdir();
    	if(successful)
    		System.out.println("SaveFiles directory created successfully.");
    }

    public void gameSetup(){
    	int size; //size entered by the players
		do {
    		System.out.println("New game? -> please type N\nLoad game? -> please type L");
    		answer = input.nextLine();
    	} while (answer.toUpperCase().charAt(0) != 'N' 
    		&& answer.toUpperCase().charAt(0) != 'L');
    	
    	if (answer.toUpperCase().charAt(0) == 'N'){
    		size = setBoardSize();
    		board = initBoard(size);
    		board.printBoard();
    		joueur = whoPlaysFirst();
    		if (joueur){
    			b = addPlayer();
    			w = addPlayer();
    		}else{
    			w = addPlayer();
    			b = addPlayer();    			    			
    		}
    	}/*else{
    		String savedFileName;
    	}*/
    }

    public int setBoardSize(){
    	int size;
    	do {
    		System.out.println("Would you like to choose the board's size (default = 11)\nY/N?");
    		answer = input.nextLine();
    	} while (answer.toUpperCase().charAt(0) != 'Y' 
    		&& answer.toUpperCase().charAt(0) != 'N');

    	if (answer.charAt(0) == 'Y' || answer.charAt(0) == 'y'){
    		System.out.println("What size board do you wish to play on?");

    		do {
    			System.out.println("Please enter a size between 3 and 14:");
    			size = input.nextInt();
    		} while (size > 14 || size < 3);
	   	}else{
	   		System.out.println("The board size will be 11");
	   		size = Board.defaultSize;
	   	}

	   	return size;
    }

    public Board initBoard(int size){
    	board = InterfaceAvecC.nativeInitBoard(size);
    	// board = new Board(size);
    	return board;
    }

    public boolean whoPlaysFirst(){
    	System.out.println("Who will play first? BLACK (*) or WHITE (o)");
    	do {
    		System.out.println("BLACK = B, WHITE = W");
    		answer = input.next();
    	} while (answer.toUpperCase().charAt(0) != 'B'
    		&& answer.toUpperCase().charAt(0) != 'W');

    	if (answer.charAt(0) == 'B' || answer.charAt(0) == 'b'){
    		System.out.println("BLACK (*) will start");
    		joueur = true;
    	}else{
    		System.out.println("WHITE (o) will start");
    		joueur = false;
    	}

    	return joueur;
    }

    public Player addPlayer(){
    	Player p;
    	String alias = "";
		String dateOfBirth = "";
		String email = "";
		char color;

    	if (joueur){
    		System.out.println("BLACK player...");
    		color = Piece.BLACK;
    	}else{
    		System.out.println("WHITE player...");
    		color = Piece.WHITE;
    	}

    	System.out.print("Alias? ");
    	alias = input.nextLine();
    	System.out.print("Date of birth (YY/MM/DD)? ");
    	dateOfBirth = input.nextLine();
    	System.out.print("Email? ");
    	email = input.nextLine();

    	p = new Player(color, alias, dateOfBirth, email, this.board);
    	joueur = !joueur;
    	return p;
    }

    // public void jouer(){
    // 	while(int i = 0 < board.getNbHexes()){

    // 	}
    // }

    public static void main (String[] args){
    	JeuHex jeu = new JeuHex();
    	jeu.makeSaveDirectory();
    	jeu.gameSetup();
    }
}
