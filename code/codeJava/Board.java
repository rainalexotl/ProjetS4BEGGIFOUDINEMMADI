// package interfaceC;

public class Board {
	public static final int defaultSize = 11;
	private int boardSize; //board dimension
	private Hex[] hex; //table of hexagons

	//if not entered boardSize will be the defaultSize;
	public Board(int boardSize, String spots){
		this.boardSize = boardSize;
		this.hex = new Hex[getNbHexes()];
		for (int i = 0; i < getNbHexes(); i++){
			int x = Coordinates.calcXCoord(i, boardSize);
			int y = Coordinates.calcYCoord(i, boardSize);
			this.hex[i] = new Hex(x, y, spots.charAt(i));
		}
	}

	public int getBoardSize(){
		return boardSize;
	}

	//number of hexagons on board (boardSize * boardSize)
	public int getNbHexes(){
		return boardSize * boardSize;
	}

	public Hex getHex(int i){
		return hex[i];
	}

	public void  printBoard(){
		int i, j;
		System.out.print("W");
		for (i = 0; i < boardSize; i++)
			System.out.print(" W");
		System.out.println("/B");

		for (i = 0; i < getNbHexes(); i++){
			if (i%boardSize == 0){
				for (j = 0; j <= i/boardSize; j++){
					System.out.print(" ");
				}
				System.out.print("B");
			}
			System.out.print(" " + hex[i].getPiece().getColor());

			if(i%boardSize == boardSize - 1)
				System.out.println(" B");
		}

		for (j = 0; j <= i/boardSize; j++)
			System.out.print(" ");

		System.out.print("B/");
		for (i = 0; i <= boardSize; i++)
			System.out.print("W ");

		System.out.println("");
	}

	//returns a board in string form
	public String convertBoardToString(){
		String str ="";
		int i;
		for (i = 0; i < boardSize * boardSize; i++){
			str += hex[i].getPiece().getColor();
		}
		return str;
	}
}
