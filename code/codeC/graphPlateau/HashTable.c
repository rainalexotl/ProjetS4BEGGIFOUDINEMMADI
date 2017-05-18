//
//  HashTable.h
//  HashTable
//
//  Created by Mmadi.anzilane on 14/04/2017.
//  Copyright © 2017 Mmadi.anzilane. All rights reserved.
//
#include "HashTable.h"
/*-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------*/
                            //implement TAD TabHash
/*-----------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------*/
                            //Create Fonctions
/*-----------------------------------------------------------------------------*/
TabHash * createTabHashRg(int sizeTab) {
    TabHash *tabH = malloc(sizeof(TabHash));
    tabH->nbGroups = 0;
    tabH->boardListGroup = malloc(sizeof(List*)*sizeTab);
    for (int i = 0; i < sizeTab; ++i) { //a voir s'il faut initialiser ou pas
        tabH->boardListGroup[i] = NULL; //createList();
    }
    return tabH;
}

int HashCode(const List *group) {
    assert(group);
    return group->sent->next->pos;
}
TabHash * hashFonctionRg(TabHash* tabH, List *group) {
    int hashCode = HashCode(group);
    if ((*tabH).boardListGroup[hashCode] == NULL) {
        printf("je passe dans le if\n");
        (*tabH).boardListGroup[hashCode] = group;
        tabH->nbGroups++;
    }else {
        printf("je passe dans le else\n");
        (*tabH).boardListGroup[hashCode] = group;
    }
    printf("nombre d'element dans le tableau %d\n", tabH->nbGroups);
    return tabH;
}

/*-----------------------------------------------------------------------------*/
                            //Modify Fonctions
/*-----------------------------------------------------------------------------*/
void freeTabHash(TabHash * tabH, int sizeTab) {
    for (size_t i = 0; i < sizeTab; i++) {
        if (tabH->boardListGroup[i]) {
            destroyList(tabH->boardListGroup[i]);
        }
    }
    tabH = NULL;
    free(tabH);
}

/*******************************************************************************/
                            //implement Search group
/*******************************************************************************/
void modifyLeaderOfVertex(Graph g, int pos, int newLeader) {
    assert(g->s[pos] && g);
    g->s[pos]->theLeaderOfGroup = newLeader;
    if (!isInGroup(g->s[pos])) { //isn't in group now he is
        g->s[pos]->isInGroup = 1;
    }
}
//Graph g to modify the leader the group
List *groupUnion(List *g1, List *g2, Graph g) {
    int leaderOfGroup = g1->sent->next->pos;
    Node * itr = g2->sent->next;
    while (itr != g2->sent) {
        modifyLeaderOfVertex(g, itr->pos, leaderOfGroup);
        g1 = pushBack(g1, itr->pos);
        assert(itr->next);
        itr = itr->next;
    }
    destroyList(g2); // because we dont use that
    printf("affichage du groupe apres union\n");
    printList(g1);
    return g1;
}

//v1 and v2 are the positions of vertexs
//v1 is the leader of the new group
List *createNewGroup(Graph g, int v1, int v2) {
    modifyLeaderOfVertex(g, v1, v1); //because it's the leader
    modifyLeaderOfVertex(g, v2, v1);
    List * newGroupe = createList();
    newGroupe = pushBack(newGroupe, v1);
    newGroupe = pushBack(newGroupe, v2);
    return newGroupe;
}

//put a alone vertex in a  group
List * putItInGroup(List *group, int v, Graph g) {
    assert(group->sent->next);
    int leaderOfGroup = group->sent->next->pos;
    modifyLeaderOfVertex(g, v, leaderOfGroup);
    group = pushBack(group, v);
    return group;
}

