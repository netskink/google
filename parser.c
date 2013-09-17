#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include "parser.h"
#include "stack.h"
#include "main.h"

extern stack_t STACK;
stack_t PRIVATE_STACK;

int ProcessLine(char *line, char *searchPattern) {

	regex_t *preg;
	int iRC;
	char buffer[80]; 


	preg = malloc(sizeof(regex_t));
	if (NULL == preg) {
		// malloc failed
		return(-1);	
	}

	iRC = regcomp(preg,searchPattern,REG_EXTENDED|REG_NOSUB);
	if (0 != iRC ) {
		// regex compile failed.
		return(-2);	
	}

	iRC = regexec(preg,line,0,NULL,0);
	if (REG_NOMATCH == iRC ) {
		// regexec failed to find a match
		regerror (iRC, preg, buffer, 80);
		//printf("%s\n",buffer);
		goto processline_cleanup;
	} else  if (0 != iRC ) {
		// regexec had some other error.
		regerror (iRC, preg, buffer, 80);
		printf("%s\n",buffer);
		goto processline_cleanup;
	} 

	// A match was found
	//printf("%s",line);

processline_cleanup:
	regfree(preg);
	free(preg);

	return(iRC);


}


int buildWordEntry(void) {
	char buffer[1024];
	word_entry_t WORDENTRY;
	int len;

	// The definition is at most the (stack size - 1) * 1024
	WORDENTRY.defn = malloc(sizeof(char)*1024*(STACK.size-1));
	if (NULL == WORDENTRY.defn) {
		return (-1);
	}
	WORDENTRY.defn[0] = 0; // Set initial string to ''

	// Assume the defined word is 64 chars or less
	WORDENTRY.word = malloc(sizeof(char)*64);
	if (NULL == WORDENTRY.word) {
		return (-2);
	}
	WORDENTRY.defn[0] = 0; // Set initial string to ''


	// A few ways come to mind with forming the definition.
	// The problem is that the stack is in reverse order
	// The defined word is at the bottom and the lines which make
	// up the definition are in reverse order.
	//
	// method 1
	// create a new stack and pop this one and put it on the other one.
	// then pop them off in the proper order. probably the easiest.
	//
	// method 2
	// find the strlen and then memmove the str to that offset in the buffer
	//
	// method 3
	// reverse the stack operation to make it into a queue and pull from it 
	// in order of how we can append the strings.



	// Method 1, pop the stack and push on the new stack to build the
	// word entry so that the definition word is on top.
	while (STACK.size > 0) {
		push(&PRIVATE_STACK, pop(&STACK));
	}

	// Now the defined word is on top of stack
	strcpy(WORDENTRY.word,pop(&PRIVATE_STACK));
	len = strlen(WORDENTRY.word);	
	WORDENTRY.word[len-2] = 0; // rub out the <cr> <lf> pair

	// The first line of the definition has the words "Defn: " in it.
	// copy it to the temp buffer and then copy it from an offset
	// skipping this part.
	strcpy(buffer,pop(&PRIVATE_STACK));
	strcat(WORDENTRY.defn,&buffer[6]);


	// And the definition is multiple lines on the rest of the stack.
	while (PRIVATE_STACK.size > 0) {
		
		strcat(WORDENTRY.defn,pop(&PRIVATE_STACK));
		len = strlen(WORDENTRY.defn);	
		WORDENTRY.defn[len-2] = 0x20; // replace <cr><lf> pair with a space
		WORDENTRY.defn[len-1] = 0x0; // and null term shortened string
	}
	printf("word-> %s\n",WORDENTRY.word);
	printf("defn-> %s\n",WORDENTRY.defn);

	return (0);
}


