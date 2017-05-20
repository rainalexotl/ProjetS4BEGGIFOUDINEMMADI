#include "../../graphPlateau/ReducedGraph.h"

void testGreationOfTheGraph() {
	Graph g;
	g = createGraph(14);
	destroyGraph(g);
	printf("Creation of the Graph with size = 14 done with success\n");
	
	g = createGraph(6);
	destroyGraph(g);
	printf("Creation of the Graph with size = 6 done with success\n");
	
	printf("Creation of the Graph is going to fail because the size is 15\n");	
	g = createGraph(15);
	destroyGraph(g);
	
}

void testInsertionOfTheVertexInGraph() {
//		//creation of the graph withour inserting vertexes
//		
//		
//		Graph g = malloc(sizeof(struct sGraph));
//		g->sizeGraph = 4;
//		g->v = (Vertex**)malloc(sizeof(Vertex*)*(4+4));
//		Graph g1 = NULL;
//		Vertex *s= NULL;
//		
//		s = (Vertex *)insertVertexGraph(g, g->sizeGraph, BLACK);
//		printf("this insertion worked\n");
//		s = (Vertex *)insertVertexGraph(g1, g->sizeGraph, BLACK);
//		printf("this insertion worked\n");
//		s = (Vertex *)insertVertexGraph(g,0, BLACK);
//		s = (Vertex *)insertVertexGraph(g,g->sizeGraph, NULL);
//		 
//		destroyGraph(g);
//	 	destroyGraph(g1);
}

void testCreationOfTheBoardsGraph() {
	 Graph g = NULL;
	 Graph g1 = createGraph(4);
	 int loaded =0;
	 char * tab = getSpotsFromFile("../../../../config/size4.txt");
	 g1 = createBoardGraph (g1, tab,&loaded);
	 printf("The creation of the board is done with success\n");
	 printf("The creation of the board has failed\n");
	 g = createBoardGraph (g, tab,&loaded);
	 
	 
	 destroyGraph(g);
	 destroyGraph(g1);
}

void testOfcalcAdjacentVertexesGraph() {
	Graph g = createGraph(4);
	Graph g1 = NULL;
	Graph g2 = createGraph(4);
	int loaded =0;
	char * tab = getSpotsFromFile("../../../../config/size5.txt");
	
	g2 = createBoardGraph (g2, tab,&loaded);

	calcAdjacentVertexesGraph(g2->v[0],g2);
	printf("the calculation is done with success\n");
	printf("the calculation has failed\n");
	calcAdjacentVertexesGraph(g->v[0],g);
	printf("the calculation has failed\n");
	calcAdjacentVertexesGraph(g1->v[0],g1);

	
	destroyGraph(g);
	destroyGraph(g1);
	destroyGraph(g2);
	
}

void testOfcalcAllAdjacentsGraph() {
	Graph g = createGraph(4);
	Graph g1 = NULL;
	
	Graph g2 = createGraph(4);
	int loaded =0;
	char * tab = getSpotsFromFile("../../../../config/size4.txt");
	
	g2 = createBoardGraph (g2, tab,&loaded);
	calcAllAdjacentsGraph(g2);
	printf("the calculation is done with success\n");
	printf("the calculation has failed\n");
	calcAllAdjacentsGraph(g1);
	printf("the calculation has failed\n");
	calcAllAdjacentsGraph(g);
	
	destroyGraph(g);
	destroyGraph(g1);
	destroyGraph(g2);
}

void testOfcalcSideAdjacentsGraph() {
	Graph g1 = NULL;
	Graph g2 = createGraph(4);
	int loaded =0;
	char * tab = getSpotsFromFile("../../../../config/size4.txt");
	
	g2 = createBoardGraph (g2, tab,&loaded);
	
	calcSideAdjacentsGraph(1,g2);
	printf("the calculation is done with success\n");
	printf("the calculation has failed`\n");
	calcSideAdjacentsGraph(30,g2);
	printf("the calculation has failed\n");
	calcSideAdjacentsGraph(1,g1);
	
	destroyGraph(g1);
	destroyGraph(g2);
}

void testReplaceVertexGraph() {
	Graph g1 = NULL;
	Graph g2 = createGraph(4);
	int loaded =0;
	char * tab = getSpotsFromFile("../../../../config/size4.txt");
	g2 = createBoardGraph (g2, tab,&loaded);
	printf("ettetete\n");
	replaceVertexGraph(g2,2,BLACK);
	printf("The replace is done with success\n");
	printf("The replace has failed\n");
	replaceVertexGraph(g2,40,BLACK);
	replaceVertexGraph(g1,2,BLACK);
	
	destroyGraph(g1);
	destroyGraph(g2);
}

void testIsInGroup() {
	Vertex *s= NULL;
	bool c = isInGroup(s);
	printf("%c\n",c);
}

void testAreAdjacentVertexes() {
	Vertex *v1 = NULL;
	Vertex *v2 = NULL;
	bool c = areAdjacentVertexes(v1,v2);
	printf("%c\n",c);
	
}

void testIsInSameGroup(){
	Vertex *v1 = NULL;
	Vertex *v2 = NULL;
	bool c = isInSameGroup(v1,v2);
	printf("%c\n",c);
}

void testVertexGraph(){
	Vertex *v1 = NULL;
	isTopLeftOrBottomRightVertexGraph(v1,3);
	isTopLeftOrBottomRightVertexGraph(v1,20);
}

void testGettersGraph(){
	Graph g = NULL;
	getSizeGraph(g);
}

int main(int argc, const char * argv[]) {
	printf("*********************************\n");
	printf("*            Unit Tests         *\n");
	printf("*********************************\n");
	
	testGreationOfTheGraph();
//	testGreationOfTheGraph();
//	testCreationOfTheBoardsGraph();
//	testOfcalcAdjacentVertexesGraph();
//	testOfcalcAllAdjacentsGraph();
//	testOfcalcSideAdjacentsGraph();
//	testReplaceVertexGraph();
//	testIsInGroup();
//	testAreAdjacentVertexes();
//	testIsInSameGroup();
//	testVertexGraph();
//	testGettersGraph();
    
	
	
}
