#ifndef TREE_H
#define TREE_H

typedef struct TreeNode
{
    struct TreeNode *parent;
    struct TreeNode **children;
    int numChildren;
    void *data;
} TreeNode;

typedef struct GameTree
{
    struct TreeNode *root;
    int size;
    int numNodes;
} GameTree;

// Creates a new game tree with a root node containing the given data
GameTree *createGameTree(void *data);

// Creates an empty game tree
GameTree *createEmptyGameTree();

// Adds a child node to a parent node
void AddChild(TreeNode *parent, TreeNode *child);

// Adds a child node to a game tree
void AddChildToGameTree(GameTree *tree, TreeNode *parent, TreeNode *child);

// Frees a node and its children recursively
void freeNode(TreeNode *node);

// Frees a game tree and all its nodes
void freeGameTree(GameTree *tree);

#endif