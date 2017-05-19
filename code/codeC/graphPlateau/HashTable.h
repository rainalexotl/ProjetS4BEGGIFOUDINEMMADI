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
                            //implement ADT TabHash
/*-----------------------------------------------------------------------------*/
typedef struct s_TabHash {
    List ** groupList;
    int nbGroups;
} TabHash;

/*-----------------------------------------------------------------------------*/
                            //Creation Functions
/*-----------------------------------------------------------------------------*/

TabHash * createTabHashRg(int sizeTab);
TabHash * hashFonctionRg(TabHash* tabH, List * gp);


/*-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------*/
                            //Modification Functions
/*-----------------------------------------------------------------------------*/
void destroyTabHash(TabHash *tabH, int sizeTab);
/*******************************************************************************/
                            //Search group implementation
/*******************************************************************************/
void modifyVertexLeader(Graph g, int pos, int newLeader);

//Graph g to modify the leader the group
List *groupUnion(List *gp1, List *gp2, Graph g);

//v1 and v2 are the positions of vertexes
//v1 is the leader of the new group
List *createNewGroup(Graph g, int v1, int v2);

//put a alone vertex in a  group
List * addToGroup(List *gp, int v, Graph g);

bool searchGroup(TabHash *tabH, Graph g, int pos, char color);
/*-----------------------------------------------------------------------------*/
                            //Observation Functions
/*-----------------------------------------------------------------------------*/
//returns true if group with leader1 is >= leader2 of to group 
bool largerGroup(const TabHash *tabH, int leader1, int leader2);

//returns true if group gp contains the two parallel sides of its color
bool isAWinningGroup(List * gp, int side1, int side2);
/*-----------------------------------------------------------------------------*/
                            //Get Functions
/*-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------*/
                            //Print Functions
/*-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------*/
                            //End
/*-----------------------------------------------------------------------------*/



#endif /* HashTable_h */
