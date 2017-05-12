import java.util.*;
import java.io.*;

public class JeuHex {
    // private static final int nbJoueurs = 2;
    private String answer; //answer of questions asked through interface
    private Board board; //board of the game
    private boolean joueur; //true = black, false = white
    private Scanner input = new Scanner(System.in);
    private Player b, w;
    private int size; //size entered by the players
    private String spots;

    public int getSize(){
        return size;
    }

    public Board getBoard(){
        return board;
    }

    public String getSpots(){
        return spots;
    }

    //makes the save file directory if it does not already exist
    public void makeSaveDirectory(){
    	File dir = new File("../../SaveFiles");
    	boolean successful = dir.mkdir();
    	if(successful)
    		System.out.println("SaveFiles directory created successfully.");
    }

    public void gameSetup(){
        char letterAnswer;
		do {
    		System.out.println("New game? -> please type N\nLoad game? -> please type L");
    		answer = input.nextLine();
            letterAnswer = answer.toUpperCase().charAt(0);
    	} while (letterAnswer != 'N' && letterAnswer != 'L');

    	if (letterAnswer == 'N'){
    		size = setBoardSize();
            //setBoardSize(this.size);
            System.out.println(size);
            spots = InterfaceAvecC.nativeGetSpots(createFileName(letterAnswer,
             Integer.toString(size)));
            System.out.println(spots);
    		board = initBoard(size, spots);

    	    board.printBoard();
    	    joueur = whoPlaysFirst();

    	    if (joueur){
    			b = addPlayer(size);
                w = addPlayer(size);
    		}else{
    			w = addPlayer(size);
                b = addPlayer(size);
    		}
    	}/*else{
    		String savedFileName;
    	}*/
    }

    public String createFileName(char c, String input){
        String fileName;
        if (c == 'N' || c == 'n'){
            fileName = "../../config/size" + input + ".txt";
        }else {
            fileName = "../../SaveFiles/" + input;
        }
        return fileName;
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

    public Board initBoard(int size, String spots){
    	board = InterfaceAvecC.nativeInitBoard(size, spots);
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

    public Player addPlayer(int size){
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
        input.nextLine(); // on vide le cash avant le prochain nextLine
    	System.out.print("Date of birth (YY/MM/DD)? ");
    	dateOfBirth = input.nextLine();
        input.nextLine();
    	System.out.print("Email? ");
    	email = input.nextLine();

    	p = new Player(color, alias, dateOfBirth, email, this.board);
    	joueur = !joueur;
    	return p;
    }

    public int play(){
        System.out.println("je passe la en java");
        // board = initBoard(size, spots);
        board.printBoard();
        //InterfaceAvecC.nativePlacePiece(4, '*');
        //board.printBoard();
        //boucle de jeux
        Player p;
    	int i = 0;
    	while(i < board.getNbHexes()){
    		char color = Player.quiJoue(joueur);

    		if (color == Piece.BLACK)
    			p = b;
    		else
    			p = w;

    		p.placePiece();
    		board.printBoard();
    		joueur = !joueur;
    	}
        return 0;
    }

    public static void main (String[] args){
    	JeuHex jeu = new JeuHex();
    	jeu.makeSaveDirectory();
        jeu.gameSetup();
        System.out.println("je passe la en java");
        InterfaceAvecC.nativeInitGame(jeu.getSpots(), jeu);
        //jeu.getBoard().printBoard();
    }
}
