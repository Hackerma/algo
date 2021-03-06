# include "binTree.h"
# include "string.h"

struct binTree *newBinTree(int key, struct binTree *left, struct binTree *right)
{
  struct binTree *tree = malloc(sizeof(struct binTree));
  tree->left = left;
  tree->right = right;
  tree->key = key;
  return tree;
}

void freeTree(struct binTree *tree)
{
  if(tree)
  {
    freeTree(tree->left);
    freeTree(tree->right);
    free(tree);
  }
}

int size(struct binTree *tree)
{
  if(tree)
    return 1 + size(tree->left) + size(tree->right);
  return 0;
}

void p_bfs(struct binTree *tree)
{
  struct binTree *node;
  struct queue *queue = malloc(sizeof(struct queue));

  if(tree)
  {
    queue_init(queue);
    queue_push(queue, tree);
    queue_push(queue, NULL);
    while(!queue_is_empty(queue))
    {
       node = queue_pop(queue);
       if(node)
       {
         printf("%d ", node->key);
         if(node->left)
           queue_push(queue, node->left);
         if(node->right)
           queue_push(queue, node->right);
       }
       else
       {
         printf("\n");
         if(!queue_is_empty(queue))
           queue_push(queue,NULL);
       }
    }
  free(queue);
  }
}

static void _printTree(struct binTree *tree)
{
  if(!tree->left && ! tree->right)
    printf("%d  ", tree->key);
  if(tree->left)
  {
    printf("%dl->", tree->key);
    printTree(tree->left);
  }
  if(tree->right)
  {
    printf("%dr->", tree->key);
    printTree(tree->right);
  }
}

void printTree(struct binTree *tree)
{
  if(tree)
    _printTree(tree);
}

static inline int max(int a, int b)
{
  return a > b ? a : b;
}

int height(struct binTree *t)
{
  if(!t)
    return -1;
  return 1 + max(height(t->left), height(t->right));
}

int leafCount(struct binTree *t)
{
  if(!t)
    return 0;

  if(!t->left && !t->right)
    return 1;
  return leafCount(t->left) + leafCount(t->right);
}

int findValue(struct binTree *tree, int node)
{
  while(tree)
  {
    if(node > tree->key)
      tree = tree->right;
    else if(node < tree->key)
      tree = tree->left;
    else
      return 1;
  }
  return 0;
}

void addBinTree(struct binTree *tree, int key)
{
  if(tree)
  {
    if(key > tree->key)
    {
      if(!tree->right)
      {
        struct binTree *ins = newBinTree(key, NULL, NULL);
        tree->right = ins;
      }
      else
        addBinTree(tree->right, key);
    }
    else if(key < tree->key)
    {
      if(!tree->left)
      {
        struct binTree *ins = newBinTree(key, NULL, NULL);
        tree->left = ins;
      }
      else
        addBinTree(tree->left, key);
    }
  }
}

struct binTree *supNode(struct binTree* root, int key)
{
  if(!root)
    return NULL;

  if(key < root->key)
    root->left = supNode(root->left, key);
  else if(key > root->key)
    root->right = supNode(root->right, key);
  else
  {
    if(!root->left)
      return root->right;
    else if(!root->right)
      return root->left;

    struct binTree *node = root->right;
    for(; node->left; node = node->left ){}
    root->key = node->key;
    root->right = supNode(root->right, root->key);
  }
  return root;
}

