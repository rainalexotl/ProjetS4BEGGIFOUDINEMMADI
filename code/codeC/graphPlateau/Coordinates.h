//
//  Coordinates.h
//  graphes
//
//  Created by Mmadi.anzilane on 14/04/2017.
//  Copyright © 2017 Mmadi.anzilane. All rights reserved.
//

#ifndef Coordinates_h
#define Coordinates_h

#include <stdio.h>

typedef struct sCoordinates {
    int x;
    int y;
} Coordinates;

Coordinates calculateCoordinates(int index, int sizeBoard);

int calculateSquareCoordinates(int x, int y, int sizeBoard);

void postUpCoordinates(Coordinates coord);

#endif /* Coordinates_h */
