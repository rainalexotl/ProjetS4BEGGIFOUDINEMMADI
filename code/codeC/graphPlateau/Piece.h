//
//  Piece.h
//  graphes
//
//  Created by Mmadi.anzilane on 21/04/2017.
//  Copyright © 2017 Mmadi.anzilane. All rights reserved.
//

#ifndef Piece_h
#define Piece_h

#include <stdio.h>
#include "Coordinates.h"

typedef struct sPiece {
    Coordinates coord;
    char color;
}Piece;

Piece  createPiece();

#endif /* Pion_h */
