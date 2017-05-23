//
//  List.h
//  List
//
//  Created by MMADI Anzilane, BEGG Rain-Alexandra and IFOUDINE Sara
//  on 14/04/2017.
//  Copyright © 2017 MMADI Anzilane, BEGG Rain-Alexandra and IFOUDINE Sara.
//  All rights reserved.
//

#ifndef List_h
#define List_h
#include <stdio.h>
/*-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------*/
                            //implement ADT List
/*-----------------------------------------------------------------------------*/
typedef struct s_Node {
    int pos;
    struct s_Node *prev;
    struct s_Node *next;
} Node;

typedef struct sList {
    Node *sent;
    int sizeList;
} List;
/*-----------------------------------------------------------------------------*/
                            //Creation Functions
/*-----------------------------------------------------------------------------*/
//allocates memory for a list and for its sentine node
List *createList();

//named pushBack because the positions are only added to the back of the list
List *pushBack(List *l, int pos);
/*-----------------------------------------------------------------------------*/
                            //Modification Functions
/*-----------------------------------------------------------------------------*/
//frees the memory allocated for all of l's elements, its sentinel and itself
void destroyList(List *l);
/*-----------------------------------------------------------------------------*/
                            //Get Functions
/*-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------*/
                            //Print Functions
/*-----------------------------------------------------------------------------*/

/*
prints the list l with n elements in the following format:
elem 0 #
elem 1 #
elem 2 #
....
elem n #
*/
void printList(const List *l);
/*-----------------------------------------------------------------------------*/
                            //End
/*-----------------------------------------------------------------------------*/




#endif /* List_h */
