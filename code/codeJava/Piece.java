public class Piece {

	public static final char BLACK = '*';
	public static final char WHITE = 'o';
	public static final char EMPTY = '.';

	private char color;
	
	public Piece(char color){
		this.color = color;
	}

	public char getColor(){
		return color;
	}

	public void setColor(char color){
		this.color = color;
	}
}
