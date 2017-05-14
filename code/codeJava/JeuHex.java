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

    public Player getBlackPlayer() {
        return b;
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
            System.out.println(size);
            spots = InterfaceAvecC.nativeGetSpots(createFileName(letterAnswer,
            Integer.toString(size)));
    		board = initBoard(size, spots);
    	    joueur = whoPlaysFirst();
    	    if (joueur){
    			b = addPlayer();
                w = addPlayer();
    		}else{
    			w = addPlayer();
                b = addPlayer();
    		}
            //save the first player
            if (joueur) {
                b.setImFirst(true);
            }else {
                w.setImFirst(true);
            }
            System.out.println("j'affiche les information des joueurs\n"+b.toPlayer()
            +"\n"+w.toPlayer());
    	}else{
            spots = loadGame("jeu1.txt");
            size = (int)Math.sqrt(spots.length());
            board = initBoard(size, spots);
            loadPlayerFromString("player.txt", Piece.BLACK);
            loadPlayerFromString("player.txt", Piece.WHITE);
            loadCirconstanceOfPlayerTabGame(spots);
            System.out.println("j'affiche les information des joueurs\n"+b.toPlayer()
            +"\n"+w.toPlayer());
    	}
    }

    public String loadGame(String nameOfsaveToLoad) {
        nameOfsaveToLoad = "../../SaveFiles/"+nameOfsaveToLoad;
        return InterfaceAvecC.nativeGetSpots(nameOfsaveToLoad);
    }

    // create the file to save
    public String creteStringToSaveOnFile() {
        String str = "";

        char c = '0';
        if (b.isFirst()) {
            c = '1';
        }
        str =str+size+'#'+board.convertBoardToString()+c;
        System.out.println("string creer = "+str);
        return str;
    }

    //save game and player
    public void saveGameAndPlayer(String nameOfSaveGame, String nameOfSavePlayer) {
        String newNameOfSaveGame ="../../SaveFiles/"+nameOfSaveGame; //explain the root
        //String newsNameOfSavePlayer="../../SaveFiles/"+nameOfSavePlayer;
        System.out.println(newNameOfSaveGame+"   "+nameOfSavePlayer);
        String stringToSave = creteStringToSaveOnFile();
        System.out.println("board to save = "+stringToSave);
        InterfaceAvecC.nativeSaveGame(newNameOfSaveGame, stringToSave, b.getTabGame(), w.getTabGame());
        savePlayer(nameOfSavePlayer);
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
    	//board = InterfaceAvecC.nativeInitBoard(size, spots);
        board = new Board(size, spots);
    	return board;
    }

    //
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

    //create a new player
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
        input.nextLine(); // on vide le cash avant le prochain nextLine
    	dateOfBirth = input.nextLine();
    	System.out.print("Email? ");
        input.nextLine();
    	email = input.nextLine();
        input.nextLine(); // on vide le cash avant le prochain nextLine

    	p = new Player(color, alias, dateOfBirth, email, this.board);
    	joueur = !joueur;
    	return p;
    }

    //save the iformation of player
    public void savePlayer(String nameOfSavePlayer){
        nameOfSavePlayer = "../../SaveFiles/"+nameOfSavePlayer;
        String WPlayer = w.toPlayer()+'$'+joueur; //on rajoute le prochain joueur
        String BPlayer = b.toPlayer()+'$'+joueur;
        InterfaceAvecC.nativeSavePlayer(nameOfSavePlayer, b.toPlayer(), WPlayer);
    }
    // I'm here
    //load player from save file
    // return a boolean to specifie who is the turn
    public int loadPlayerFromString(String stringFromFilInC, char color) {
        stringFromFilInC = "../../SaveFiles/"+stringFromFilInC;
        String loadFil = InterfaceAvecC.nativeStringToLoadPlayer(color, stringFromFilInC);
        System.out.println(loadFil);
        int size = loadFil.length();
        System.out.println(size);
        char[] tab = new char[size];
        for (int j = 0; j < size; j++) {
            tab[j] = loadFil.charAt(j);
        }

        String Alias = "", DateOfBirth = "", Email = "", WhoIsTheTurn = "";
        int i = 0;
        while (i < size) {
            //System.out.println(tab[i]);
            //# symbole of date in the save fil
            if (tab[i] == color) {
                i++;
                while (tab[i] != '#') {
                    Alias += tab[i++];
                }
                //System.out.println(Alias);
            }else if (tab[i] == '#'){
                i++;
                while (tab[i] != '@') {
                    DateOfBirth += tab[i++];
                }
                //System.out.println(DateOfBirth);
            }else if (tab[i] == '@') {
                i++;
                while (tab[i] != '$') {
                    Email += tab[i++];
                }
                //System.out.println(Email);
            }else {
                //System.out.println(tab[i]);

                i++;
                WhoIsTheTurn += tab[i++];
            }
        }

        if (color == Piece.BLACK) {
            b = new Player(color, Alias, DateOfBirth, Email, this.board);
        }else {
            w = new Player(color, Alias, DateOfBirth, Email, this.board);
        }
        System.out.println(Integer.parseInt(WhoIsTheTurn));
        return Integer.parseInt(WhoIsTheTurn);
    }

    void loadCirconstanceOfPlayerTabGame(String spots) {
        for (int i = 0; i < spots.length(); i++) {
            if (spots.charAt(i) == Piece.BLACK) {
                b.modifTabGame(i);
            }else if (spots.charAt(i) == Piece.WHITE) {
                w.modifTabGame(i);
            }
        }
    }

    void  quitMenu() {
        int choice = 0;
        boolean ok = true;
        boolean ko = true;
        String nameOfSaveGame = "";
        String nameOfSavePlayer = "";
        do {
            System.out.println("*------------------------------------------*");
			System.out.println("* What do you want to do?                  *");
			System.out.println("* 1 : quit and save.                       *");
			System.out.println("* 2 : quit and not save.                   *");
			//System.out.println("* 3 : If you want to quit.                 *");
			System.out.println("*------------------------------------------*");
            do {
                System.out.print("choice : ");
                choice = input.nextInt();
                if (choice == 1 || choice == 2) {
                    ko = false;
                }
            } while (ko);
            if (choice == 1) {
                //System.out.print("enter the name of saveGame   : ");
                //nameOfSaveGame = input.nextLine();
                //input.nextLine(); //to free buff
                //System.out.print("enter the name of savePlayer : ");
                //nameOfSavePlayer = input.nextLine();
                saveGameAndPlayer("jeu1.txt", "player1.txt");
                ok = false;
            }else if (choice == 2) {
                ok = false;
            }
        } while (ok);
    }

    public int play(){
        System.out.println("je passe la en java");
        board.printBoard();
        Player p;
    	int i = 0;
        boolean stop = false;
        System.out.println(board.getNbHexes());
    	while(i < board.getNbHexes() && !stop){
    		char color = Player.quiJoue(joueur);

    		if (color == Piece.BLACK)
    			p = b;
    		else
    			p = w;

    		stop = p.placePiece();

    		//board.printBoard();
            p.printTabGame();
            //System.out.println("\n");
            //w.printTabGame();
    		joueur = !joueur;
            //System.out.println("\n "+i);
            i++;
    	}
        if (stop) { //I do just that but we can change if we want, just for test
            return 1;
        }else {
            return 0;
        }

    }

    public static void main (String[] args){
    	JeuHex jeu = new JeuHex();
    	jeu.makeSaveDirectory();
        jeu.gameSetup();
        System.out.println("je passe la en java");
        if(InterfaceAvecC.nativeInitGame(jeu.getSpots(), jeu) == 1);
            jeu.quitMenu();
        //System.out.println(Integer.parseInt("23")+2);

        //jeu.getBoard().printBoard();
    }
}
