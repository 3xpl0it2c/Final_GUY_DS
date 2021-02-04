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
	unsigned long rootID = root->key->id;

	if (rootID > value->id) {
		if (root->right != NULL) return insertIntoTree(root->right, value);
		root->right = newBNode(value);
	}

	if (rootID < value->id) {
		if (root->left != NULL) return insertIntoTree(root->left, value);
		root->left = newBNode(value);
	}
}

student_t* findInTree(bnode_t* root, student_t* target) {
	if (root == NULL) return NULL;

	student_t* currentStudent = root->key;

	if (currentStudent->id == target->id) { return currentStudent; }
	else if (currentStudent->id > target->id) { return findInTree(root->right, target); }
	else { return findInTree(root->left, target); }
}
