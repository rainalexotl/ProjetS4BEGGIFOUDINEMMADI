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
                            //implement ADT TabHash
/*-----------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------*/
                            //Creation Functions
/*-----------------------------------------------------------------------------*/
TabHash * createTabHashRg(int sizeTab) {
    TabHash *tabH = malloc(sizeof(TabHash));
    tabH->nbGroups = 0;
    tabH->groupList = malloc(sizeof(List*)*sizeTab);
    for (int i = 0; i < sizeTab; ++i) { //a voir s'il faut initialiser ou pas
        tabH->groupList[i] = NULL; //createList();
    }
    return tabH;
}

int hashCode(const List *gp) {
    assert(gp);
    return gp->sent->next->pos;
}

TabHash * hashFonctionRg(TabHash* tabH, List * gp) {
    int hc = hashCode(gp);
    if ((*tabH).groupList[hc] == NULL) {
        (*tabH).groupList[hc] = gp;
        tabH->nbGroups++;
    }else {
        (*tabH).groupList[hc] = gp;
    }
    return tabH;
}

/*-----------------------------------------------------------------------------*/
                            //Modification Functions
/*-----------------------------------------------------------------------------*/
void freeTabHash(TabHash * tabH, int sizeTab) {
    for (size_t i = 0; i < sizeTab; i++) {
        if (tabH->groupList[i]) {
            destroyList(tabH->groupList[i]);
        }
    }
    tabH = NULL;
    free(tabH);
}

/*******************************************************************************/
                            //Search group implementation
/*******************************************************************************/
void modifyVertexLeader(Graph g, int pos, int newLeader) {
    assert(g->v[pos] && g);
    g->v[pos]->groupLeader = newLeader;
    if (!isInGroup(g->v[pos])) { //wasn't previously in group
        g->v[pos]->isInGroup = 1;
    }
}

//Graph g to modify the leader the group
List *groupUnion(List *gp1, List *gp2, Graph g) {
    int groupLeader = gp1->sent->next->pos;
    Node * itr = gp2->sent->next;
    while (itr != gp2->sent) {
        modifyVertexLeader(g, itr->pos, groupLeader);
        gp1 = pushBack(gp1, itr->pos);
        assert(itr->next);
        itr = itr->next;
    }
    destroyList(gp2); // because we dont use that
    printList(gp1);
    return gp1;
}

//v1 and v2 are the positions of vertexs
//v1 is the leader of the new group
List *createNewGroup(Graph g, int v1, int v2) {
    modifyVertexLeader(g, v1, v1); //because it's the leader
    modifyVertexLeader(g, v2, v1);
    List * newGroup = createList();
    newGroup = pushBack(newGroup, v1);
    newGroup = pushBack(newGroup, v2);
    return newGroup;
}

//put a alone vertex in a  group
List * addToGroup(List *gp, int v, Graph g) {
    assert(gp->sent->next);
    int groupLeader = gp->sent->next->pos;
    modifyVertexLeader(g, v, groupLeader);
    gp = pushBack(gp, v);
    return gp;
}

//thougnt to create a alias
bool searchGroup(TabHash *tabH, Graph g, int pos, char color) {
    int side1, side2;
    if (color == BLACK) {
        side1 = getB1Graph(getSizeGraph(g));
        side2 = getB2Graph(getSizeGraph(g));
    }else {
        side1 = getW1Graph(getSizeGraph(g));
        side2 = getW2Graph(getSizeGraph(g));
    }
    List * newGroup = NULL; List * vList = NULL; List * vAdjList = NULL;
    Vertex * v = NULL; Vertex * vAdj = NULL; 
    int posAdj = -1;
    assert(g->v[pos]);
    v = g->v[pos]; //we create alias
    bool winningGroup = false;
    for (int i = 0; i < MAXVOISIN; i++) {
        vAdj = v->Adjacents[i];
        if (vAdj != NULL) {
            vList = tabH->groupList[(v->groupLeader)];
            vAdjList = tabH->groupList[(vAdj->groupLeader)];;
            if (areAdjacentVertexes(v ,vAdj)) { //main condition
                if (isInGroup(vAdj) && isInGroup(v)) {
                    if (!isInSameGroup(v, vAdj)) {
                        if (largerGroup(tabH, v->groupLeader, vAdj->groupLeader) == 1 ) {
                            newGroup = groupUnion(vList, vAdjList, g);
                        }else {
                            newGroup = groupUnion(vAdjList, vList, g);
                        }
                        tabH = hashFonctionRg(tabH, newGroup);
                    } // if its in the same group, nothing is done
                }else if (!isInGroup(vAdj) && isInGroup(v)) { 
                    // they aren't in the same group but they are adjacent,
                    posAdj = calculateHexCoordinates(vAdj->coord.x, vAdj->coord.y,
                        getSizeGraph(g));
                    vList = addToGroup(vList, posAdj, g);
                    newGroup = vList;
                }else if (isInGroup(vAdj) && !isInGroup(v)){
                    vAdjList = addToGroup(vAdjList, pos, g);
                    newGroup = vAdjList;
                }else {
                    posAdj = calculateHexCoordinates(vAdj->coord.x, 
                        vAdj->coord.y, getSizeGraph(g));
                    newGroup = createNewGroup(g, pos, posAdj);
                    tabH = hashFonctionRg(tabH, newGroup);
                }
            }
        }
    }
    // if (newGroup != NULL)
    //     printList(newGroup);
    if (isAWinningGroup(newGroup, side1, side2)) {
        winningGroup = true;
    }
    return winningGroup;
}
/*-----------------------------------------------------------------------------*/
                            //Observation Functions
/*-----------------------------------------------------------------------------*/
//returns true if group with leader1 is >= to group of leader2
bool largerGroup(const TabHash *tabH, int leader1, int leader2) {
    if (tabH->groupList[leader1]->sizeList >= tabH->groupList[leader2]->sizeList){
        return true;
    }else
        return false;

}

//returns true if group gp contains the two parallel sides of its color
bool isAWinningGroup(List * gp, int side1, int side2) {

    int i = 0;
    bool stop = false;
    if (!gp){
        return stop;
    }
    Node *itr = gp->sent;
    while (itr->next != gp->sent && stop == 0) {
        if (itr->next->pos == side2) {
            i++;
        }
        if (itr->next->pos == side1) {
            i++;
        }
        if (i == 2) {
            stop = true;
        }
        assert(itr->next);
        itr = itr->next;
    }
    return stop;
}
/*-----------------------------------------------------------------------------*/
                            //Get Functions
/*-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------*/
                            //Print Functions
/*-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------*/
                            //End
/*-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------*/
