#include <stdlib.h>
#include "tree.h"

TreeNode *createNode(void *data)
{
    TreeNode *node = malloc(sizeof(TreeNode));
    node->parent = NULL;
    node->children = NULL;
    node->numChildren = 0;
    node->data = data;
    return node;
}

GameTree *createGameTree(void *data)
{
    GameTree *tree = malloc(sizeof(GameTree));
    tree->root = createNode(data);
    tree->size = 1;
    tree->numNodes = 1;
    return tree;
}

GameTree *createEmptyGameTree()
{
    GameTree *tree = malloc(sizeof(GameTree));
    tree->root = NULL;
    tree->size = 0;
    tree->numNodes = 0;
    return tree;
}

void AddChild(TreeNode *parent, TreeNode *child)
{
    parent->children = realloc(parent->children, sizeof(TreeNode *) * (parent->numChildren + 1));
    parent->children[parent->numChildren] = child;
    child->parent = parent;
    parent->numChildren++;
}

void AddChildToGameTree(GameTree *tree, TreeNode *parent, TreeNode *child)
{
    AddChild(parent, child);
    tree->size++;
    tree->numNodes++;
}

void freeNode(TreeNode *node)
{
    for (int i = 0; i < node->numChildren; i++)
    {
        freeNode(node->children[i]);
    }
    free(node->children);
    free(node);
}

void freeGameTree(GameTree *tree)
{
    freeNode(tree->root);
    free(tree);
}