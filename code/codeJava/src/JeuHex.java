import java.util.*;
import java.io.*;

/**
 * @class JeuHex
 * @brief the game turns around this class
 * @var board the board of the game
 * @var joueur toggles after every turn true = black, false = white
 * @var b black player
 * @var w white player
 * @var size the boardSize entered by the players
 * @var spots the hexes of the board
 * @var hVSh true if the game is played by two humans
 */
public class JeuHex {
    private Board board;
    private boolean joueur;
    private Scanner input = new Scanner(System.in);
    private Player b, w;
    private int size;
    private String spots;
    private String configPath = "../../../doc/config/size";
    private String saveFilesPath = "../../../doc/SaveFiles/";
    private boolean hVSh;

    /**
     * @return the size of the board entered by the player
     */
    public int getSize(){
        return size;
    }

    /**
     * @return the board of the game
     */
    public Board getBoard(){
        return board;
    }

    /**
     * @return the string representation of the hexes on the board
     */
    public String getSpots(){
        return spots;
    }

    /**
     * @return the black player of the game
     */
    public Player getBlackPlayer() {
        return b;
    }

    /**
     * @return true if the game is played by two humans
     */
    public boolean isHVSh() {
        return hVSh;
    }

    /**
     * @brief makes a directory named SaveFiles that holds all the saved games
     */
    public void makeSaveDirectory(){
    	File dir = new File(saveFilesPath);
    	boolean successful = dir.mkdir();
    	if(successful)
    		System.out.println("SaveFiles directory created successfully.");
    }

    /**
     * @brief the game is configured in this function
     * @return true if the player decides to play the game once its been started
     */
    public boolean gameSetup(){
        char letterAnswer;
        char finalChoice;
        boolean start = true; // see following do while loop
        boolean letsPlay = true; //! equals false once the player quits the game

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
            do {
                letterAnswer = Menu.aiOrHuman();
                if (letterAnswer == 'A' || letterAnswer == 'H') {
                    do {
                        finalChoice = Menu.finalChoice();
                    } while (finalChoice != 'N' && finalChoice != 'Y');
                }
            } while (letterAnswer != 'A' && letterAnswer != 'H');
            if (letterAnswer == 'A') {
                hVSh = false;
                System.out.println("AI is BLACK (*)");
            }

    	    whoPlaysFirst();

    	    if (joueur) {
                if (letterAnswer == 'A') {
                    b = addPlayer(letterAnswer);
                }else {
        			b = addPlayer('H');
                }
                w = addPlayer('H');
                b.setFirstPlayer(true);
    		}else {
                if (letterAnswer == 'A') {
                    w = addPlayer('H');
                    b = addPlayer(letterAnswer);
                }else {
        			w = addPlayer('H');
                    b = addPlayer('H');
                }
                w.setFirstPlayer(true);
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

    /**
     * @brief loads player information and saved game configuration
     * @param loadFileName the name of the file where this information is saved
     */
    public void loadPlayersAndGame(String loadFileName) {
        spots = loadGame(loadFileName);
        size = (int)Math.sqrt(spots.length());
        board = initBoard(size, spots);
        loadPlayerFromString(loadFileName, Piece.BLACK);
        loadPlayerFromString(loadFileName, Piece.WHITE);
        loadPlayerMovesTab(spots);
    }

    /**
     * @return the string of board spots
     * @param loadFileName the name of the file where the spots are saved
     */
    public String loadGame(String loadFileName) {
        loadFileName = saveFilesPath + loadFileName;
        return InterfaceAvecC.nativeGetSpots(loadFileName);
    }

    /**
     * @brief creates the file to be saved
     * @return the configured string to be put in a file
     */
    public String createStringToSaveOnFile() {
        String str = "";

        char c = '0';
        if (b.isFirst()) {
            c = '1';
        }
        str = str + size + '#' + board.convertBoardToString() + c;
        return str;
    }

    /**
     * @brief saves the game and the player information into the SaveFiles direvtory
     * @param nameOfSaveFile the name of the file where the information is to be saved
     */
    public void saveGameAndPlayer(String nameOfSaveGame) {
        String newNameOfSaveGame = saveFilesPath + nameOfSaveGame;
        String stringToSave = createStringToSaveOnFile();
        InterfaceAvecC.nativeSaveGame(newNameOfSaveGame, stringToSave, b.getMovesTab(), w.getMovesTab());
        savePlayer(nameOfSaveGame, hVSh);
    }

    /**
     * @brief prompts the players to enter the board size
     */
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

    /**
     * @brief initializes the board
     * @param size the size that the board will be
     * @param spots a string representing the pieces of the board
     * @return the board that has been initialized
     */
    public Board initBoard(int size, String spots){
        board = new Board(size, spots);
    	return board;
    }

    /**
     * @brief sets the first player of the current game
     */
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

    /**
     * @brief prompts player information that will be saved into a file
     * @return the player the newly created player
     */
    public Player addPlayer(char AI){
    	Player p;
    	String alias = "";
		Date dateOfBirth;
		String email = "";
		char color;
        int day; int month; int year;

        if (AI == 'A') {
            p = new PlayerIA(this.board);
        }else {

        	if (joueur){
        		System.out.println("BLACK player...");
        		color = Piece.BLACK;
        	}else{
        		System.out.println("WHITE player...");
        		color = Piece.WHITE;
        	}
        	System.out.print("Alias? ");
        	alias = input.nextLine();

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

        	p = new Player(color, alias, dateOfBirth, email, this.board);
        }
    	joueur = !joueur;
    	return p;
    }

    /**
     * @brief saves the players into a file
     * @param nameOfSavePlayer the name of the file the players will be saved into
     * @param hVSh true if the game is played between two humans
     */
    public void savePlayer(String nameOfSavePlayer, boolean hVSh){
        nameOfSavePlayer = saveFilesPath + "savePlayer/player" + nameOfSavePlayer;
        char bC = '0';
        char wC = '1';
        char ai = '0';
        if (b.isFirst()) {
            bC = '1';
            wC = '0';
        }
        if (!hVSh) {
            ai = '1';
        }
        String wPlayer = w.toStringPlayer()+'$'+wC+ai; //on rajoute le prochain joueur
        String bPlayer = b.toStringPlayer()+'$'+bC+ai;
        InterfaceAvecC.nativeSavePlayer(nameOfSavePlayer, bPlayer, wPlayer);
    }

    /**
     * @brief loads a player from a save file in SaveFiles/savePlayer/ directory
     * @param loadfileName the name of the file where the player information is
     * @param color the color of the player to be loaded
     */
    public void loadPlayerFromString(String loadFileName, char color) {
        loadFileName = saveFilesPath + "savePlayer/player" + loadFileName;
        String loadFile = InterfaceAvecC.nativeStringToLoadPlayer(color, loadFileName);
        int size = loadFile.length();
        char[] tab = new char[size];
        for (int j = 0; j < size; j++) {
            tab[j] = loadFile.charAt(j);
        }

        String alias = "", dobString = "", email = "", whosTurnIsIt = "", isAI = "";
        Date dateOfBirth = new Date(0, 0, 0);
        int i = 0;
        int j = 0;

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
                }
            }else if (tab[i] == '@') {
                i++;
                while (tab[i] != '$') {
                    email += tab[i++];
                }
            }else if (tab[i] == '$') {
                i++;
                whosTurnIsIt += tab[i++];
                isAI += tab[i++];
            }else {
                i++;
            }
        }

