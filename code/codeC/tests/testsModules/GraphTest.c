#include "../../src/ReducedGraph.h"

int main(int argc, const char * argv[]) {
	Graph g = createGraph(8);
	int loaded = 0;
	int pos;
	Piece p;
	
	printf("*********************************\n");
	printf("*      Tests for the Graph      *\n");
	printf("*********************************\n");
	
	char * str = getSpotsFromFile("../../../../doc/config/size8.txt");
     g = createBoardGraph(g, str, &loaded);
     printf("This is a creation a graph size 8\n");
	 printBoard(g);
	 
	 printf("Now we can insert a vertex in this board\n");
	 
	 p = createPiece(BLACK);
     assert(p.coord.x < getSizeGraph(g) && p.coord.y < getSizeGraph(g));
     pos = calculateHexCoordinates(p.coord.x, p.coord.y, getSizeGraph(g));
     replaceVertexGraph(g, pos, BLACK);
     printf("This is the new board\n");
     printBoard(g);
     
     printf("We can calculate a vertex neighbors\n");
     printf("For example choose a position board  : 8*8\n");
     scanf("%d",&pos);
     calcAdjacentVertexesGraph(g->v[pos],g);
     printf("The neignbors of this vertex pos = %d are \n",pos);
     printVertexAdjPositions(pos,g);
     
}
