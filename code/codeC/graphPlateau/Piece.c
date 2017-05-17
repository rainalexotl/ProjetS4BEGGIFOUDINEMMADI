//
//  Piece.c
//  graphes
//
//  Created by Mmadi.anzilane on 21/04/2017.
//  Copyright © 2017 Mmadi.anzilane. All rights reserved.
//

#include "Piece.h"

Piece createPiece(char color) {
    Piece p;
    p.color = color;
    printf("Please enter the coodinates\n");
    printf("x = ");
    scanf("%d", &p.coord.x);
    printf("y = ");
    scanf("%d", &p.coord.y);
    return p;
}
