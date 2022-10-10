#include "apc.h"

void print_list (Dlist* head)
{
	if (head == NULL)
		return;
	else
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
}
