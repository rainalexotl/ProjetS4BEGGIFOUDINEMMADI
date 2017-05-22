/**
 * @class Coordinates
 * @brief represents the coordinates of a hex on the board
 */
public class Coordinates {

	private int x;
	private int y;

	/**
	 * @param x the x coordinate
	 * @param y the y coordinate
	 */
	public Coordinates(int x, int y){
		this.x = x;
		this.y = y;
	}

	/**
	 * @return the x coordinate
	 */
	public int getXCoord(){
		return x;
	}

	/**
	 * @return the y coordinate
	 */
	public int getYCoord(){
		return y;
	}

	/**
	 * @param i an index on the board
	 * @param boardSize the size of the board
	 * @return an x coordinate from an index i and the boardSize
	 */
	public static int calcXCoord(int i, int boardSize) {
		return InterfaceAvecC.nativeCalcXCoord(i, boardSize);
	}

	/**
	 * @param i an index on the board
	 * @param boardSize the size of the board
	 * @return an y coordinate from an index i and the boardSize
	 */
	public static int calcYCoord(int i, int boardSize) {
		return InterfaceAvecC.nativeCalcYCoord(i, boardSize);
	}

	/**
	 * @param x coordinate
	 * @param y coordinate
	 * @param boardSize the size of the board
	 * @return the i index calculated from an x and y coordinate and the size
	 */
	public int calcPosition(int x, int y, int boardSize) {
		return InterfaceAvecC.nativeCalcPosition(x, y, boardSize);
	}
}
