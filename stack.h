// This is a stack that can store strings of 256 chars per stack element.
// The stack itself can only hold 100 strings.  Since the stack in this
// project holds a single definition and no definition is more than 60 
// lines this is sufficient.

#define STACKSIZE 100
struct stack {
    size_t size;
    char items[STACKSIZE][256];
};
typedef struct stack stack_t;

int stack_not_empty(stack_t *ps);

void push(stack_t *ps, char *buffer);

char * pop(stack_t *ps);


