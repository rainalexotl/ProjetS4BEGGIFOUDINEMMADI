// package interfaceC;

public class InterfaceAvecC {

	static {
		System.load("/Users/Angelo/Desktop/ProjetHex/ProjetS4BEGGIFOUDINEMMADI/code/lib/libInterfaceAvecC.dylib");
	}

	//public static native Piece nativeInitPiece(char color);
	//public static native Hex nativeInitHex(int x, int y, char piece);
	//public static native Board nativeInitBoard(int boardSize, String spots);
	public static native char nativeInitGame(String spots, JeuHex jeu);
	public static native int nativeCalcXCoord(int i, int boardSize);
	public static native int nativeCalcYCoord(int i, int boardSize);
	public static native int nativeCalcPosition(int x, int y, int boardSize);
	public static native int nativePlacePiece(int pos, char color);
	public static native String nativeGetSpots(String fileName);
	public static native void nativeSaveGame(String savedFileName, String stringToSave, int[] bMovesTab, int[] wMovesTab);
	public static native void nativeSavePlayer(String nameOfSavePlayer, String bPlayer, String wPlayer);
	public static native String nativeStringToLoadPlayer(char color, String loadFileName);
	public static native String [] nativeGetSaveFile();
}
