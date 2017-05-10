// package interfaceC;

public class InterfaceAvecC {

	static {
		System.loadLibrary("InterfaceAvecC");
	}

	public static native Piece nativeInitPiece(char color);
	public static native Hex nativeInitHex(int x, int y, char piece);
	public static native Board nativeInitBoard(int boardSize);
	public static native int nativeCalcXCoord(int i, int boardSize);
	public static native int nativeCalcYCoord(int i, int boardSize);
	public static native int nativeCalcPosition(int x, int y, int boardSize);
}
