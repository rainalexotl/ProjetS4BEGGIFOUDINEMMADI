//
//  HashTable.h
//  HashTable
//
//  Created by MMADI Anzilane, BEGG Rain-Alexandra and IFOUDINE Sara
//  on 14/04/2017.
//  Copyright © 2017 MMADI Anzilane, BEGG Rain-Alexandra and IFOUDINE Sara.
//  All rights reserved.
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
//allocates memory for a hashTable and its array of lists (groups)
TabHash * createTabHashRg(int sizeTab);

//adds a list gp to the hash table tabH and increments tabH's number of groups
TabHash * hashFonctionRg(TabHash* tabH, List * gp);

/*-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------*/
                            //Modification Functions
/*-----------------------------------------------------------------------------*/
//frees the memory allocated for a hashTable and for its array of lists
void destroyTabHash(TabHash *tabH, int sizeTab);

/*******************************************************************************/
                            //Search group implementation
/*******************************************************************************/
//changes the leader of the group the vertex at position pos belongs to
void modifyVertexLeader(Graph g, int pos, int newLeader);

//unites the group gp1 and gp2
List *groupUnion(List *gp1, List *gp2, Graph g);

/*v1 and v2 are the positions of vertexes
  v1 will be the leader of the new group */
List *createNewGroup(Graph g, int v1, int v2);

//adds a vertex at a position v to a group gp
List * addToGroup(List *gp, int v, Graph g);

//checks if a vertex at pos belongs to a group and eventually adds it to a group
//also checks if a group is a winning group
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
