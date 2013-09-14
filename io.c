#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "io.h"
#include "parser.h"
#include "main.h"


void ReadFile(char *filename) {

	FILE *fd;
	char buffer[1024];
	int iRC;

	fd =  fopen(filename, "r");
	if (NULL == fd) {
		return;
	}

	while (NULL != fgets(buffer,1024,fd)) {
		iRC = ProcessLine(buffer);
		iRC = iRC; // To suppress warning.
		//printf("iRC = ProcessLine() is %d\n",iRC);

//		printf("%s",buffer);
	}
}


