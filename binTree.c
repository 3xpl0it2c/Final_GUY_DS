#include <stdlib.h>
#include "binTree.h"

bnode_t* newBNode(student_t* st) {
	bnode_t* node = malloc(sizeof(bnode_t));

	node->key = st;
	node->right = node->left = NULL;

	return node;
}
