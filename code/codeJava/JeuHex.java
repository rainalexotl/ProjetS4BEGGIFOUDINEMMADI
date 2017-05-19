import java.util.*;
import java.io.*;

public class JeuHex {
    private Board board; //board of the game
    private boolean joueur; //true = black, false = white
    private Scanner input = new Scanner(System.in);
    private Player b, w;
    private int size; //size entered by the players
    private String spots;
    private String configPath = "../../config/size";
    private String saveFilesPath = "../../SaveFiles/";

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
    	File dir = new File(saveFilesPath);
    	boolean successful = dir.mkdir();
    	if(successful)
    		System.out.println("SaveFiles directory created successfully.");
    }

    public boolean gameSetup(){
        char letterAnswer;
        char finalChoice;
        boolean start = true; // see following do while loop
        boolean letsPlay = true; // equals false once the player quits the game

    	do {
            letterAnswer = Menu.newLoadQuitMenu();
            if (letterAnswer == 'N' || letterAnswer == 'L' || letterAnswer == 'Q') {
                do {
                    finalChoice = Menu.finalChoice();
                } while(finalChoice != 'N' && finalChoice != 'Y');
                if (finalChoice == 'Y') {
                    start = false;
                }
            }
    	} while (start);

    	if (letterAnswer == 'N') {
    		enterBoardSize();
            String newFileName = configPath + Integer.toString(size) + ".txt";
            spots = InterfaceAvecC.nativeGetSpots(newFileName);
    		board = initBoard(size, spots);
    	    whoPlaysFirst();
    	    if (joueur) {
    			b = addPlayer(); b.setFirstPlayer(true);
                w = addPlayer();
    		}else {
    			w = addPlayer(); w.setFirstPlayer(true);
                b = addPlayer();
    		}
    	}else if (letterAnswer == 'L') {
            String loadFileName = chooseLoadFile();
            loadPlayersAndGame(loadFileName);
    	}else {
            letsPlay = false;
            System.out.println("**********************");
            System.out.println("*    SEE YOU SOON    *");
            System.out.println("**********************");
        }
        return letsPlay;
    }

    public void loadPlayersAndGame(String loadFileName) {
        spots = loadGame(loadFileName);
        size = (int)Math.sqrt(spots.length());
        board = initBoard(size, spots);
        loadPlayerFromString(loadFileName, Piece.BLACK);
        loadPlayerFromString(loadFileName, Piece.WHITE);
        loadPlayerMovesTab(spots);
    }

    public String loadGame(String loadFileName) {
        loadFileName = saveFilesPath + loadFileName;
        return InterfaceAvecC.nativeGetSpots(loadFileName);
    }

    // create the file to save
    public String createStringToSaveOnFile() {
        String str = "";

        char c = '0';
        if (b.isFirst()) {
            c = '1';
        }
        str = str + size + '#' + board.convertBoardToString() + c;
        return str;
    }

    //save game and player
    public void saveGameAndPlayer(String nameOfSaveGame) {
        String newNameOfSaveGame = saveFilesPath + nameOfSaveGame; //explain the root
        String stringToSave = createStringToSaveOnFile();
        InterfaceAvecC.nativeSaveGame(newNameOfSaveGame, stringToSave, b.getMovesTab(), w.getMovesTab());
        savePlayer(nameOfSaveGame);
    }

    public void enterBoardSize(){
        char letterAnswer;
    	do {
    		letterAnswer = Menu.sizeOrDefaultMenu();
    	} while (letterAnswer != 'Y' && letterAnswer != 'N');

    	if (letterAnswer == 'Y'){
    		do {
    			size = Menu.enterSizeMenu();
    		} while (size > 14 || size < 3);
	   	}else{
	   		System.out.println("The board size will be 11");
	   		size = Board.defaultSize;
	   	}
    }

    public Board initBoard(int size, String spots){
        board = new Board(size, spots);
    	return board;
    }

    //
    public void whoPlaysFirst(){
        char letterAnswer;
    	do {
            letterAnswer = Menu.firstPlayerMenu();
    	} while (letterAnswer != 'B' && letterAnswer != 'W');

    	if (letterAnswer == 'B') {
    		System.out.println("BLACK (*) will start");
    		joueur = true;
    	}else {
    		System.out.println("WHITE (o) will start");
    		joueur = false;
    	}
    }

    //create a new player
    public Player addPlayer(){
    	Player p;
    	String alias = "";
		Date dateOfBirth;
		String email = "";
		char color;
        int day; int month; int year;

    	if (joueur){
    		System.out.println("BLACK player...");
    		color = Piece.BLACK;
    	}else{
    		System.out.println("WHITE player...");
    		color = Piece.WHITE;
    	}
    	System.out.print("Alias? ");
    	alias = input.nextLine();

        // input.nextLine(); // on vide le cash avant le prochain nextLine
    	System.out.println("Date of birth (DD/MM/YY)? ");
        do {
            System.out.print("Day? "); day = input.nextInt();
        } while (day > 31 || day < 1);
        do {
            System.out.print("Month? "); month = input.nextInt();
        } while (month > 12 || month < 1);
        do {
            System.out.print("Year? "); year = input.nextInt();
        } while (year < 0 || year > 99);

    	dateOfBirth = new Date(day, month, year);

        input.nextLine(); // on vide le cash avant le prochain nextLine
    	System.out.print("Email? ");
    	email = input.nextLine();
        //input.nextLine(); // on vide le cash avant le prochain nextLine

    	p = new Player(color, alias, dateOfBirth, email, this.board);
        dateOfBirth.toStringDate();
    	joueur = !joueur;
    	return p;
    }

    //save the iformation of player
    public void savePlayer(String nameOfSavePlayer){
        nameOfSavePlayer = saveFilesPath + "savePlayer/player" + nameOfSavePlayer;
        char bC = '0';
        char wC = '1';
        if (b.isFirst()) {
            bC = '1';
            wC = '0';
        }
        String wPlayer = w.toStringPlayer()+'$'+wC; //on rajoute le prochain joueur
        String bPlayer = b.toStringPlayer()+'$'+bC;
        InterfaceAvecC.nativeSavePlayer(nameOfSavePlayer, bPlayer, wPlayer);
    }

    //loads player from save file in SaveFiles/savePlayer directory
    public void loadPlayerFromString(String loadFileName, char color) {
        loadFileName = saveFilesPath + "savePlayer/player" + loadFileName;
        String loadFile = InterfaceAvecC.nativeStringToLoadPlayer(color, loadFileName);
        // System.out.println(loadFile);
        int size = loadFile.length();
        // System.out.println(size);
        char[] tab = new char[size];
        for (int j = 0; j < size; j++) {
            tab[j] = loadFile.charAt(j);
        }

        String alias = "", dobString = "", email = "", whosTurnIsIt = "";
        String dayString = "", monthString = "", yearString = "";
        Date dateOfBirth = new Date(0, 0, 0);
        int i = 0;
        int j = 0;
        System.out.println(loadFile);
        while (i < size - 1) {
            if (tab[i] == color) {
                i++;
                while (tab[i] != '#') {
                    alias += tab[i++];
                }
            }else if (tab[i] == '#') {
                i++;
                while (tab[i] != '@') {
                    if (tab[i] != '/') {
                        dobString += tab[i];
                        if (j == 1) {
                            dateOfBirth.setDay(Integer.parseInt(dobString));
                        }else if (j == 3) {
                            dateOfBirth.setMonth(Integer.parseInt(dobString));
                        }else if (j == 5) {
                            dateOfBirth.setYear(Integer.parseInt(dobString));
                        }
                        dobString = "";
                        j++;
                    }
                    i++;

                    // if (dobString.charAt(j) != '/') {
                    //     if (j == 0 || j == 1) {
                    //         dayString += dobString.charAt(j);
                    //     }else if (j == 2 || j == 3) {
                    //         monthString += dobString.charAt(j + 1);
                    //     }else if (j == 4 || j == 5) {
                    //         yearString += dobString.charAt(j + 2);
                    //     }
                    // }
                    // j++;
                }
            }else if (tab[i] == '@') {
                i++;
                while (tab[i] != '$') {
                    email += tab[i++];
                }
            }else if (tab[i] == '$') {
                i++;
                whosTurnIsIt += tab[i++];
            }else {
                i++;
            }
        }
        System.out.println(dateOfBirth.toStringDate());

        if (color == Piece.BLACK) {
            b = new Player(color, alias, dateOfBirth, email, this.board);
            if (Integer.parseInt(whosTurnIsIt) == 1) {
                b.setFirstPlayer(true);
            }
        }else {
            w = new Player(color, alias, dateOfBirth, email, this.board);
            if (Integer.parseInt(whosTurnIsIt) == 1) {
                w.setFirstPlayer(true);
            }
        }
    }

    public void loadPlayerMovesTab(String spots) {
        for (int i = 0; i < spots.length(); i++) {
            if (spots.charAt(i) == Piece.BLACK) {
                b.modifMovesTab(i);
            }else if (spots.charAt(i) == Piece.WHITE) {
                w.modifMovesTab(i);
            }
        }

        //who is turn
        if (b.isFirst()) {
            if (b.getNbOfMoves() == w.getNbOfMoves()) {
                joueur = true;
            }else {
                joueur = false;
            }
        }else {
            if (b.getNbOfMoves() == w.getNbOfMoves()) {
                joueur = false; //while turn
            }else {
                joueur = true;
            }
        }
    }

    public void quitGame() {
        int choice = 0;
        boolean ok = true;
        boolean ko = true;
        String nameOfSaveGame = "";
        // String nameOfSavePlayer = "";
        char finalChoice;
        do {
            do {
                choice = Menu.quitMenu();
                if (choice == 1 || choice == 2) {
					do {
						finalChoice = Menu.finalChoice();
					} while (finalChoice != 'N' && finalChoice != 'Y');
                    if (finalChoice == 'Y') {
                        ko = false;
                    }
                }
            } while (ko);
            if (choice == 1) {
                input.nextLine();
                System.out.print("enter the name of saveGame   : ");
                nameOfSaveGame = input.nextLine();
                saveGameAndPlayer(nameOfSaveGame);
                ok = false;
            }else if (choice == 2) {
                if (joueur) {
                    w.setQuitter(true);
                }else {
                    b.setQuitter(true);
                }
                ok = false;
            }
        } while (ok);
    }

    public char play() {
        System.out.println("je passe la en java");
        board.printBoard();
        Player p;
    	int i = 0;
        char event = 'c';
        System.out.println(board.getNbHexes());
    	while(i < board.getNbHexes() && (event == 'c')){
    		char color = Player.quiJoue(joueur);

    		if (color == Piece.BLACK)
    			p = b;
    		else
    			p = w;

    		event = p.placePiece();

            p.printMovesTab();
    		joueur = !joueur;
            i++;
            if (event == 'w') {
                p.setWinner(true);
                event = 'w';
            }else if (event == 'q'){
                event = 'q';
            }
    	}
        return event;
    }

    public String chooseLoadFile() {
        String  choice = "";
        boolean ok = true;
        // boolean ko = true;
        String []saveFile = InterfaceAvecC.nativeGetSaveFile();

        System.out.println("Which file do you want to load?");
        for(int i = 0; i < saveFile.length; i++){
            System.out.println(saveFile[i]);
        }
        do {
            System.out.print("choice : ");
            choice = input.nextLine();
            for(int i = 0; i < saveFile.length; i++){
                if (choice.equals(saveFile[i])) {
                    ok = false;
                    i = saveFile.length;
                }

            }
        } while(ok);
        return choice;
    }

    public static void main (String[] args) {
    	JeuHex jeu = new JeuHex();
    	jeu.makeSaveDirectory();
        if(jeu.gameSetup())
            if(InterfaceAvecC.nativeInitGame(jeu.getSpots(), jeu) == 'q')
                jeu.quitGame();
            else
                if (jeu.getBlackPlayer().isWinner())
                    System.out.println("\nBLACK PLAYER WINS!\n");
                else
                    System.out.println("\nWHITE PLAYER WINS!\n");
    }
}
