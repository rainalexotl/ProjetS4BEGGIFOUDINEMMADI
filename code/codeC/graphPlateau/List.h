//
//  List.h
//  List
//
//  Created by Mmadi.anzilane on 14/04/2017.
//  Copyright © 2017 Mmadi.anzilane. All rights reserved.
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
prints the list l with n elements in the format
elem 0 #
elem 2 #
elem 3 #
....
elem n #
*/
void printList(const List *l);
/*-----------------------------------------------------------------------------*/
                            //End
/*-----------------------------------------------------------------------------*/




#endif /* List_h */
