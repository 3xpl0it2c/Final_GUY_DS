#include <stdlib.h>
#include "binTree.h"
#include "student.h"

bnode_t* newBNode(student_t* st) {
	bnode_t* node = malloc(sizeof(bnode_t));

	node->key = st;
	node->right = node->left = NULL;

	return node;
}

void insertIntoTree(bnode_t* root, student_t* value) {
	double rootAvg = getAverage(root->key);
	double keyAvg = getAverage(value);

	if (rootAvg > keyAvg) {
		if (root->right != NULL) return insertIntoTree(root->right, value);
		root->right = newBNode(value);
	}

	if (rootAvg < keyAvg) {
		if (root->left != NULL) return insertIntoTree(root->left, value);
		root->left = newBNode(value);
	}
}
