#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stack.h"
#include "main.h"


stack_t  STACK;


// returns zero when stack is empty
int stack_not_empty(stack_t *ps) {
    return (ps->size);
}


void push(stack_t *ps, char *buffer) {

    if (ps->size == STACKSIZE) {
        fputs("Error: stack overflow\n", stderr);
        abort();
    } else {
        //ps->items[ps->size++] = x;
		strcpy(ps->items[ps->size++],buffer);
	}

}


char * pop(stack_t *ps) {

    if (ps->size == 0){
        fputs("Error: stack underflow\n", stderr);
        abort();
    } else {
        return ps->items[--ps->size];
	}
}
