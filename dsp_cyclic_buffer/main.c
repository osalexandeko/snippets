#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct c_node{
	struct c_node * next;
	struct c_node * prev;
	int32_t value;
} c_node_t;

typedef struct c_buffrer{
 	c_node_t * root;
 	int index;
 	int size;
 	int32_t (* insert)(int);
 	int32_t (* get)(int);
} c_buffrer_t;

int main(int argc, char *argv[]) {
	return 0;
}
