/**
 * @class Piece
 * @brief represents a piece on to be put on a hex
 */
public class Piece {


	public static final char BLACK = '*'; //! a black piece on the board
	public static final char WHITE = 'o'; //! a white piece on the board
	public static final char EMPTY = '.'; //! an empty piece on the board

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
