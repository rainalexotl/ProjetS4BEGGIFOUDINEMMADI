#include "../../src/ReducedGraph.h"


int main(int argc, const char * argv[]) {
	printf("*********************************\n");
	printf("*    Tests for the Hash Table   *\n");
	printf("*********************************\n");
	
	int sizeTab;
	printf("Please enter the size of the Hash Table you want\n");
	scanf("%d",&sizeTab);
	TabHash *tabH = createTabHashRg(sizeTab);
	printf("The creation of the hash table is done with success\n");
	freeTabHash(tabH,sizeTab);
}
