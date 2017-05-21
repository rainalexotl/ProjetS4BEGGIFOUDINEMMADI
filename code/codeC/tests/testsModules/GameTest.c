#include "../../src/ReducedGraph.h"
//
//
//typedef struct sGraph * Graph;
//
int main(int argc, const char * argv[]) {
	//*************************Test prototype Game****************
	printf("*********************************\n");
	printf("*         You can play          *\n");
	printf("*********************************\n");
	 bool joueur = true;
     int i = 0;
     int stop = 0;
     Piece p;
     int pos;
	 printf("this is a test for Creation fonctions\n");
	 Graph g = createGraph(4);
	 int loaded=0;
     char * str = getSpotsFromFile("../../../../doc/config/size4.txt");
     g = createBoardGraph(g, str, &loaded);
	 printBoard(g);
     TabHash * tabHBlack = createTabHashRg(getNbVertexGraph(g));
     TabHash * tabHWhite = createTabHashRg(getNbVertexGraph(g));
     printf("this is a test for modification fonctions\n");
     while (i < getNbVertexGraph(g) && stop == 0){
         if (joueur){
		    
             p = createPiece(BLACK);
             assert(p.coord.x < getSizeGraph(g) && p.coord.y <getSizeGraph(g));
             pos = calculateHexCoordinates(p.coord.x, p.coord.y, getSizeGraph(g));
             if(g->v[pos]->color == EMPTY ){
			 replaceVertexGraph(g, pos, BLACK);
             printVertexAdjPositions(pos, g);
             stop = searchGroup(tabHBlack, g, pos, BLACK);			 
			 }

         }else {
             p = createPiece(WHITE);
             assert(p.coord.x < getSizeGraph(g) && p.coord.y <getSizeGraph(g));
             pos = calculateHexCoordinates(p.coord.x, p.coord.y, getSizeGraph(g));
             if(g->v[pos]->color == EMPTY ){
			 replaceVertexGraph(g, pos, WHITE);
             printVertexAdjPositions(pos, g);
             stop = searchGroup(tabHWhite, g, pos, WHITE);
            }
         }
         printBoard(g);
         joueur = !joueur;
         i++;
     }

     if (stop){
         printf("groupe gagnant trouve avec valeur de stop = %d\n", stop);
     }

     return 0;
     
}
