#include "../../src/ReducedGraph.h"

int main(int argc, const char * argv[]) {
	
	printf("*********************************\n");
	printf("*    Tests for Reduced Graph    *\n");
	printf("*********************************\n");
	
	Graph g = createGraph(4);
	int loaded = 0;
	char * str = getSpotsFromFile("../../../../doc/config/size4.txt");
	g = createBoardGraph(g, str, &loaded);
	ReducedGraph *_rG=createReducedGraph(g);
	printf("The creation of the Reduced Graph is done \n");
	printf("This is the board  of the Reduced Graph\n");
	printBoard(_rG->rG);
	//freeReducedGraph(_rG);
	printf("Now we destroyed the Reduced Graph\n");
	destroyGraph(g);
}
