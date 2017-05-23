#include "TreeOfGameIA.h"
#include <time.h>
#include <string.h>
#include <assert.h>
// srand(time(NULL)); // initialisation de rand


int  hasList(const TabHash *tabH, int side1, int side2, int sizeTabH);
//on passe une copie car on ne veux rien modifier
int minimax(Graph gbis, int profondeur) {

    int val_max = -1;
    int val_tmp, pos = 0;

    for (int i = 0; i < getNbVertexGraph(gbis); i++) {
        if (gbis->v[i]->color == EMPTY) {
            gbis->v[i]->color = BLACK; //because I choose IA is BLACK
            val_tmp = min(gbis, profondeur-1);
            if(val_tmp > val_max || ((val_tmp == val_max) && (rand()%2 == 0))) {
                val_max = val_tmp;
                pos = i;
            }

            gbis->v[i]->color = EMPTY;
        }
    }
    return pos;
}



int min(const Graph gbis, int profondeur) {

    int IA = 0; int ADV = 0;int bestGroup;
    if (profondeur == 0 || endGame(gbis, &IA, &ADV,&bestGroup) != 0) {
        return heuristique(gbis);
    }
    int val_min = 1;
    int val_tmp = 0;

    for (int i = 0; i < getNbVertexGraph(gbis); i++) {
        if (gbis->v[i]->color == EMPTY) {
            gbis->v[i]->color = WHITE;
            val_tmp = max(gbis, profondeur-1);
            if(val_tmp < val_min || ((val_min == val_tmp) && (rand()%2 == 0))) { //ne pas oublier d'include le randome
                val_min = val_tmp;
            }
            //restoration
            gbis->v[i]->color = EMPTY;
        }
    }
    return val_min;
}

int max(Graph gbis, int profondeur) {
    int IA = 0; int ADV = 0;
    int bestGroup;
    if (profondeur == 0 || endGame(gbis, &IA, &ADV,&bestGroup) != 0) {
        return heuristique(gbis);
    }

    int val_max = -1;
    int val_tmp;
    for (int i = 0; i < getNbVertexGraph(gbis); i++) {
        if (gbis->v[i]->color == EMPTY) {
            gbis->v[i]->color = BLACK;
            val_tmp = min(gbis, profondeur-1);
            if(val_tmp > val_max || ((val_max == val_tmp) && (rand()%2 == 0))) { //ne pas oublier d'include le randome
                val_max = val_tmp;
            }
            //restoration
            gbis->v[i]->color = EMPTY;
        }
    }
    return val_max;
}


//s'il y' a un gagnant
int endGame(const Graph g, int *IA, int *ADV , int *bestGroup) {
    Graph gbis = newGrpah(g);
    int sizeTab = getNbVertexGraph(gbis);
    TabHash * blackHashTab = createTabHashRg(sizeTab);
    TabHash * whiteHashTab = createTabHashRg(sizeTab);

    for (int i = 0; i < getNbVertexGraph(gbis); i++) {
        if (gbis->v[i]->color != EMPTY) {
            if (gbis->v[i]->color == BLACK) {
                if (searchGroup(blackHashTab, gbis, i, BLACK) == 1) {
                    return 1;
                }
            }else {
                if (searchGroup(whiteHashTab, gbis, i, WHITE) == 1) {
                    return -1;
                }
            }
        }
    }
    //retourne 0 si ils sont pareils sinon 1 pour le black , 2 pour le white qui est le mieux

    int side1B = getB1Graph(getSizeGraph(gbis));
    int side2B = getB2Graph(getSizeGraph(gbis));
    int side1W = getW1Graph(getSizeGraph(gbis));
    int side2W = getW2Graph(getSizeGraph(gbis));
    int black = hasList(blackHashTab,side1B,side2B,sizeTab);
    int white = hasList(whiteHashTab,side1W,side2W,sizeTab);

    if (black == 0 || white == 0 || black == white ){
        *bestGroup = 0;
    }else if (black > white ) {
        *bestGroup = 1;
    }else if (black < white ) {
        *bestGroup = 2;
    }

    *IA = blackHashTab->nbGroups;
    *ADV = whiteHashTab->nbGroups;
    destroyTabHash(blackHashTab, getNbVertexGraph(gbis));
    destroyTabHash(whiteHashTab, getNbVertexGraph(gbis));
    destroyGraph(gbis);
    return 0;
}

int heuristique(const Graph g) {
    Graph gbis = newGrpah(g);
    int nbGroupIA = 0; int nbGroupADV;

    int win = 0;
    int bestGroup;
    if ((win = endGame(gbis, &nbGroupIA, &nbGroupADV,&bestGroup)) != 0) {
        if (win == 1) {
            destroyGraph(gbis);
            return 1;
        }else {
            destroyGraph(gbis);
            return -1;
        }
    }
    destroyGraph(gbis);
    //printf("le best group est %d\n",bestGroup);
//    if (nbGroupIA < nbGroupADV && bestGroup == 2 ) {
//        return -1;
//    }else if (nbGroupIA < nbGroupADV && bestGroup == 1){
//        return 1;
//    }else if (nbGroupIA > nbGroupADV && bestGroup == 2){
//        return -1;
//    }else{
//        return 1;
//    }
    if (bestGroup == 1) {
        return 1;
    }else if (bestGroup == 2) {
        return -1;
    }else {
        if (nbGroupADV <= nbGroupIA) {
            return 1;
        }else {
            return -1;
        }
    }
}

bool hasSide(List *l , int side1, int side2 ){
    Node *itr = l->sent;
    while (itr->next != l->sent) {
        if (itr->next->pos == side1  || itr->next->pos == side2 )
            return true;
        assert(itr->next);
        itr = itr->next;
    }
    return false;
}

int hasList(const TabHash *tabH, int side1, int side2, int sizeTabH) {
    int j = 0;
    for (int i = 0; i < sizeTabH ; i++) {
        if (tabH->groupList[i] != NULL) {
            if (hasSide(tabH->groupList[i],side1,side2 )) {
                j++;
            }
        }
    }
    return j;
}

Graph newGrpah(const Graph g) {
    Graph gbis = createGraph(getSizeGraph(g));
    for (int i = 0; i < getNbVertexGraph(g); i++) {
        gbis->v[i] = insertVertexGraph(gbis, i, g->v[i]->color);
    }
    calcAllAdjacentsGraph(gbis);
    return gbis;
}
