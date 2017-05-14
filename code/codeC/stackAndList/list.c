#include "list.h"

typedef struct s_node {
	struct s_node *next;
	struct s_node *prev;
	Position p;
} Node;

struct s_list {
	Node *sent;
};

List initList(){
	List l = (List)malloc(sizeof(List));
	l->sent = malloc(sizeof(Node));
	l->sent->next = l->sent;
	l->sent->prev = l->sent;
	l->sent->p = NULL;
	return l;
}

void addPos(List *l, Position p){
	List L = *l;
	Node *n = (Node*)malloc(sizeof(Node));
	n->p = p;
	Node *itr = L->sent->next;

	if(emptyList(L)){
		n->prev = L->sent;
		n->next = L->sent;
		L->sent->next = n;
		L->sent->prev = n;
		// printf("ajout du premier Position de la liste %s\n", e->nom);
		*l = L;
	}

	while(itr != L->sent){
		if (itr->p < p){
			itr = itr->next;
		}else{
			n->next = itr;
			n->prev = itr->prev;
			itr->prev->next = n;
			itr->prev = n;
			*l = L;
		}
	}

	/*si on arrive la on a atteint le sentinel et l'elemtent ajoute sera
	l'Position le plus grand (en valeur) de la liste*/
	n->next = itr;
	n->prev = itr->prev;
	itr->prev->next = n;
	itr->prev = n;
	*l = L;
	// printf("ajout en queue %s de la liste\n", e->nom);
}

bool emptyList(List l){
	return (l->sent->next == l->sent);
}

bool isFirst(List l, Position p){
	return (l->sent->next->p == p);
}

bool isLast(List l, Position p){
	return (l->sent->prev->p == p);
}

Position searchForPos(List l, Position p){
	if(emptyList(l)) return NULL;

	Node *itr = l->sent->next;
	while(itr != l->sent){
		if(itr->p->pos == p->pos){
			return itr->p;
		}else{
			itr = itr->next;
		}
	}
	return NULL;
}

void deletePos(List *l, Position p){
	List L = *l;
	if (emptyList(L)) return;

	/*on verifie que l'Position existe*/
	Position pos = searchForPos(L, p);
	if (pos == NULL) return;

	Node *itr = L->sent->next;

	/*on cherche l'Position de la liste que correspond a l'Position
	mis en parametre puisque la on sait au'il existe*/
	while (itr->p != pos) itr = itr->next;

	itr->prev->next = itr->next;
	itr->next->prev = itr->prev;
	free(itr);

	*l = L;
}

void printListForward(List l, bool b){
	if(emptyList(l)) return;
	Node *itr;

	/*si b = true*/
	if (b){
		itr = l->sent->next;
		while(itr != l->sent){
			printf("%d->", itr->p->pos);
			itr = itr->next;
		}
	}else{
		itr = l->sent->prev;
		while(itr != l->sent){
			printf("%d->", itr->p->pos);
			itr = itr->prev;
		}
	}
	printf("\n");
}

