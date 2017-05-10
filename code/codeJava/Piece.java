public class Piece {

	private PieceColor color;

	public static enum PieceColor {
		BLACK, WHITE, EMPTY;
	}

	public Piece(PieceColor color){
		this.color = color;
	}

	public PieceColor getColor(){
		return color;
	}

	public void setColor(PieceColor color){
		this.color = color;
	}

	public String pieceSymbol(){
		if (color == PieceColor.BLACK)
			return "*";
		else if (color == PieceColor.WHITE)
			return "o";
		else
			return ".";
	}
}