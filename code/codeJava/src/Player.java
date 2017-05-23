import java.util.Scanner;

/**
 * @class Player
 * @brief represents the a player in the game
 * @var color the color of the player
 * @var alias the player's alias
 * @var dateOfBirth the player's date of birth
 * @var email the player's email
 * @var board the board the player is playing on
 * @var movesTab an array of the coordinates the player plays on
 * @var firstPlayer true if the player plays first
 * @var winner true if the player wins a game
 * @var quitter true if the player forfeited the current game
 */
public class Player {

	private char color;
	private String alias;
	private Date dateOfBirth;
	private String email;
	private Board board;
	private Scanner input;
	private int[] movesTab;
	private int movesItr; //! index to insert in movesTab
	private boolean firstPlayer = false;
	private boolean winner = false;
	private boolean quitter = false;

	/**
	 * @par Player constructor
	 * @parblock
	 * sets the color, alias, DOB, email and board of the player
	 * the number of moves will be saved in movesTab[0]
	 * the moves played will be saved in movesTab starting at movesTab[1]
	 * @endparblock
	 */
	public Player(char color, String alias, Date dateOfBirth,
				  String email, Board board){
		this.color = color;
		this.alias = alias;
		this.dateOfBirth = dateOfBirth;
		this.email = email;
		this.board = board;
		this.input = new Scanner(System.in);

		movesTab = new int[(board.getBoardSize() * board.getBoardSize()) + 2];
		movesTab[0] = 0;
		movesItr = 1; //! the moves will be saved starting from the 1st index
	}

	/**
	 * @return the color of the player
	 */
	public char getColor() {
		return color;
	}

	/**
	 * @return the alias of the player
	 */
	public String getAlias() {
		return alias;
	}

	/**
	 * @return the dateOfBirth of the player
	 */
	public Date getDOB() {
		return dateOfBirth;
	}

	/**
	 * @return the email of the player
	 */
	public String getEmail() {
		return email;
	}

	/**
	 * @return the board on which the player is playing
	 */
	public Board getBoard() {
		return board;
	}

	/**
	 * @return the table of moves the player has played
	 */
	public int[] getMovesTab() {
		return movesTab;
	}

	/**
	 * @par nbOfMove
	 * @parblock
	 * nbOfMoves are multiplied by 2 since we increment each time a
	 * single coordinate is added
	 * @endparblock
	 * @return the nbOfMoves done by the player
	 */
	public int getNbOfMoves() {
		return movesTab[0];
	}

	/**
	 * @return the name of the player's color in the format (.) COLORNAME
	 */
	public String getColorName() {
		if (color == Piece.BLACK)
			return "(*) BLACK ";
		else
			return "(o) WHITE ";
	}

	/**
	 * @return true if the player won the game
	 */
	public boolean isWinner() {
		return winner;
	}

	/**
	 * @return true if the player starts the game
	 */
	public boolean isFirst() {
		return firstPlayer;
	}

	/**
	 * @return true if the player forfeited the game
	 */
	public boolean isQuitter() {
		return quitter;
	}

	/**
	 * @brief sets the winner of the game
	 */
	public void setWinner(boolean win) {
		this.winner = win;
	}

	/**
	 * @brief sets the first player of the game
	 */
	public void setFirstPlayer(boolean first) {
		this.firstPlayer = first;
	}

	/**
	 * @brief sets the quitter if the game
	 */
	public void setQuitter(boolean quit) {
		this.quitter = quit;
	}

	/**
	 * @brief sets the iterator index of movesTab
	 */
	public void setMovesItr(int movesItr) {
		this.movesItr = movesItr;
	}

	/**
	 * @return the player info in format : ALIAS#DD/MM/YY@PLAYER@EMAIL.COM
	 */
	public String toStringPlayer() {
		return alias + '#' + dateOfBirth.toStringDate() + '@' + email;
	}

	/**
	 * @par printPlayerInfo()
	 * @parblock
	 * Prints the player's number of turn and their previous move's coordinates
	 * @endparblock
	 */
	public void printPlayerInfo() {
		System.out.println("Turn #" + ((movesItr + 1) / 2));
		if (movesItr > 1)
		System.out.println("Last move: (" + movesTab[(movesItr - 2)] + ","
			+ movesTab[(movesItr - 1)] + ")");
	}

