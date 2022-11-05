#include "apc.h"

void print_list (Dlist* head)
{
	while (head != NULL)
	{
		if (head->data < 10)
			printf("000");
		else if (head->data > 9 && head->data < 100)
			printf("00");
		else if (head->data > 99 && head->data < 1000)
			printf("0");
		
		printf("%d ", head->data);
		head = head->next;
	}	
	printf ("\n");
}

void pretty_print_list(char* message, Dlist* head) {
	printf("%s -> ", message);
	print_list(head);
}