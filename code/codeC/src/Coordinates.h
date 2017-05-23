//
//  Coordinates.h
//  coordinates
//
//  Created by MMADI Anzilane, BEGG Rain-Alexandra and IFOUDINE Sara
//  on 14/04/2017.
//  Copyright © 2017 MMADI Anzilane, BEGG Rain-Alexandra and IFOUDINE Sara.
//  All rights reserved.
//

#ifndef Coordinates_h
#define Coordinates_h

#include <stdio.h>
/*-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------*/
                            //implement ADT Coordinates
/*-----------------------------------------------------------------------------*/

typedef struct sCoordinates {
    int x;
    int y;
} Coordinates;

/*-----------------------------------------------------------------------------*/
                            //Creation Functions
/*-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------*/
                            //Modification Functions
/*-----------------------------------------------------------------------------*/
//returns calculated coordinates based on an index of a board of size = sizeBoard
Coordinates calculateCoordinates(int index, int sizeBoard);
/*-----------------------------------------------------------------------------*/
                            //Observation Functions
/*-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------*/
                            //Get Functions
/*-----------------------------------------------------------------------------*/
//Calculates the position of a hex based on its x y cordinates
int calculateHexCoordinates(int x, int y, int sizeBoard);
/*-----------------------------------------------------------------------------*/
                            //Print Fonctions
/*-----------------------------------------------------------------------------*/
//prints passed coordinates
void printCoordinates(Coordinates coord);
/*-----------------------------------------------------------------------------*/
                            //End
/*-----------------------------------------------------------------------------*/






#endif /* Coordinates_h */
