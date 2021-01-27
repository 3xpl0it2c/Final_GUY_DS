#pragma once
#include "student.h"

struct BNode {
	student_t* key;
	struct BNode* left;
	struct BNode* right;
};

typedef struct BNode bnode_t;
