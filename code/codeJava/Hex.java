public class Hex {
	//a spot on the board

	private Coordinates coord;
	private boolean full;
	private Piece piece;

	public Hex(int x, int y, char piece){
		this.coord = new Coordinates(x, y);
	 	this.piece = new Piece(piece);
		this.full = false;
	}

	public Coordinates getCoord(){
		return coord;
	}

	public Piece getPiece(){
		return piece;
	}

	public boolean isFull(){
		if (piece.getColor() != Piece.EMPTY)
			full = true;
		else
			full = false;
		return full;
	}
}
