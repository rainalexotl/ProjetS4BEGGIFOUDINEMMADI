//
//  Coordinates.c
//  graphes
//
//  Created by Mmadi.anzilane on 14/04/2017.
//  Copyright © 2017 Mmadi.anzilane. All rights reserved.
//

#include "Coordinates.h"

Coordinates calculateCoordinates(int index, int sizeBoard) {
    Coordinates coord;
    coord.x = index/sizeBoard;
    coord.y = index%sizeBoard;
    return coord;
}

int calculateSquareCoordinates(int x, int y, int sizeBoard) {
    return sizeBoard*x+y;
}

void postUpCoordinates(Coordinates coord) {
    printf("x = %d\ny = %d\n", coord.x, coord.y);
}
