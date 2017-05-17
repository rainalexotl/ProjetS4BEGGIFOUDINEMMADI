// package interfaceC;

public class Board {
	public static final int defaultSize = 11;
	private int boardSize; //board dimension
	// private int nbHexes;
	private Hex[] hex; //table of hexagons

	//if not entered boardSize will be the defaultSize;
	public Board(int boardSize, String spots){
		this.boardSize = boardSize;
		// this.nbHexes = boardSize * boardSize;
		this.hex = new Hex[getNbHexes()];
		for (int i = 0; i < getNbHexes(); i++){
			 int x = Coordinates.calcXCoord(i, boardSize);
			 int y = Coordinates.calcYCoord(i, boardSize);
			 this.hex[i] = new Hex(x, y, spots.charAt(i));
			//this.hex[i] = InterfaceAvecC.nativeInitHex(x, y, spots.charAt(i));
		}
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

	//retourne un string à partir du graphe
	public String convertBoardToString() {
		String str ="";
		int i;
		for (i = 0; i < boardSize*boardSize; i++) {
			str += hex[i].getPiece().getColor();
		}
		return str;
	}

	// public static void main(String[] args) {
	// 	//Board b = new Board(defaultSize);
	// 	//b.printBoard();
	// }
}
