 //
 // main.c
 //
 //
 // Created by Mmadi.anzilane on 14/04/2017.
 // Copyright © 2017 Mmadi.anzilane. All rights reserved.


#include <stdio.h>
//#include "Graph.h"
#include "ReducedGraph.h"
int main(int argc, const char * argv[]) {
    int i;
    Graph g = createGraph(4);
    char * str = getSpotsFromFile("../../../doc/config/size4.txt");
    g = createBoardGraph(g, str, &i);
    printf("i = %d\n", i);
    printBoard(g);

    char * player = loadPlayer('o', "../../../doc/SaveFiles/savePlayer/playerparti1.txt");
    printf("player %s\ntaille %d \n", player, (int)strlen(player));

    free(player);
    int k = 0;
    char ** saveFiles = getSaveFiles(argv[1], &k);
    for (int j = 0; j < k; j++) {
        printf("fils %d : %s\n", j, saveFiles[j]);
    }
    free(str);
    free(player);

    printf("player %s\n", player);

    destroySaveFiles(saveFiles);
    ReducedGraph * rg = createReducedGraph(g);
    destroyReducedGraph(rg);
    destroyGraph(g);
    //
    //
    //
    // TabHash * tabHBlack = createTabHashRg(getNbVertexGraph(g));
    // TabHash * tabHWhite = createTabHashRg(getNbVertexGraph(g));
    // bool joueur = true;
    // int i = 0;
    // int stop = 0;
    // Piece p;
    // int pos;
    // g->s[15]->color = '*';
    // g->s[15]->color = 'o';
    // postUpBoard(g);
    // postUpSideAdjacentGraph(g);
    // while (i < getNbVertexGraph(g) && stop == 0){
    //     if (joueur){
    //         p = createPiece(BLACK);
    //         pos = calculateSquareCoordinates(p.coord.x, p.coord.y, getsizeGraph(g));
    //         replaceVertexGraph(g, pos, BLACK);
    //         printf("position du sommet adjacent des sommet \n");
    //         postUpPositionAdjacentVertex(pos, g);
    //         stop = searchGroup(tabHBlack, g, pos, BLACK);
    //     }else {
    //         p = createPiece(WHITE);
    //         pos = calculateSquareCoordinates(p.coord.x, p.coord.y, getsizeGraph(g));
    //         replaceVertexGraph(g, pos, WHITE);
    //         printf("position du sommet adjacent des sommet \n");
    //         postUpPositionAdjacentVertex(pos, g);
    //         stop = searchGroup(tabHWhite, g, pos, WHITE);
    //     }
    //     postUpBoard(g);
    //     joueur = !joueur;
    //     i++;
    // }
    //
    // if (stop){
    //     printf("groupe gagnant trouvé\nvaleur de stop = %d\n", stop);
    // }

    return 0;
}
