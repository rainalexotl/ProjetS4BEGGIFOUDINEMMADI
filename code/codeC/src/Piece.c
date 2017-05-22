//
//  Piece.c
//  piece
//
//  Created by MMADI Anzilane, BEGG Rain-Alexandra and IFOUDINE Sara
//  on 14/04/2017.
//  Copyright © 2017 MMADI Anzilane, BEGG Rain-Alexandra and IFOUDINE Sara.
//  All rights reserved.
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
