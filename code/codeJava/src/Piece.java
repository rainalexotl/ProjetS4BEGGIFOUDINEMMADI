/**
 * @class Piece
 * @brief represents a piece on to be put on a hex
 * @var BLACK representative constant of a black piece (*)
 * @var WHIITE representative constant of  a black piece (o)
 * @var EMPTY representative constant of an empty piece (.)
 */
public class Piece {


	public static final char BLACK = '*';
	public static final char WHITE = 'o';
	public static final char EMPTY = '.';

	private char color;
	
	/**
	 * @brief asigns a color to a piece
	 * @param color the color of the piece 
	 */
	public Piece(char color){
		this.color = color;
	}

	/**
	 * @return the color of the piece
	 */
	public char getColor(){
		return color;
	}

	/**
	 * @brief sets the color of a piece
	 */
	public void setColor(char color){
		this.color = color;
	}
}
