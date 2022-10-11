#include "apc.h"

int addition (Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
	if ((*head1 == NULL) && (*head2 == NULL))
	{
		return FAILURE;
	}
	else if ((*head1 == NULL) && (*head2 != NULL))
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
		int carry = 0, res, ret;

		while ((temp1 != NULL) || (temp2 != NULL))
		{
			res = ((temp1 == NULL) ? 0 : (temp1->data)) + ((temp2 == NULL) ? 0 : temp2->data) + carry;
			
			//printf ("Result: %d\n", res);
			if (res >= 10000)
			{
				carry = 1;
				res = res - 10000;
			}
			else
			{
				carry = 0;
			}

			//printf ("Result: %d & Carry: %d\n", res, carry);
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

		if (carry == 1)
		{
			ret = dl_insert_first (headR, tailR, carry);
			if (ret == FAILURE)
			{
				printf ("ERROR: Node not created.\n");
				return FAILURE;
			}
		}
	}
}
