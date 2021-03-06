# include "../queue.h"

struct binTree
{
  int key;
  struct binTree *left, *right;
};

struct binTree *newBinTree(int key, struct binTree *left, struct binTree *right);

void freeTree(struct binTree *tree);

void printTree(struct binTree *tree);

int size(struct binTree *tree);

int height(struct binTree *tree);

int leafCount(struct binTree*tree);

int findValue(struct binTree *tree, int key);

void addBinTree(struct binTree *tree, int key);

struct binTree *supNode(struct binTree *tree, int key);

