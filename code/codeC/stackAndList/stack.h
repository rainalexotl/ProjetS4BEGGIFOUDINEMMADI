#ifndef stack_h
#define stack_h
#include <stdio.h>
#define NMAX_ELEM 10
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include "position.h"

typedef struct s_node Node;
typedef struct s_Stack * Stack;

Stack initStack();
void printStack(Stack s);
bool emptyStack(Stack s);
void push(Stack *s, Position p);
void pop(Stack *s);
bool searchStack(Stack s, Position p);
Position top(Stack s);
//stack *saisir_pile();	

#endif //stack_h
