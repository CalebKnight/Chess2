#include <stdlib.h>
#include <stdio.h>

typedef struct LinkedListNode
{
    void *data;
    struct LinkedListNode *next;
    struct LinkedListNode *prev;
} Node;

/*Creates a node with empty data to be initialised with values later*/
Node *CreateNode()
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->next = NULL;
    node->prev = NULL;
    return node;
}

typedef struct LinkedList
{
    Node *head;
    Node *tail;
    int size;
} List;
/*Creates a list with empty pointers to be initialised later*/
List *CreateList()
{
    List *list = (List *)malloc(sizeof(List));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

void SetHead(List *list, Node *node)
{
    list->head = node;
}

void SetTail(List *list, Node *node)
{
    list->tail = node;
}

Node *GetTail(List *list)
{
    return list->tail;
}

Node *GetHead(List *list)
{
    return list->head;
}

Node *GetNext(Node *node)
{
    return node->next;
}

Node *GetPrev(Node *node)
{
    return node->prev;
}

void SetNext(Node *node, Node *node2)
{
    node->next = node2;
}

void SetPrev(Node *node, Node *node2)
{
    node->prev = node2;
}

void AppendList(List *list, Node *node)
{
    if (list->head == NULL)
    {
        SetHead(list, node);
        SetTail(list, node);
        list->size++;
    }
    else
    {
        SetNext(list->tail, node);
        SetPrev(node, list->tail);
        SetTail(list, node);
        list->size++;
    }
}

/*Frees all data from a node*/
void FreeNode(Node *node)
{
    free(node);
}

void FreeNodeData(Node *node)
{
    free(node->data);
}

void FreeAllNodesData(Node *node)
{
    if (node->next != NULL)
    {
        if (node->next->next != NULL)
        {
            FreeAllNodesData(node->next);
        }
        else
        {
            FreeNodeData(node->next);
        }
    }
    FreeNodeData(node);
}

// Frees both the data and the node itself from memory
void FreeListData(List *list)
{
    if (list->head == NULL)
    {
    }
    else if (list->head->next == NULL)
    {
        FreeNodeData(list->head);
    }
    else if (list->tail->prev == list->head)
    {
        FreeNodeData(list->tail);
        FreeNodeData(list->head);
    }
    else
    {
        FreeAllNodesData(list->head);
    }
}

/*Loop through the list and free each node one by one from memory*/
void FreeAllNodes(Node *node)
{
    if (node->next != NULL)
    {
        if (node->next->next != NULL)
        {
            FreeAllNodes(node->next);
        }
        else
        {
            FreeNode(node->next);
        }
    }
    FreeNode(node);
}
/*Free both or one of the two head and tail pointers in the list and the list itself from memory*/
void FreeList(List *list)
{
    if (list->head == NULL)
    {
    }
    else if (list->head->next == NULL)
    {
        FreeNode(list->head);
    }
    else if (list->tail->prev == list->head)
    {
        FreeNode(list->tail);
        FreeNode(list->head);
    }
    else
    {
        FreeAllNodes(list->head);
    }
    free(list);
}