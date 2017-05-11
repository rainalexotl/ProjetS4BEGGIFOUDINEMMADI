public class Hex {
	//a spot on the board

	private Coordinates coord;
	private boolean pleine;
	private Piece piece;

	public Hex(int x, int y, char piece){
		this.coord = new Coordinates(x, y);
		// this.piece = new Piece(piece);

		
		this.piece = InterfaceAvecC.nativeInitPiece(piece);
		this.pleine = false;
	}

	public Coordinates getCoord(){
		return coord;
	}

	public boolean isFull(){
		if (piece.getColor() != Piece.EMPTY)
			pleine = true;
		else
			pleine = false;
		return pleine;
	}

	public Piece getPiece(){
		return piece;
	}
}
