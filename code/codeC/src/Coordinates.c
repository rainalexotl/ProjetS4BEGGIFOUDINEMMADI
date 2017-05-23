//
//  Coordinates.c
//  coordinates
//
//  Created by MMADI Anzilane, BEGG Rain-Alexandra and IFOUDINE Sara
//  on 14/04/2017.
//  Copyright © 2017 MMADI Anzilane, BEGG Rain-Alexandra and IFOUDINE Sara.
//  All rights reserved.
//

#include "Coordinates.h"
/*-----------------------------------------------------------------------------*/
                            //Creation Functions
/*-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------*/
                            //Modification Functions
/*-----------------------------------------------------------------------------*/
Coordinates calculateCoordinates(int index, int sizeBoard) {
    Coordinates coord;
    coord.x = index / sizeBoard;
    coord.y = index % sizeBoard;
    return coord;
}
/*-----------------------------------------------------------------------------*/
                            //Observation Functions
/*-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------*/
                            //Get Functions
/*-----------------------------------------------------------------------------*/
int calculateHexCoordinates(int x, int y, int sizeBoard) {
    return sizeBoard * x + y;
}

/*-----------------------------------------------------------------------------*/
                            //Print Functions
/*-----------------------------------------------------------------------------*/
void printCoordinates(Coordinates coord) {
    printf("x = %d\ny = %d\n", coord.x, coord.y);
}
/*-----------------------------------------------------------------------------*/
                            //End
/*-----------------------------------------------------------------------------*/
