import java.util.*;
import java.text.*;


public class PlayerIA extends Player {

    public SimpleDateFormat ft = new SimpleDateFormat("dd/MM/yy");
    
    public PlayerIA(Board board) {
        super(Piece.BLACK, "IA", new Date(), "angelodelagx@gmail.com", board);
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
