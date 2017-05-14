#include "stack.h"

typedef struct s_node{
	Position p;
	struct s_node *next;
} Node;

struct s_Stack{
	Node *top;
    int nbElem;
};

Stack initStack(){
	Stack s = malloc(sizeof(Stack));
	s->top = NULL;
	return s;
}

Position top(Stack s){
	return s->top->p;
}

void printStack(Stack s){
	Node *itr = s->top;

   	while (itr != NULL){
		printf("%d\n", itr->p->pos);
		itr = itr->next;
   }
}

bool emptyStack(Stack s){
	return s->top == NULL;
}

void push(Stack *s, Position p){
	Node *n = (Node*)malloc(sizeof(Node));
	n->p = p;
	n->next = (*s)->top;
	(*s)->top = n;
}

void pop(Stack *s){
	assert(!emptyStack(*s));
	Node *n = (*s)->top;
	(*s)->top = (*s)->top->next;
	free(n);
}

bool searchStack(Stack s, Position p){
	if (emptyStack(s)) return false;
	Node * itr = s->top;
	
	while (itr != NULL){
		if (itr->p->pos == p->pos)
			return true;
		else
			itr = itr->next;
	}
	return false;	
}

//T_pile *saisir_pile(){
// int i,nb,val;
// T_pile *s=init_Pile();
// printf("Combien de valeurs voulez vous entrer?\n");
//	scanf("%d",&nb);
//	for(i=1;i<=nb;i++){
//		printf("veuillez rentrer la valeur %d\n",i);
//		scanf("%d",&val);
//		empiler(s,val);
//	}
//	return s;
//}

/*
int main(){
	T_pile *p=malloc(sizeof(T_pile));
	p=saisir_pile();
    affiche_Pile(p);
}
	
*/
