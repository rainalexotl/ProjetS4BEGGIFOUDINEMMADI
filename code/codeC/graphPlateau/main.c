// //
// //  main.c
// //
// //
// //  Created by Mmadi.anzilane on 14/04/2017.
// //  Copyright © 2017 Mmadi.anzilane. All rights reserved.
// //
//
// #include <stdio.h>
// //#include "Graph.h"
// #include "ReducedGraph.h"
// int main(int argc, const char * argv[]) {
//     Graph g = CreateGraph(4);
//     char * str = transformGraphToBoardOfChar("../../../config/size4.txt");
//     g = CreateBoardGraph(g, str);
//     postUpBoard(g);
//
//     TabHash * tabHBlack = createTabHashRg(getNbVertexGraph(g));
//     TabHash * tabHWhite = createTabHashRg(getNbVertexGraph(g));
//     bool joueur = true;
//     int i = 0;
//     int stop = 0;
//     Piece p;
//     int pos;
//     g->s[15]->color = '*';
//     g->s[15]->color = 'o';
//     postUpBoard(g);
//     postUpSideAdjacentGraph(g);
//     while (i < getNbVertexGraph(g) && stop == 0){
//         if (joueur){
//             p = createPiece(BLACK);
//             pos = calculateSquareCoordinates(p.coord.x, p.coord.y, getsizeGraph(g));
//             replaceVertexGraph(g, pos, BLACK);
//             printf("position du sommet adjacent des sommet \n");
//             postUpPositionAdjacentVertex(pos, g);
//             stop = searchGroup(tabHBlack, g, pos, BLACK);
//         }else {
//             p = createPiece(WHITE);
//             pos = calculateSquareCoordinates(p.coord.x, p.coord.y, getsizeGraph(g));
//             replaceVertexGraph(g, pos, WHITE);
//             printf("position du sommet adjacent des sommet \n");
//             postUpPositionAdjacentVertex(pos, g);
//             stop = searchGroup(tabHWhite, g, pos, WHITE);
//         }
//         postUpBoard(g);
//         joueur = !joueur;
//         i++;
//     }
//
//     if (stop){
//         printf("groupe gagnant trouvé\nvaleur de stop = %d\n", stop);
//     }
//
//     return 0;
// }
