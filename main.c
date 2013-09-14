#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hash.h"
#include "io.h"
#include "main.h"

int main(int argc, char *argv[]) {

	int iRC;
//	char *str1, *token;
//	char *str2, *subtoken;
//	char *saveptr1;
//	char *saveptr2;
//	int j;
	
//	char **words;
//	int word_cnt;

	//printf("argc = %d\n",argc);
	iRC=EXIT_SUCCESS;

//	if (argc != 4) {
//		fprintf(stderr, "Usage: %s string delim subdelim\n",
//	if (argc != 3) {
//		fprintf(stderr, "Usage: %s string delim \n",
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <file>\n", argv[0]);
		iRC=EXIT_FAILURE;
		exit(iRC);
	}


	f("this",0);
	f("this",0);
	f("is",0);
	f("a",0);
	f("test",0);


	ReadFile(argv[1]);
	

	exit(iRC);

}



