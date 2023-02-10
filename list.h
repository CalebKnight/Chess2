#ifndef LINKEDLIST_H
#define LINKEDLIST_H
typedef struct LinkedListNode
{
    void *data;
    struct LinkedListNode *next;
    struct LinkedListNode *prev;
} Node;
typedef struct LinkedList
{
    Node *head;
    Node *tail;
} List;
Node *CreateNode();
List *CreateList();
void SetHead(List *list, Node *node);
void SetNext(Node *node, Node *next);
void SetPrev(Node *node, Node *prev);
void AppendList(List *list, Node *node);
void SetTail(List *list, Node *node);
Node *GetNext(Node *node);
void FreeNode(Node *node);
void FreeAllNodes(Node *node);
void FreeList(List *list);
Node *GetTail(List *list);
Node *GetHead(List *list);
Node *GetPrev(Node *node);
Node *GetNext(Node *node);
#endif