        if (color == Piece.BLACK) {
            if (Integer.parseInt(isAI) == 1) {
                b = new PlayerIA(this.board);
                hVSh = false;
            }else {
                b = new Player(color, alias, dateOfBirth, email, this.board);
            }
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

    /**
     * @brief loads the moves played be a certain player in a previous game
     * @param spots a string that will contain the position of the moves played
     */
    public void loadPlayerMovesTab(String spots) {
        for (int i = 0; i < spots.length(); i++) {
            if (spots.charAt(i) == Piece.BLACK) {
                b.modifMovesTab(i);
            }else if (spots.charAt(i) == Piece.WHITE) {
                w.modifMovesTab(i);
            }
        }

        if (b.isFirst()) { //! who was first
            if (b.getNbOfMoves() == w.getNbOfMoves()) {
                joueur = true;
            }else {
                joueur = false;
            }
        }else {
            if (b.getNbOfMoves() == w.getNbOfMoves()) {
                joueur = false;
            }else {
                joueur = true;
            }
        }
    }

    /**
     * @brief allows the players to end the game with or without saving
     */
    public void quitGame() {
        int choice = 0;
        boolean ok = true;
        boolean ko = true;
        String nameOfSaveGame = "";
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
                System.out.print("enter the name of saveGame : ");
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

    /**
     * @par Play Function
     * @parblock
     * The games runs on this function, it contains a while loop that loops
     * as long as an index i is less than the number of hexes on the board,
     * neither player has won the game and neither player has quit the game
     * @endparblock
     * @return event a character equal to q (quit), w (win) or c (continue)
     */
    public char play() {
        board.printBoard();
        Player p;
    	int i = 0;
        char event = 'c';

    	while(i < board.getNbHexes() && (event == 'c')){
    		char color = Player.quiJoue(joueur);

    		if (color == Piece.BLACK)
    			p = b;
    		else
    			p = w;

            p.printPlayerInfo();
    		event = p.placePiece();


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

    /**
     * @brief prompts the name of the file to be loaded
     * @return the choice the name of the file that was entered by the players
     */
    public String chooseLoadFile() {
        String  choice = "";
        boolean ok = true;
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
