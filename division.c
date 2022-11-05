#include "apc.h"

int division (Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
	printf ("------------------------------\n");
	Dlist* dividend_h = *head1;
	Dlist* dividend_t = *tail1;
	Dlist* divisor_h = *head2;
	Dlist* divisor_t = *tail2;
	Dlist* temp_h = NULL;
	Dlist* temp_t = NULL;
	Dlist* quotient_h = NULL;
	Dlist* quotient_t = NULL;
	Dlist* tempR_h = NULL;
	Dlist* tempR_t = NULL;
	int ret, flag;
	
	//print_list (quotient_h);
	while (1)
	{
		ret = dl_insert_last (&quotient_h, &quotient_t, 0);
		flag = 0;

		while ((ret = compare_LL_lt (temp_h, divisor_h)) != GT)	//Appending to Temporary Dividend.
		{
			printf ("Return: %d\n", ret);
			if (dividend_h == NULL)
			{
				flag = 1;
				break;
			}
			ret = dl_insert_last (&temp_h, &temp_t, dividend_h->data);
			//print_list (temp_h);
			dividend_h = dividend_h->next;
		}
		printf ("Temporary Dividend:\n");
		print_list (temp_h);
		print_list (divisor_h);

		if (flag == 1)
			break;
		printf ("------------------------------\n");
		
		while (compare_LL_lt (temp_h, tempR_h) != LT)
		{
			dl_delete_list (&tempR_h, &tempR_t);
			quotient_h->data += 1;
			ret = multiplication (&quotient_h, &quotient_t, &divisor_h, &divisor_t, &tempR_h, &tempR_t);
			if (ret == FAILURE)
				printf ("Multiplication Operation failed.\n");
			ret = remove_zeros (&tempR_h);
			printf ("Quotient: %d\n", quotient_h->data);
		}

		//print_list (temp_h);
		//print_list (tempR_h);
		printf ("***********------\n");
		ret = dl_insert_last (headR, tailR, (quotient_h->data - 1));
		dl_delete_list (&quotient_h, &quotient_t);
		
		Dlist* subR_h = NULL;
		Dlist* subR_t = NULL;
		ret = addition (&temp_h, &temp_t, &divisor_h, &divisor_t, &subR_h, &subR_t);	//Instead of recalculating new product with (quotient->data - 1), we added Divisor to the Dividend.
		if (ret == FAILURE)
			printf ("Addition Operation failed.\n");
		
		print_list (tempR_h);
		print_list (subR_h);
		dl_delete_list (&temp_h, &temp_t);
		ret = subtraction (&subR_h, &subR_t, &tempR_h, &tempR_t, &temp_h, &temp_t);	//Calculating Remainder and storing in 'temp_h'.
		if (ret == FAILURE)
			printf ("Subtraction Operation failed.\n");
		print_list (temp_h);
		dl_delete_list (&subR_h, &subR_t);
	}

	printf ("After Division:\n");
	printf ("Quotient: ");
	print_list (*headR);
	printf ("Divisor: ");
	print_list (divisor_h);
	printf ("Remainder: ");
	print_list (temp_h);
	return SUCCESS;
}

int remove_zeros (Dlist** head)
{
	if (*head == NULL)
		return FAILURE;

	if ((*head)->data == 0)
	{
		*head = (*head)->next;
		free ((*head)->prev);
		(*head)->prev = NULL;
		return SUCCESS;
	}
}
