#include "../../src/ReducedGraph.h"

/*I need this fonction because in some tests I dont use Adjacents
and for example in the fonction that tests the creation of the graph
when I use the fonction's graph to destroy the graph , there is a problem
because I do free to values that doesn't exist
*/ 

void destroyGraphBis(Graph g) {
	assert(g != NULL);
    for (int i = 0; i < getNbVertexGraph(g)+4; i++) {
        free(g->v[i]);
    }
    free(g->v);
    free(g);
}

void testGreationOfTheGraph() {
	Graph g;
	g = createGraph(4);
	int loaded =0;
	char * tab = getSpotsFromFile("../../../../doc/config/size4.txt");
	g = createBoardGraph (g, tab,&loaded);
	
	destroyGraphBis(g);
	printf("Creation of the Graph with size = 14 done with success\n");
	
	g = createGraph(6);
	destroyGraphBis(g);
	printf("Creation of the Graph with size = 6 done with success\n");
	
	printf("Creation of the Graph is going to fail because the size is 15\n");	
	g = createGraph(15);
	destroyGraphBis(g);
	
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
//		s = insertVertexGraph(g, g->sizeGraph, BLACK);
//		printf("this insertion worked\n");
//		s = insertVertexGraph(g1, g->sizeGraph, BLACK);
//		printf("this insertion worked\n");
//		s = insertVertexGraph(g,0, BLACK);
//		s = insertVertexGraph(g,g->sizeGraph, NULL);
//		 printf("%d",s->groupLeader);
//		destroyGraphBis(g);
//	 	destroyGraphBis(g1);
}

void testCreationOfTheBoardsGraph() {
	 Graph g = NULL;
	 Graph g1 = createGraph(4);
	 int loaded =0;
	 char * tab = getSpotsFromFile("../../../../doc/config/size4.txt");
	 g1 = createBoardGraph (g1, tab,&loaded);
	 printf("The creation of the board is done with success\n");
	 printf("The creation of the board has failed\n");
	 g = createBoardGraph (g, tab,&loaded);
	 
	 
	 destroyGraphBis(g);
	 destroyGraphBis(g1);
}

void testOfcalcAdjacentVertexesGraph() {
	Graph g = createGraph(4);
	Graph g1 = NULL;
	Graph g2 = createGraph(4);
	int loaded =0;
	char * tab = getSpotsFromFile("../../../../doc/config/size5.txt");
	
	g2 = createBoardGraph (g2, tab,&loaded);

	calcAdjacentVertexesGraph(g2->v[0],g2);
	printf("the calculation is done with success\n");
	printf("the calculation has failed\n");
	calcAdjacentVertexesGraph(g->v[0],g);
	printf("the calculation has failed\n");
	calcAdjacentVertexesGraph(g1->v[0],g1);

	
	destroyGraphBis(g);
	destroyGraphBis(g1);
	destroyGraphBis(g2);
	
}

void testOfcalcAllAdjacentsGraph() {
	Graph g = createGraph(4);
	Graph g1 = NULL;
	
	Graph g2 = createGraph(4);
	int loaded =0;
	char * tab = getSpotsFromFile("../../../../doc/config/size4.txt");
	
	g2 = createBoardGraph (g2, tab,&loaded);
	calcAllAdjacentsGraph(g2);
	printf("the calculation is done with success\n");
	printf("the calculation has failed\n");
	calcAllAdjacentsGraph(g1);
	printf("the calculation has failed\n");
	calcAllAdjacentsGraph(g);
	
	destroyGraphBis(g);
	destroyGraphBis(g1);
	destroyGraphBis(g2);
}

void testOfcalcSideAdjacentsGraph() {
	Graph g1 = NULL;
	Graph g2 = createGraph(4);
	int loaded =0;
	char * tab = getSpotsFromFile("../../../../doc/config/size4.txt");
	
	g2 = createBoardGraph (g2, tab,&loaded);
	
	calcSideAdjacentsGraph(1,g2);
	printf("the calculation is done with success\n");
	printf("the calculation has failed`\n");
	calcSideAdjacentsGraph(30,g2);
	printf("the calculation has failed\n");
	calcSideAdjacentsGraph(1,g1);
	
	destroyGraphBis(g1);
	destroyGraphBis(g2);
}

void testReplaceVertexGraph() {
	Graph g1 = NULL;
	Graph g2 = createGraph(4);
	int loaded =0;
	char * tab = getSpotsFromFile("../../../../doc/config/size4.txt");
	g2 = createBoardGraph (g2, tab,&loaded);
	printf("ettetete\n");
	replaceVertexGraph(g2,2,BLACK);
	printf("The replace is done with success\n");
	printf("The replace has failed\n");
	replaceVertexGraph(g2,40,BLACK);
	replaceVertexGraph(g1,2,BLACK);
	
	destroyGraphBis(g1);
	destroyGraphBis(g2);
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

void printMenu(){
	printf("wich test do you want to test?\n");
	printf("Choose the number of the test you want or '0' to stop the tests\n");
	printf("1- Test of the fonction that create  the graph\n");
	printf("2- Test of the fonction that create the board's graph\n");
	printf("3- Test of the fonction that  calculate an adjacent vertex\n");
	printf("4- Test of the fonction that  calculate all adjacents vertexes\n");
	printf("5- Test of the fonction that  calculate a side adjacents\n");
	printf("6- Test of the fonction that  replace  a vertex in the graph\n");
	printf("7- Test of the fonction that  test if a Vertex belongs to a group\n");
	printf("8- Test of the fonction that test if two vertexes are adjacent\n");
	printf("9- Test of the fonction that test if two Vertexes belongs to the same group\n");
	printf("10- Test of all the fonctions that calculate different things in a vertex\n");
	printf("11- Test of all the Getters fonctions\n");
}

int main(int argc, const char * argv[]) {
	printf("*********************************\n");
	printf("*            Unit Tests         *\n");
	printf("*********************************\n");
	int i = -1;
	while(i != 0){
		printMenu();
		scanf("%d",&i);
		switch(i){
			case 1 :
				testGreationOfTheGraph();
				break;
			case 2 :
				testCreationOfTheBoardsGraph();
				break;
			case 3 :
				testOfcalcAdjacentVertexesGraph();
				break;
			case 4 :
				testOfcalcAllAdjacentsGraph();
				break;
			case 5 :
				testOfcalcSideAdjacentsGraph();
				break;
			case 6 :
				testReplaceVertexGraph();
				break;
			case 7 :
				testIsInGroup();
				break;
			case 8 :
				testAreAdjacentVertexes();
				break;
			case 9 :
				testIsInSameGroup();
				break;
			case 10 :
				testVertexGraph();
				break;
			case 11 :
				testGettersGraph();
				break;
		}
		
    }
    
	
	
}
