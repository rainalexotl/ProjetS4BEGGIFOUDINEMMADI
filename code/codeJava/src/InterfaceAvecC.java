public class InterfaceAvecC {

	static {
		System.load("/Users/Angelo/Desktop/ProjetHex/ProjetS4BEGGIFOUDINEMMADI/code/lib/libInterfaceAvecC.dylib");
	}

	//! calls the play method in Java
	public static native char nativeInitGame(String spots, JeuHex jeu);

	//! calculates the x coordinate of a position i
	public static native int nativeCalcXCoord(int i, int boardSize);

	//! calculates the y coordinate of a position i
	public static native int nativeCalcYCoord(int i, int boardSize);

	//! calculates the position of a Hex at (x, y)
	public static native int nativeCalcPosition(int x, int y, int boardSize);

	//! replaces a piece in the graph and checks for a winning group
	public static native int nativePlacePiece(int pos, char color);

	//! gets the spots of the board from a file called fileName
	public static native String nativeGetSpots(String fileName);

	//! calls the c function saveBoardFile() in order to right a save file of a game
	public static native void nativeSaveGame(String savedFileName, String stringToSave, int[] bMovesTab, int[] wMovesTab);

	//! calls the c function savePlayer() in order to save the player information in a file
	public static native void nativeSavePlayer(String nameOfSavePlayer, String bPlayer, String wPlayer);

	//! loads a player's previously saved information with the c function loadPlayer()
	public static native String nativeStringToLoadPlayer(char color, String loadFileName);

	//! calls the c function getSaveFiles() and gets all the names of the previously saved files
	public static native String [] nativeGetSaveFile();

	public static native int nativeMiniMax();
}
