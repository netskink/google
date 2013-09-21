#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "parser.h"
#include "io.h"
#include "hash.h"
#include "stack.h"


// This stack is a global and not something I would normally do.
// Its done this way to demonstrate a global variable and the use
// of the extern keyword.
extern stack_t STACK;

enum steps {LOOKFORWORD,
			LOOKFORDEFN,
			LOOKFORDEFNCONT};
typedef enum steps steps_t;

// The protoypes for these routines are here since they are 
// private to the implementation.
steps_t look_for_word(char *buffer, stack_t *pStack, steps_t current_state);
steps_t look_for_defn(char *buffer, stack_t *pStack, steps_t current_state); 
steps_t look_for_defn_cont(char *buffer, stack_t *pStack, steps_t current_state); 


// State machine function pointer
steps_t (*states) ( char *buffer, stack_t *pStack, steps_t current_state);


int  ReadFile(char *filename) {

	FILE *fd;
	char buffer[256];
	steps_t current_state;

	fd =  fopen(filename, "r");
	if (NULL == fd) {
		return (-1);
	}

	// Init the state machine
	current_state = LOOKFORWORD;
	states = look_for_word;



	while (NULL != fgets(buffer,1024,fd)) {

		// Call the current function on the buffer
		current_state = states(buffer,&STACK,current_state);

		// Select the next function to call based
		// on the new state.

		switch(current_state) {
		case LOOKFORWORD:
			states = look_for_word;
			break;
		case LOOKFORDEFN:
			states = look_for_defn;
			break;
		case LOOKFORDEFNCONT:
			states = look_for_defn_cont;
			break;
		default:
			// This should never be hit.
			fprintf(stderr,"error in state machine.\n");
			abort();

		}



	} /* end of while loop */
	fclose(fd);
	return(0);
}


steps_t look_for_word(char *buffer, stack_t *pStack, steps_t current_state) {

	int iRC;

	// look for a word with a definition

	// TODO: Bug
	// Below is variant for looking for words with hypens
	// such as XXX-XXX. However, It finds Leading capitalized
	// sentences with a dash in them.
	//iRC = ProcessLine(buffer, "^[A-Z;']+-*[A-Z]*\\s");

	iRC = ProcessLine(buffer, "^[A-Z]+\\s\\s$");
	if (0 == iRC) {
		// it found a definition word
		// put it on stack and look for 
		// the definition.
		push(&STACK,buffer);
		return (LOOKFORDEFN);
	}
	return (current_state);
}

steps_t look_for_defn(char *buffer, stack_t *pStack, steps_t current_state) {

	int iRC;

	// look for a word with a definition
	iRC = ProcessLine(buffer, "^Defn:|^1");
	if (0 == iRC) {
		// it found the start of the definition
		// either by using the Defn: keyword
		// or via a 1. notation.  
		// TODO: In the case
		// of the 1. notation is has a bug
		// since the code is set to erase
		// Defn: prefix.  

		// put it on stack
		push(&STACK,buffer);
		return (LOOKFORDEFNCONT);
	}
	return (current_state);
}

steps_t look_for_defn_cont(char *buffer, stack_t *pStack, steps_t current_state) {

	int iRC;
	word_entry_t *pWORDENTRY; 

	// look for a word with a definition
	//iRC = ProcessLine(buffer, "[&A-Za-z.,()/[/]]+");
	iRC = ProcessLine(buffer, "[A-Za-z]+");
	if (0 == iRC) {
		// it found the start of the definition
		// put it on stack
		push(&STACK,buffer);
		current_state = LOOKFORDEFNCONT;
	} else if (REG_NOMATCH == iRC) {
		// it has found all of the definition
		// pop the entire stack for now
		current_state = LOOKFORWORD;

		pWORDENTRY = malloc(sizeof(word_entry_t));
		if (NULL == pWORDENTRY) {
			fprintf(stderr,"alloc error in look_for_defn_cont!\n");
			abort();
		}
		buildWordEntry(pWORDENTRY); 
		f(pWORDENTRY->word,0x10000);

		// Debug code to check if something is left
		// on the stack.
		//while (stack_not_empty(&STACK)) {
	//		printf("io.c->%s\n",pop(&STACK));
	//	}
	}
	return (current_state);
}
