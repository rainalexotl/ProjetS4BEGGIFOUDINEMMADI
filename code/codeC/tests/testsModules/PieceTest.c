#include "../../src/ReducedGraph.h"



int main(int argc, const char * argv[]) {
	printf("*********************************\n");
	printf("*       Tests for the Piece     *\n");
	printf("*********************************\n");
	Piece piece = createPiece(BLACK);
	printf("This is your piece\n");
	printf("The colar of the Piece is  : %c\n",piece.color);
    printf("The coodinates of the Piece are x = %d & y = %d\n",piece.coord.x,piece.coord.y);

}
