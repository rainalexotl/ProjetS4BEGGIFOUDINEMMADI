#include "../../src/ReducedGraph.h"

int main(int argc, const char * argv[]){
	int nbMax;
	int elem;
	printf("*********************************\n");
	printf("*       Tests for the List      *\n");
	printf("*********************************\n");
	
	List *l = createList();
	printf("Please Enter the number of elements that you will insert\n");
	scanf("%d",&nbMax);
	
	for (int i = 0; i < nbMax;++i) { 
		printf("Please enter the element\n");
		scanf("%d",&elem);
		pushBack(l,elem);
	}
	printf("This is your List\n");
	printList(l);
	destroyList(l);
}
