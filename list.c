#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"
#include "hash.h"
#include "io.h"
#include "stack.h"
#include "main.h"

/*
struct node {
	struct node *pNext;
	int *pData;
};
typedef struct node node_t;

struct list {
	struct node *pFirst;
};
*/

/*
Traversal of a singly linked list is simple, 
beginning at the first node and following each next link until we come to the end:

 node := list.firstNode
 while node not null
     (do something with node.data)
     node := node.next
*/
int append(list_t *pList, void *pData) {

	node_t *pTip;
	node_t *pNewNode;



	// Creat the new node
	pNewNode = malloc(sizeof(node_t));
	if (NULL == pNewNode) {
		return(-1);
	}

	// Add the data;
	pNewNode->pData = pData;
	pNewNode->pNext = NULL;


	if (NULL == pList->pFirst) {
		pList->pFirst = pNewNode;
	} else {
		pTip = pList->pFirst;
		// Find the last node
		while(NULL != pTip->pNext ) {
			pTip = pTip->pNext;
		}
		pTip->pNext = pNewNode;
	}
	return(0);
}


list_t *init_list(void) {

	list_t *pList;
	pList = malloc(sizeof(list_t));
	if (NULL == pList) {
		return(NULL);
	}

	pList->pFirst = NULL;
	return (pList);
}

#ifdef thomas
#endif