//thougnt to create a alias
bool searchGroup(TabHash *tabH, Graph g, int pos, char color) {
    int side1, side2;
    if (color == BLACK){
        side1 = getB1Graph(getsizeGraph(g));
        side2 = getB2Graph(getsizeGraph(g));
    }else{
        side1 = getW1Graph(getsizeGraph(g));
        side2 = getW2Graph(getsizeGraph(g));
    }
    List * newGroupe = NULL;
    int posAdj = -1;
    Vertex * vAdj = NULL;
    Vertex * v = NULL;
    assert(g->s[pos]);
    v = g->s[pos]; //we create alias
    bool winningGroup = false;
    for (int i = 0; i < MAXVOISIN; i++) { //I put 6 just to try
        //assert(v->Adjacents[i]); //I test if it's
        vAdj = v->Adjacents[i]; // we create alias
        if (vAdj != NULL) {
            if (areVertexAdjacent(v ,vAdj)) { //main condition
                if (isInGroup(vAdj) && isInGroup(v)) {
                    if (!isInSameGroup(v, vAdj)) {
                        if (whichIsLargestGroup(tabH, v->theLeaderOfGroup, vAdj->theLeaderOfGroup) == 1 ) {
                            newGroupe = groupUnion(tabH->boardListGroup[(v->theLeaderOfGroup)], tabH->boardListGroup[(vAdj->theLeaderOfGroup)], g);
                        }else {
                            newGroupe = groupUnion(tabH->boardListGroup[(vAdj->theLeaderOfGroup)], tabH->boardListGroup[(v->theLeaderOfGroup)], g);
                        }
                        tabH = hashFonctionRg(tabH, newGroupe);
                    }//else is in the same group so, we don't do nothing
                }else if (!isInGroup(vAdj) && isInGroup(v)) { //isn't in group but they are Adjacents
                    posAdj = calculateSquareCoordinates(vAdj->coord.x, vAdj->coord.y, getsizeGraph(g));
                    tabH->boardListGroup[(v->theLeaderOfGroup)] = putItInGroup(tabH->boardListGroup[(v->theLeaderOfGroup)], posAdj, g);
                    newGroupe = tabH->boardListGroup[(v->theLeaderOfGroup)];
                }else if (isInGroup(vAdj) && !isInGroup(v)){
                    tabH->boardListGroup[vAdj->theLeaderOfGroup] = putItInGroup(tabH->boardListGroup[vAdj->theLeaderOfGroup], pos, g);
                    newGroupe = tabH->boardListGroup[vAdj->theLeaderOfGroup];
                }else {
                    posAdj = calculateSquareCoordinates(vAdj->coord.x, vAdj->coord.y, getsizeGraph(g));
                    newGroupe = createNewGroup(g, pos, posAdj);
                    tabH = hashFonctionRg(tabH, newGroupe);
                }
            }
        }
    }
    if (newGroupe != NULL)
            printList(newGroupe);
    if (IsAWinGroup(newGroupe, side1, side2)) {
        winningGroup = true;
    }
    return winningGroup;
}
/*-----------------------------------------------------------------------------*/
                            //Observation Fonctions
/*-----------------------------------------------------------------------------*/
//To find out which is the largest group between two groups
bool whichIsLargestGroup(const TabHash *tabH, int leader1, int leader2) {
    printf("leader1 size = %d, leader2 size = %d\n", tabH->boardListGroup[leader1]->sizeList, tabH->boardListGroup[leader2]->sizeList);
    //because they can't have a same leader
    //assert(tabH->boardListGroup[leader1]->sizeList == tabH->boardListGroup[leader2]->sizeList);
    if (tabH->boardListGroup[leader1]->sizeList >= tabH->boardListGroup[leader2]->sizeList){
        return true;
    }else
        return false;

}

bool IsAWinGroup(List * group, int side1, int side2) {

    int i = 0;
    bool stop = false;
    if (!group){
        return stop;
    }
    Node *itr = group->sent;
    while (itr->next != group->sent && stop == 0) {
        //printf("elem %d %d\n",i++, itr->next->pos);
        if (itr->next->pos == side2) {
            printf("somme %d\n", itr->next->pos);
            i++;
        }
        if (itr->next->pos == side1) {
            i++;
            printf("sommet %d\n", itr->next->pos);
        }
        if (i == 2) {
            stop = true;
        }
        assert(itr->next);
        itr = itr->next;
    }
    printf("valeur de stop à la sortie de la fonction win %d\n", stop);
    return stop;
}
/*-----------------------------------------------------------------------------*/
                            //Get Fonctions
/*-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------*/
                            //Post Up Fonctions
/*-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------*/
                            //End
/*-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------*/
