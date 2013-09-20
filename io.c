#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "parser.h"
#include "io.h"
#include "hash.h"
#include "stack.h"


extern stack_t STACK;

enum steps {LOOKFORWORD,
			LOOKFORDEFN,
			LOOKFORDEFNCONT};

int  ReadFile(char *filename) {

	FILE *fd;
	char buffer[256];
	int iRC;
	enum steps current_state = LOOKFORWORD;
	word_entry_t *pWORDENTRY; 

	fd =  fopen(filename, "r");
	if (NULL == fd) {
		return (-1);
	}

	while (NULL != fgets(buffer,1024,fd)) {

		// TODO: This code here will changed to a state machine
		// instead of this bunch of if code later.

		if (LOOKFORWORD == current_state) {
			// look for a word with a definition
			//iRC = ProcessLine(buffer, "^[A-Z;']+-*[A-Z]*\\s");
			iRC = ProcessLine(buffer, "^[A-Z]+\\s\\s$");
			if (0 == iRC) {
				// it found a definition word
				// put it on stack
				push(&STACK,buffer);
				current_state = LOOKFORDEFN;
				continue;
			}
		}

		if (LOOKFORDEFN == current_state) {
			// look for a word with a definition
			//iRC = ProcessLine(buffer, "^Defn:|^1");
			iRC = ProcessLine(buffer, "^Defn:|^1");
			if (0 == iRC) {
				// it found the start of the definition
				// put it on stack
				push(&STACK,buffer);
				current_state = LOOKFORDEFNCONT;
				continue;
			}
		}

		if (LOOKFORDEFNCONT == current_state) {
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
					return (-2);
				}
				buildWordEntry(pWORDENTRY); 
				f(pWORDENTRY->word,0x10000);
				//while (stack_not_empty(&STACK)) {
			//		printf("io.c->%s\n",pop(&STACK));
			//	}
			}
		}


	} /* end of while loop */
	fclose(fd);
	return(0);
}


