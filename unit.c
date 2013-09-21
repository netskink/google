#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hash.h"
#include "list.h"
#include "io.h"
#include "stack.h"
#include "main.h"

/*
 * These are primative unit tests.
 */


extern stack_t STACK;

void test_stack(void) {

	int i;
	char buf[256];

	push(&STACK,"one");
	push(&STACK,"two");
	push(&STACK,"three");

	printf("%s\n",pop(&STACK));
	printf("%s\n",pop(&STACK));
	printf("%s\n",pop(&STACK));


	for(i=0;i<26;i++) {
		sprintf(buf,"%d",i);
		push(&STACK,buf);
	}

}


void test_hash(void) {

	f("this",0);
	f("this",0);
	f("is",0);
	f("a",0);
	f("test",0);

}

void test_list(void) {

	int i;
	int iArray[] = {0,1,2,3,4,5,6,7,8,9};
	list_t *pList;
	node_t *pNode;


	// list unit tests
	pList = init_list();
	if (NULL == pList) {
		fprintf(stderr, "error in list create.\n");
		exit(-1);
	}
	i=0;
	while(i<10) {
		append(pList,&iArray[i]);
		i++;
	}
	pNode=pList->pFirst;
	while(NULL != pNode) {
		printf("list item => %d\n",*(int*) pNode->pData);
		pNode = pNode->pNext;
	}
}


