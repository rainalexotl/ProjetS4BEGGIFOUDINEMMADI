#include <stdio.h>
#include "../../src/ReducedGraph.h"



int main(int argc, const char * argv[]) {
	int x; int size;
	Coordinates coord;
	printf("***********************************\n");
	printf("*    Tests for the Coordinates    *\n");
	printf("***********************************\n");
	printf("Choose the index and the size of the board\n");
	
	printf("index?\n");
	scanf("%d",&x);
	
	printf("size?\n");
	scanf("%d",&size);
	
	coord = calculateCoordinates(x,size);
	printf("This is the coordinates\n ");
	printCoordinates(coord);
	
	printf("This is the position of a square using it's coordinates\n");
	int position = calculateHexCoordinates(coord.x,coord.y,size);
	
	printf("the position of the coordinates x = %d & y = %d is %d\n",coord.x,coord.y,position);
	
}
