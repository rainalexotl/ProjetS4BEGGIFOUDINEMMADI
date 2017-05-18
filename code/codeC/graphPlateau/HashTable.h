//
//  Graph.h
//  graphes
//
//  Created by Mmadi.anzilane on 14/04/2017.
//  Copyright © 2017 Mmadi.anzilane. All rights reserved.
//
#ifndef HashTable_h
#define HashTable_h

#include "List.h"
#include "Graph.h"
/*-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------*/
                            //implement TAD TabHash
/*-----------------------------------------------------------------------------*/
typedef struct s_TabHash {
    List ** boardListGroup;
    int nbGroups;
} TabHash;

/*-----------------------------------------------------------------------------*/
                            //Create Fonctions
/*-----------------------------------------------------------------------------*/

TabHash * createTabHashRg(int sizeTab);
TabHash * hashFonctionRg(TabHash* tabH, List * group);


/*-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------*/
                            //Modify Fonctions
/*-----------------------------------------------------------------------------*/
void freeTabHash(TabHash *tabH, int sizeTab);
/*******************************************************************************/
                            //implement Search group
/*******************************************************************************/
void modifyLeaderOfVertex(Graph g, int pos, int newLeader);

//Graph g to modify the leader the group
List *groupUnion(List *g1, List *g2, Graph g);

//v1 and v2 are the positions of vertexs
//v1 is the leader of the new group
List *createNewGroup(Graph g, int v1, int v2);

//put a alone vertex in a  group
List * putItInGroup(List *group, int v, Graph g);

bool searchGroup(TabHash *tabH, Graph g, int pos, char color);
/*-----------------------------------------------------------------------------*/
                            //Observation Fonctions
/*-----------------------------------------------------------------------------*/
//To find out which is the largest group between two groups
bool whichIsLargestGroup(const TabHash *tabH, int leader1, int leader2);

//thougnt to create a alias
bool IsAWinGroup(const List * group, int side1, int side2);
/*-----------------------------------------------------------------------------*/
                            //Get Fonctions
/*-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------*/
                            //Post Up Fonctions
/*-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------*/
                            //End
/*-----------------------------------------------------------------------------*/



#endif /* HashTable_h */
