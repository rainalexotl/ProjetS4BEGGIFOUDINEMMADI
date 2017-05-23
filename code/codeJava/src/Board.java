/**
 * @class Board
 * @brief Represents the board that the game will be played on
 * @var defaultSize the default size of the hex board is 11 if not specified
 * @var boardSize the size of the board
 * @var hex a table of hexagons
 */
public class Board {
	public static final int defaultSize = 11;
	private int boardSize;
	private Hex[] hex;

	/**
	 * @brief sets the size and the "pieces" of the board
	 * @param boardSize the size of the board, =defaultSize if not entered
	 * @param spots a string that contains the colors of the board
	 */
	public Board(int boardSize, String spots) {
		this.boardSize = boardSize;
		this.hex = new Hex[getNbHexes()];
		for (int i = 0; i < getNbHexes(); i++){
			int x = Coordinates.calcXCoord(i, boardSize);
			int y = Coordinates.calcYCoord(i, boardSize);
			this.hex[i] = new Hex(x, y, spots.charAt(i));
		}
	}

	/**
	 * @return the boardSize the size of the board
	 */
	public int getBoardSize(){
		return boardSize;
	}

	/**
	 * @return the nbHexes the number of hexes on the board (boardSize * boardSize)
	 */
	public int getNbHexes(){
		return boardSize * boardSize;
	}

	/**
	 * @return the hex at the position i of the board
	 */
	public Hex getHex(int i){
		return hex[i];
	}

	/**
	 * @brief prints the board in ascii format
	 * @par Layout
	 * @parblock
	 * W W W W W/B
	 *  B . . . . B
	 *   B . . . . B
	 *    B . . . . B
	 *     B . . . . B
	 *      B/W W W W W
	 * @endparblock
	 */
	public void  printBoard(){
		int i, j;
		
		System.out.println("");

		System.out.print("   ");
		for (i = 0; i < boardSize; i++)
			System.out.print(i + " ");

		System.out.print("\n W");
		for (i = 0; i < boardSize; i++)
			System.out.print(" W");
		System.out.println("/B");

		for (i = 0; i < getNbHexes(); i++){
			if (i%boardSize == 0){
				System.out.print(i / boardSize);
				for (j = 0; j <= i/boardSize; j++){
					System.out.print(".");
				}
				System.out.print("B");
			}
			System.out.print(" " + hex[i].getPiece().getColor());

			if(i%boardSize == boardSize - 1)
				System.out.println(" B");
		}

		for (j = 0; j <= i/boardSize; j++)
			System.out.print(" ");

		System.out.print(" B/");
		for (i = 0; i <= boardSize; i++)
			System.out.print("W ");

		System.out.println("");
	}

	/**
	 * @return the board in string from
	 */
	public String convertBoardToString(){
		String str = "";
		int i;
		for (i = 0; i < boardSize * boardSize; i++){
			str += hex[i].getPiece().getColor();
		}
		return str;
	}
}
