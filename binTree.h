#pragma once
#include "student.h"

struct BNode {
	student_t* key;
	struct BNode* left;
	struct BNode* right;
};

typedef struct BNode bnode_t;

bnode_t* newBNode(student_t*);
void insertIntoTree(bnode_t*, student_t*);
