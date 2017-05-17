// package interfaceC;

public class InterfaceAvecC {

	static {
		System.load("/home/manzilane/Documents/ProjetS4/ProjetS4BEGGIFOUDINEMMADI/code/lib/libInterfaceAvecC.so");
	}

	//public static native Piece nativeInitPiece(char color);
	//public static native Hex nativeInitHex(int x, int y, char piece);
	//public static native Board nativeInitBoard(int boardSize, String spots);
	public static native int nativeInitGame(String spots, JeuHex jeu);
	public static native int nativeCalcXCoord(int i, int boardSize);
	public static native int nativeCalcYCoord(int i, int boardSize);
	public static native int nativeCalcPosition(int x, int y, int boardSize);
	public static native void nativePlacePiece(int pos, char spots);
	public static native String nativeGetSpots(String fileName);
	public static native void nativeSaveGame(String savedFileName, String StringToSave, int[]BTabGame, int[]WTabGame);
	public static native void nativeSavePlayer(String nameOfSavePlayer, String Bplayer, String Wplayer);
	public static native String nativeStringToLoadPlayer(char color, String stringFromFilInC);
	public static native String [] nativeGetSaveFile();
}
