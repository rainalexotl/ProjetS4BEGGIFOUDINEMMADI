public class Hex {
	//a spot on the board

	private Coordinates coord;
	private boolean pleine;
	private Piece piece;

	public Hex(int x, int y, Piece.PieceColor piece){
		this.coord = new Coordinates(x, y);
		// this.piece = new Piece(Piece.PieceColor.EMPTY);
		// this.piece = new Piece(piece);
		this.piece = InterfaceAvecC.nativeInitPiece(piece);
		this.pleine = false;
	}

	public Coordinates getCoord(){
		return coord;
	}

	public boolean isFull(){
		if (piece.getColor() != Piece.PieceColor.EMPTY)
			pleine = true;
		else
			pleine = false;
		return pleine;
	}

	public Piece getPiece(){
		return piece;
	}
}