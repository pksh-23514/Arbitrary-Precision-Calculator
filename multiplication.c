#include "apc.h"

int multiplication (Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
	if ((*head1 == NULL) && (*head2 != NULL))	//If one of the Operand is Zero, Result shall be Zero.
	{
		//Create one Node with Data as '0' and return.
		return SUCCESS;
	}
	else if ((*head2 == NULL) && (*head1 != NULL))	//If one of the Operand is Zero, Result shall be Zero.
	{
		//Create one Node with Data as '0' and return.
		return SUCCESS;
	}
	else
	{
		int len1 = count_nodes (*head1);	//Count the number of Nodes in First Operand.
		int len2 = count_nodes (*head2);	//Count the number of Nodes in Second Operand.
		int len = (len1 > len2) ? (len1 + 1) : (len2 + 1);
		printf ("Initial lenth: %d\n", len);
		Dlist* temp2 = *tail2;
		Dlist *tempR_h, *tempR_t, *sumR_h, *sumR_t;
		int carry, res, ret, count = 0;
		
		sumR_h = sumR_t = NULL;
		ret = create_result (&sumR_h, &sumR_t, len);	//Use the larger number of Nodes ('len') to create a Dummy DLL with data as '0'.
		if (ret == FAILURE)		//Error Handling.
		{
			printf ("ERROR: Node not created.\n");
			return FAILURE;
		}

		while (temp2 != NULL)	//The loop shall run till all the Nodes of the Second Operand have multiplied with the First Operand.
		{
			carry = 0;
			tempR_h = tempR_t = NULL;	//To store the product of each Node in a Temporary DLL.
			*headR = *tailR = NULL;
			Dlist* temp1 = *tail1;

			while (temp1 != NULL)	//The loop shall run till all the Nodes of the First Operand have been multiplied with the single Node of the Second Operand.
			{
				res = (temp1->data * temp2->data) + carry;
				printf ("Temp1: %d\tTemp2: %d\n", temp1->data, temp2->data);

				if (res >= 10000)	//To check if the product has more than 4 digits or not.
				{
					carry = res / 10000;
					res = res % 10000;
				}
				else
					carry = 0;
				//printf ("Carry: %d\tResult: %d\n", carry, res);

				ret = dl_insert_first (&tempR_h, &tempR_t, res);	//Store the product after adjusting for 'carry' in the DLL.
				if (ret == FAILURE)		//Error Handling.
				{
					printf ("ERROR: Node not created.\n");
					return FAILURE;
				}

				temp1 = temp1->prev;
			}
			//printf ("Carry: %d\n", carry);

			if (carry != 0)		//If the 'carry' is Non-zero after the Inner loop termination, store it in the DLL.
			{
				ret = dl_insert_first (&tempR_h, &tempR_t, carry);
				if (ret == FAILURE)		//Error Handling.
				{
					printf ("ERROR: Node not created.\n");
					return FAILURE;
				}
			}

			for (int i = 0; i < count; i++)
			{
				ret = dl_insert_last (&tempR_h, &tempR_t, 0);
			}
			printf ("Result of Inner loop: ");
			print_list (tempR_h);
			
			ret = addition (&tempR_h, &tempR_t, &sumR_h, &sumR_t, headR, tailR);	//Add the Dummy DLL and the Temporary DLL to form the Result DLL.
			if (ret == SUCCESS)
			{
				printf ("Result after Addition: ");
				print_list (*headR);
/*
				if (temp2->prev != NULL)
				{
					ret = dl_insert_last (headR, tailR, 0);
					if (ret == FAILURE)
					{
						printf ("ERROR: Node not created.\n");
						return FAILURE;
					}
				}
*/
				printf ("Value for next Iteration: ");
				print_list (*headR);
				dl_delete_list (&tempR_h, &tempR_t);
				//free (sumR_h);
				//free (sumR_t);

				sumR_h = *headR;
				sumR_t = *tailR;
				temp2 = temp2->prev;
				count++;
				//exit (0);
			}
			else
				return FAILURE;
		}

		return SUCCESS;
	}
}

int count_nodes (Dlist* head)	//The function shall return the Number of Nodes in the DLL.
{
	int len = 0;
	while (head != NULL)
	{
		len += 1;
		head = head->next;
	}

	return len;
}

int create_result (Dlist** headR, Dlist** tailR, int len)	//The function shall create a DLL with 'len' number of Nodes and '0' as Data.
{
	int ret;

	for (int i = 0; i < len; i++)
	{
		ret = dl_insert_first (headR, tailR, 0);
		if (ret == FAILURE)
		{
			printf ("ERROR: Node not created.\n");
			return FAILURE;
		}
	}

	return SUCCESS;
}
