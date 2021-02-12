#include "binTree.h"
#include "student.h"
#include <stdlib.h>

bnode_t *newBNode(student_t *st) {
  bnode_t *node = malloc(sizeof(bnode_t));

  node->key = st;
  node->right = node->left = NULL;

  return node;
}

void insertIntoTree(bnode_t *root, student_t *value) {
  unsigned long rootID = root->key->id;

  if (rootID > value->id) {
    if (root->right != NULL)
      return insertIntoTree(root->right, value);
    root->right = newBNode(value);
  }

  if (rootID < value->id) {
    if (root->left != NULL)
      return insertIntoTree(root->left, value);
    root->left = newBNode(value);
  }
}

student_t *findInTree(bnode_t *root, unsigned long targetID) {
  if (root == NULL)
    return NULL;

  student_t *currentStudent = root->key;

  if (currentStudent->id == targetID) {
    return currentStudent;
  } else if (currentStudent->id > targetID) {
    return findInTree(root->right, targetID);
  } else {
    return findInTree(root->left, targetID);
  }
}

void printTree(bnode_t *root) {
  if (root == NULL)
    return;

  printStudent(root->key);

  printTree(root->left);
  printTree(root->right);
}
