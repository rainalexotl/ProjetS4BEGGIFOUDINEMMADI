#ifndef position_h
#define position_h
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

struct s_position{
	int pos;
	bool visited;
	struct s_position * neighbors[6];
};

typedef struct s_position * Position;

#endif //position_h
