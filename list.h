
/*
 record Node {
    data; // The data being stored in the node
    Node next // A reference to the next node, null for last node
 }
 record List {
     Node firstNode // points to first node of list; null for empty list
 }
*/

struct node {
	struct node *pNext;
	int *pData;
};
typedef struct node node_t;

struct list {
	struct node *pFirst;
};
typedef struct list list_t;

int append(list_t *pList, void *pData);

list_t *init_list(void);
