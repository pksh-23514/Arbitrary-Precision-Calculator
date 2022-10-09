#ifndef APC_H
#define APC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Maximum length of buffers */
#define MAX_BUF 500
#define SUCCESS 0
#define FAILURE -1

typedef struct
{
	struct node *prev;
	int data;
	struct node *next;
} Dlist;
typedef enum
{
	ADD, SUB, MUL, DIV, MOD, UNSUPPORTED
} Operation;
typedef struct
{
	char* temp;
	int size;
	char sign;
} Num;

/* */
int read_and_validate_args (Num*, Num*, char*, char*, char*);

/* */
Operation is_operator (char);

/* */
int convert (char*, char*, int, int, Dlist**, Dlist**, Dlist**, Dlist**);

/* */
int str_to_LL (char*, int, Dlist**, Dlist**);

/* */
int dl_insert_last (Dlist**, Dlist**, int);

/* */
int compare (char*, char*);

/* */
int addition (Dlist**, Dlist**, Dlist**, Dlist**, Dlist**, Dlist**, char, char, char);

/* */
void print_list (Dlist*);




#endif
