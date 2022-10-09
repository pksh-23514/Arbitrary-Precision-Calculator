#include "apc.h"

void print_list (Dlist* tail)
{
	if (tail == NULL)
		return;
	else
	{
		while (tail)
		{
			if (tail->data < 10)
				printf("000");
			else if (tail->data > 9 && tail->data < 100)
				printf("00");
			else if (tail->data > 99 && tail->data < 1000)
				printf("0");
			
			printf("%d ", tail->data);
			tail = tail->prev;
		}
		
		printf ("\n");
	}
}
