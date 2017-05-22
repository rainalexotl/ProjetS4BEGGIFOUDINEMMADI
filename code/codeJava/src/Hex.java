/**
 * @class Hex
 * @brief represents a hex on the board
 * @var coord coordinates of the hex
 * @var full boolean that shows if the hex has a piece or not
 * @var the piece that is on the hex
 */
public class Hex {
	private Coordinates coord; 
	private boolean full;
	private Piece piece; 

	/**
	 * @brief sets the coordinates of a hex and sets its full boolean at false
	 * @param x its x coordinate
	 * @param y its y coordinate
	 * @param piece the piece thats on the hex spot
	 */
	public Hex(int x, int y, char piece){
		this.coord = new Coordinates(x, y);
	 	this.piece = new Piece(piece);
		this.full = false;
	}

	/**
	 * @return the coordinates of the hex
	 */
	public Coordinates getCoord(){
		return coord;
	}

	/**
	 * @return the piece on the hex spot
	 */
	public Piece getPiece(){
		return piece;
	}

	/**
	 * @return true if the hex has a piece on it
	 */
	public boolean isFull(){
		if (piece.getColor() != Piece.EMPTY)
			full = true;
		else
			full = false;
		return full;
	}
}
