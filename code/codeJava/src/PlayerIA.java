

public class PlayerIA extends Player {

    public PlayerIA(Board board) {
        // Date date = new Date();
        super(Piece.BLACK, "IA", new Date(23, 5, 17), "angelodelagx@gmail.com", board);
    }

    public char placePiece() {
		char event = 'c';
		int pos = -1;

		pos = InterfaceAvecC.nativeMiniMax();
		getBoard().getHex(pos).getPiece().setColor(Piece.BLACK);

		getBoard().printBoard();
		modifMovesTab(pos);

		if (InterfaceAvecC.nativePlacePiece(pos, Piece.BLACK) == 1) {
			event = 'w';
		}
		return event;
	}

}