	/**
	 * @brief prints the moves played by the player
	 */
	public void printMovesTab() {
		for (int i = 0; i < movesItr; i++) {
			System.out.print(" "+movesTab[i]);
		}
		System.out.println();
	}

	/**
	 * @brief adds the coordinates of a played move, increments movesItr and nbOfMoves
	 * @param pos the x, y coordinates are calculated from a position
	 */
	public void modifMovesTab(int pos) {
		int x = Coordinates.calcXCoord(pos, board.getBoardSize());
		int y = Coordinates.calcYCoord(pos, board.getBoardSize());
		movesTab[movesItr++] = x;
		movesTab[movesItr++] = y;
		movesTab[0] +=2;
	}

	/**
	 * @brief prompts coordinates from the player
	 * @return coord the coordinates entered by the player
	 */
	public Coordinates enterCoordinates() {
		Coordinates coord;
		int x;
		int y;
		System.out.println(getColorName() + "PLAYER, where do you want to put your piece?");
		System.out.print("x = ");
		x = input.nextInt();
		while(x < 0 || x >= board.getBoardSize()){
			System.out.println("Please enter a number between 0 and " + (board.getBoardSize()-1));
			System.out.print("x = ");
			x = input.nextInt();
		}

		System.out.print("y = ");
		y = input.nextInt();
		while(y < 0 || y >= board.getBoardSize()){
			System.out.println("Please enter a number between 0 and " + (board.getBoardSize()-1));
			System.out.print("y = ");
			y = input.nextInt();
		}

		coord = new Coordinates(x, y);
		return coord;
	}

	/**
	 * @par placePiece Function
	 * @parblock
	 * Allows a player to place a piece of their color and modifies their
	 * movesTab. Also allows to the player to quit the game
	 * @endparblock
	 * @return event equal to c (continue game), w (a player won), q (quit game)
	 */
	public char placePiece() {
		char event = 'c';
		Coordinates coord = null;
		int choice = 0;
		int pos = -1;
		boolean ok = true;
		boolean ko = true;
		char colorBis = 0;
		char finalChoice;
		if (color == Piece.BLACK) {
			colorBis = 'b';
		}else {
			colorBis = 'w';
		}
		do {
			coord = enterCoordinates();
			pos = coord.calcPosition(coord.getXCoord(), coord.getYCoord(), board.getBoardSize());
			if (! board.getHex(pos).isFull()){
				board.getHex(pos).getPiece().setColor(colorBis);
			}else{
				System.out.println("That hex spot already has a piece on it");
				while(board.getHex(pos).isFull()){
					coord = enterCoordinates();
					pos = coord.calcPosition(coord.getXCoord(), coord.getYCoord(), board.getBoardSize());
				}
				board.getHex(pos).getPiece().setColor(colorBis);
			}
			board.printBoard();

			do {
				choice = Menu.confirmOrQuitMenu();
				if(choice == 1 || choice == 2 || choice == 3) {
					do {
						finalChoice = Menu.finalChoice();
					} while (finalChoice != 'N' && finalChoice != 'Y');
					if (finalChoice == 'Y') {
						ko = false;
					}
				}
			} while (ko);
			switch (choice) {
				case 1 :
					board.getHex(pos).getPiece().setColor(Piece.EMPTY);
					break;
				case 2 :
					board.getHex(pos).getPiece().setColor(color);
					ok = false;
					break;
				case 3 :
					board.getHex(pos).getPiece().setColor(color);
					event = 'q'; //save
					ok = false;
				break;
			}
		}while (ok);

		board.printBoard();
		modifMovesTab(pos);
		
		if (InterfaceAvecC.nativePlacePiece(pos, color) == 1) {
			event = 'w'; //win
		}
		return event;
	}

	/**
	 * @return * if joueur = true, o if joueur = false
	 */
	public static char quiJoue(boolean joueur) {
		return joueur ? Piece.BLACK : Piece.WHITE;
	}
}
