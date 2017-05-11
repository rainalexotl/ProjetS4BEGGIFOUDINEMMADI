// package interfaceC;

public class Coordinates {

	private int x;
	private int y;

	public Coordinates(int x, int y){
		this.x = x;
		this.y = y;
	}

	public int getXCoord(){
		return x;
	}

	public int getYCoord(){
		return y;
	}

	public static int calcXCoord(int i, int boardSize){
		// return i/boardSize;

		return InterfaceAvecC.nativeCalcXCoord(i, boardSize);
	}

	public static int calcYCoord(int i, int boardSize){
		// return i%boardSize;

		return InterfaceAvecC.nativeCalcYCoord(i, boardSize);
	}

	public int calcPosition(int x, int y, int boardSize){
		// return boardSize * x + y;
		
		return InterfaceAvecC.nativeCalcPosition(x, y, boardSize);
	}
}
