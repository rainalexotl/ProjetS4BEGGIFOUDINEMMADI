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

    //
public boolean gameSetup(){
    char letterAnswer;
    char finalChoice;
    boolean ok = true;
    boolean ko = true; //if we want to continue the game
	do {
        System.out.println("*------------------------------------------*");
		System.out.println("* New game?  -> please  type N             *");
		System.out.println("* Load game? -> please  type L             *");
		System.out.println("* Quit game? -> please  tape Q             *");
		System.out.println("*------------------------------------------*");
        System.out.print("choice = ");
		answer = input.nextLine();
        letterAnswer = answer.toUpperCase().charAt(0);
        boolean test = (letterAnswer == 'L');
        if (letterAnswer == 'N' || letterAnswer == 'L' || letterAnswer == 'Q') {
            System.out.println("choice = "+letterAnswer );
            do{
                System.out.println("*------------------------------------------*");
        		System.out.println("* Is this your final choice?               *");
        		System.out.println("* To confirm -> please  type Y             *");
        		System.out.println("* To Return  -> please  tape N             *");
        		System.out.println("*------------------------------------------*");
                System.out.print("choice = ");
                finalChoice = input.nextLine().toUpperCase().charAt(0);
            }while(finalChoice != 'N' && finalChoice != 'Y');
            if (finalChoice != 'N') {
                ok = false;
            }
        }
	} while (ok);


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
        //System.out.println("j'affiche les information des joueurs\n"+b.toPlayer()
        //+"\n"+w.toPlayer());
	}else if (letterAnswer == 'L'){
        String nameOfLoadGame = menuChooseFile();
        spots = loadGame(nameOfLoadGame); //menuChooseFile() : return the save file
        size = (int)Math.sqrt(spots.length());
        board = initBoard(size, spots);
        loadPlayerFromString(nameOfLoadGame, Piece.BLACK);
        loadPlayerFromString(nameOfLoadGame, Piece.WHITE);
        loadCirconstanceOfPlayerTabGame(spots);
        //System.out.println("j'affiche les information des joueurs\n"+b.toPlayer()
        //+"\n"+w.toPlayer());
	}else {
        ko = false;
        System.out.println("***********************");
        System.out.println("*    SEE YOUY SOON    *");
        System.out.println("***********************");
    }
    return ko;
}

    // public void loadPlayer(String nameOfLoadPlayer ,char color) {
    //     loadPlayerFromString("player.txt", color);
    // }

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
    public void saveGameAndPlayer(String nameOfSaveGame) {
        String newNameOfSaveGame ="../../SaveFiles/"+nameOfSaveGame; //explain the root
        //String newsNameOfSavePlayer="../../SaveFiles/"+nameOfSavePlayer;
        //System.out.println(newNameOfSaveGame+"   "+nameOfSavePlayer);
        String stringToSave = creteStringToSaveOnFile();
        //System.out.println("board to save = "+stringToSave);
        InterfaceAvecC.nativeSaveGame(newNameOfSaveGame, stringToSave, b.getTabGame(), w.getTabGame());
        savePlayer(nameOfSaveGame);
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

        input.nextLine(); // on vide le cash avant le prochain nextLine
    	System.out.print("Date of birth (YY/MM/DD)? ");
    	dateOfBirth = input.nextLine();

        input.nextLine(); // on vide le cash avant le prochain nextLine
    	System.out.print("Email? ");
    	email = input.nextLine();
        //input.nextLine(); // on vide le cash avant le prochain nextLine

    	p = new Player(color, alias, dateOfBirth, email, this.board);
    	joueur = !joueur;
    	return p;
    }

    //save the iformation of player
    public void savePlayer(String nameOfSavePlayer){
        nameOfSavePlayer = "../../SaveFiles/savePlayer/"+"player"+nameOfSavePlayer;
        char bC = '0';
        char wC = '1';
        if (b.isFirst()) {
            bC = '1';
            wC = '0';
        }
        String WPlayer = w.toPlayer()+'$'+wC; //on rajoute le prochain joueur
        String BPlayer = b.toPlayer()+'$'+bC;
        InterfaceAvecC.nativeSavePlayer(nameOfSavePlayer, BPlayer, WPlayer);
    }
    // I'm here
    //load player from save file
    // return a boolean to specifie who is the turn
    public void loadPlayerFromString(String stringFromFilInC, char color) {
        stringFromFilInC = "../../SaveFiles/savePlayer/"+"player"+stringFromFilInC;
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
        System.out.println(loadFil);
        while (i < size-1) {
            if (tab[i] == color) {
                i++;
                while (tab[i] != '#') {
                    Alias += tab[i++];
                }
            }else if (tab[i] == '#'){
                i++;
                while (tab[i] != '@') {
                    DateOfBirth += tab[i++];
                }
            }else if (tab[i] == '@') {
                i++;
                while (tab[i] != '$') {
                    Email += tab[i++];
                }
            }else if (tab[i] == '$') {
                i++;
                System.out.println(tab[i]+" "+i+" color "+color);
                WhoIsTheTurn += tab[i++];
            }else {
                i++;
            }

        }

        if (color == Piece.BLACK) {
            b = new Player(color, Alias, DateOfBirth, Email, this.board);
            if (Integer.parseInt(WhoIsTheTurn) == 1) {
                b.setImFirst(true);
            }
        }else {
            w = new Player(color, Alias, DateOfBirth, Email, this.board);
            if (Integer.parseInt(WhoIsTheTurn) == 1) {
                w.setImFirst(true);
            }
        }
        System.out.println("turn "+Integer.parseInt(WhoIsTheTurn)+" color"+color);
        //return Integer.parseInt(WhoIsTheTurn); //pour savoir qui cmmence
    }

    void loadCirconstanceOfPlayerTabGame(String spots) {
        for (int i = 0; i < spots.length(); i++) {
            if (spots.charAt(i) == Piece.BLACK) {
                b.modifTabGame(i);
            }else if (spots.charAt(i) == Piece.WHITE) {
                w.modifTabGame(i);
            }
        }
        System.out.println("taille du tableau \nblack = "+b.getNbTurnsPlay()+"\nwhile = "+w.getNbTurnsPlay());
        b.printTabGame();
        System.out.println("\n");
        w.printTabGame();
        System.out.println("\n");

        //who is turn
        if (b.isFirst()) {
            if (b.getNbTurnsPlay() == w.getNbTurnsPlay()) {
                joueur = true;
            }else {
                joueur = false;
            }
        }else {
            System.out.println("je passe la poir le teste de a qui le tour");
            if (b.getNbTurnsPlay() == w.getNbTurnsPlay()) {
                joueur = false; //while turn
            }else {
                joueur = true;
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
                input.nextLine();
                System.out.print("enter the name of saveGame   : ");
                nameOfSaveGame = input.nextLine();
                //input.nextLine(); //to free buff
                //System.out.print("enter the name of savePlayer : ");
                ///nameOfSavePlayer = input.nextLine();
                //System.out.println("save player in = "+nameOfSavePlayer+"\nsave game in = "+nameOfSaveGame);
                saveGameAndPlayer(nameOfSaveGame);
                ok = false;
            }else if (choice == 2) {
                ok = false;
            }
        } while (ok);
    }

    public int play() {
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

    public String menuChooseFile() {
        String  choice = "";
        boolean ok = true;
        boolean ko = true;
        String []saveFile = InterfaceAvecC.nativeGetSaveFile();

        System.out.println("wich file do you want to load?");
        for(int i = 0; i < saveFile.length; i++){
            System.out.println(saveFile[i]);
        }
        do {
            System.out.print("choice : ");
            choice = input.nextLine();
            for(int i = 0; i < saveFile.length; i++){
                if (choice.equals(saveFile[i])) {
                    ko = false;
                    i = saveFile.length;
                }

            }
        }while(ko);
        return choice;
    }

    public static void main (String[] args) {
    	JeuHex jeu = new JeuHex();
    	jeu.makeSaveDirectory();
        if(jeu.gameSetup())
            if(InterfaceAvecC.nativeInitGame(jeu.getSpots(), jeu) == 1)
                jeu.quitMenu();
    }
}
