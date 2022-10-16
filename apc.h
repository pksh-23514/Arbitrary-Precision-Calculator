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

struct Node
{
	struct Node *prev;
	int data;
	struct Node *next;
};

typedef struct Node Dlist;
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
int dl_insert_first (Dlist**, Dlist**, int);

/* */
int result_sign (char*, char*, char, char, char*, char*);

/* */
int compare (char*, char*);

/* */
int addition (Dlist**, Dlist**, Dlist**, Dlist**, Dlist**, Dlist**);

/* */
int subtraction (Dlist**, Dlist**, Dlist**, Dlist**, Dlist**, Dlist**);

/* */
int multiplication (Dlist**, Dlist**, Dlist**, Dlist**, Dlist**, Dlist**);

/* */
int count_nodes (Dlist*);

/* */
int create_result (Dlist**, Dlist**, int);

/* */
void print_list (Dlist*);

/* */
int LL_to_str (Dlist*, Dlist*, char, char*);

int dl_delete_list(Dlist **head, Dlist **tail);

#endif
