#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define NDEBUG

#include "dbg.h"

typedef int (*compare_cb)(int a, int b);

typedef int * (*sort_algo)(int *list, int count, compare_cb cmp);

void die(char *msg)
{
	if(errno){
		perror(msg);		
	} else {
		fprintf(stderr, "%s\n", msg);
	}

	exit(EXIT_FAILURE);
}

int sorted_order(int a, int b)
{
	return (a < b);
}

int reverse_order(int a, int b)
{
	return (a > b);
}

int * selection_sort(int *list, int count, compare_cb cmp)
{
int *list_cpy;
int i, j, tmp;

	list_cpy = malloc(count * sizeof(int));
	CHECK_MEM(list_cpy);

	for(i = 0; i < count; i++){
		list_cpy[i] = list[i];
	}

	for(i = 0; i < count - 1; i++){
		for(j = i+1; j < count; j++){
			if( !cmp(list_cpy[i], list_cpy[j]) ){

				tmp = list_cpy[j];
				list_cpy[j] = list_cpy[i];
				list_cpy[i] = tmp;	
			}
		}
	}

	return list_cpy;

error:	
	return NULL;
}

int test_sorting(int *list, int count, sort_algo sort, compare_cb cmp)
{
int *sorted;
int i;
	sorted = sort(list, count, cmp);
	CHECK(sorted != NULL, "List not sorted");

	for(i = 0; i < count; i++){
		printf("%d ", sorted[i]);
	}

	printf("\n");

	free(sorted);

	return 0;

error:
	return -1;
}

int main(int argc, char *argv[])
{
int *to_sort;
int count, i;
char **args;

	if(argc < 2){
		die("USAGE: ex <num1> <num2> <numN>...");
	}

	count = argc - 1;
	args = argv + 1;

	to_sort = malloc(count * sizeof(int));
	CHECK_MEM(to_sort);

	for(i = 0; i < count; i++){

		to_sort[i] = atoi(args[i]);
	}

	if( test_sorting(to_sort, count, selection_sort, sorted_order) != 0 ) goto error;
	if( test_sorting(to_sort, count, selection_sort, reverse_order) != 0 ) goto error;

	free(to_sort);
	
	return 0;

error:
	return -1;
}
