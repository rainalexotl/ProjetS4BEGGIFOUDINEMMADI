import java.util.Scanner;

public class Player {

	private char color; //the player's color
	private String alias;
	private String dateOfBirth;
	private String email;
	private Board board; //the board the player is playing on
	private Scanner input;
	private int[] movesTab;
	private int movesItr; // index to insert in movesTab
	private boolean firstPlayer = false;
	private boolean winner = false;
	private boolean quitter = false; //if the player abandoned the current game

	public Player(char color, String alias, String dateOfBirth,
				  String email, Board board){
		this.color = color;
		this.alias = alias;
		this.dateOfBirth = dateOfBirth;
		this.email = email;
		this.board = board;
		this.input = new Scanner(System.in);

		movesTab = new int[(board.getBoardSize() * board.getBoardSize()) + 2];
		movesTab[0] = 0; // number of moves are saved in movesTab[0]
		movesItr = 1; // the moves will be saved starting from the 1st index
	}

	public char getColor() {
		return color;
	}

	public String getAlias() {
		return alias;
	}

	public String getDOB() {
		return dateOfBirth;
	}

	public String getEmail() {
		return email;
	}

	public Board getBoard() {
		return board;
	}

	public int[] getMovesTab() {
		return movesTab;
	}

	// nbOfMoves * 2 (coordinates)
	public int getNbOfMoves() {
		return movesTab[0];
	}

	public String getColorName() {
		if (color == Piece.BLACK)
			return "(*) BLACK ";
		else
			return "(o) WHITE ";
	}

	public boolean isWinner() {
		return winner;
	}

	public boolean isFirst() {
		return firstPlayer;
	}

	public boolean isQuitter() {
		return quitter;
	}

	public void setWinner(boolean win) {
		this.winner = win;
	}

	public void setFirstPlayer(boolean first) {
		this.firstPlayer = first;
	}

	public void setQuitter(boolean quit) {
		this.quitter = quit;
	}

	public void setMovesItr(int movesItr) {
		this.movesItr = movesItr;
	}

	public void printMovesTab() {
		for (int i = 0; i < movesItr; i++) {
			System.out.print(" "+movesTab[i]);
		}
	}

	public String toStringPlayer() {
		return alias+'#'+dateOfBirth+'@'+email;
	}

	//change table
	public void modifMovesTab(int pos) {
		int x = Coordinates.calcXCoord(pos, board.getBoardSize());
		int y = Coordinates.calcYCoord(pos, board.getBoardSize());
		movesTab[movesItr++] = x;
		movesTab[movesItr++] = y;
		movesTab[0] +=2;
	}

	public Coordinates enterCoordinates() {
		Coordinates coord;
		int x;
		int y;
		System.out.println("\n" + getColorName() + "player, where do you want to put your piece?");
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

	public char placePiece() {
		char circonstance = 'c';
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
				System.out.println("That spot already has a piece on it");
				while(board.getHex(pos).isFull()){
					coord = enterCoordinates();
					pos = coord.calcPosition(coord.getXCoord(), coord.getYCoord(), board.getBoardSize());
				}
				board.getHex(pos).getPiece().setColor(colorBis);
			}
			board.printBoard();
			//menu
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
					circonstance = 'q'; //save
					ok = false;
				break;
			}
		}while (ok);
		board.printBoard();
		//pour modifier dans le meme temps le graphe cote c;
		modifMovesTab(pos);
		if (InterfaceAvecC.nativePlacePiece(pos, color) == 1) {
			circonstance = 'w'; //win
		}

		return circonstance;
	}

	public static char quiJoue(boolean joueur) {
		return joueur ? Piece.BLACK : Piece.WHITE;
	}

	// public void Menu() {
    //     int choice = 0;
	// 	int ok = 1;
	// 	Coordinates coord = NULL;
	// 	char colorBis = 0;
	//
	// 	if (color == Piece.BLACK) {
	// 		colorBis = 'b';
	// 	}else{
	// 		colorBis = 'w';
	// 	}
	//
	// 	do {
	// 		input.next
	// 		switch (choice) {
	//             case 1 : //entrer des coordonner
	// 				coord = enterCoordinates();
	// 				int pos = coord.calcPosition(coord.getXCoord(), coord.getYCoord(), board.getBoardSize());
	// 				board.getHex(pos).getPiece().setColor(colorBis);
	// 				board.printBoard();
	// 				break;
	//             case 2 :
	//
	//         }
	// 	}while(ok);
	//
    // }

	// public static void main(String[] args) {
	// 	boolean joueur = true;
	// 	// Board board = new Board(5);
	//
	//
	// 	Board board = InterfaceAvecC.nativeInitBoard(5);
	// 	Player b = new Player(Piece.BLACK, "turner", "guy", "guy@truc.com", board);
	// 	Player w = new Player(Piece.WHITE, "miller", "pam", "pam@thing.fr", board);
	//
	// 	board.printBoard();
	//
	// 	Player p;
	// 	int i = 0;
	// 	while(i < board.getNbHexes()){
	// 		char color = quiJoue(joueur);
	//
	// 		if (color == Piece.BLACK)
	// 			p = b;
	// 		else
	// 			p = w;
	//
	// 		p.placePiece();
	// 		p.board.printBoard();
	// 		joueur = !joueur;
	// 	}
	// }
}
