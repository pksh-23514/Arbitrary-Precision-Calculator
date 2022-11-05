#include "apc.h"

int subtraction (Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
	//printf ("Inside Subtraction:\n");
	//print_list (*head1);
	//print_list (*head2);
	//print_list (*headR);
	if ((*head1 == NULL) && (*head2 != NULL))
	{
		*headR = *head2;
		*tailR = *tail2;
		return SUCCESS;
	}
	else if ((*head2 == NULL) && (*head1 != NULL))
	{
		*headR = *head1;
		*tailR = *tail2;
		return SUCCESS;
	}
	else
	{
		Dlist* temp1 = *tail1;
		Dlist* temp2 = *tail2;
		int borrow = 0, res, ret;

		while ((temp1 != NULL) || (temp2 != NULL))
		{
			int num1 = ((temp1 == NULL) ? 0 : (temp1->data));
			int num2 = ((temp2 == NULL) ? 0 : (temp2->data));
			//printf ("temp1->data: %d & temp2->data: %d\n", num1, num2);
			
			if (num1 < num2)
			{
				//printf ("temp1->data: %d & temp2->data: %d\n", num1, num2);
				borrow = 10000;
				temp1->prev->data = temp1->prev->data - 1;
				//printf ("Prev Node Data: %d\n", temp1->prev->data);
			}
			else
			{
				borrow = 0;
			}

			res = num1 - num2 + borrow;
			//printf ("Result: %d\n", res);
			ret = dl_insert_first (headR, tailR, res);
			if (ret == FAILURE)
			{
				printf ("ERROR: Node not created.\n");
				return FAILURE;
			}

			if (temp1 != NULL)
				temp1 = temp1->prev;
			if (temp2 != NULL)
				temp2 = temp2->prev;
		}

		//print_list (*headR);

		return SUCCESS;
	}
}
