#include "apc.h"

int division (Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
	// printf ("------------------------------\n");
	Dlist* dividend_h = *head1;
	Dlist* dividend_t = *tail1;
	Dlist* divisor_h = *head2;
	Dlist* divisor_t = *tail2;
	Dlist* temp_dividend_h = NULL;
	Dlist* temp_dividend_t = NULL;
	Dlist* quotient_h = NULL;
	Dlist* quotient_t = NULL;
	Dlist* temp_product_h = NULL;
	Dlist* temp_product_t = NULL;
	int ret, flag;
	
	while (1)
	{
		flag = 0;
		while (compare_LL_lt (temp_dividend_h, divisor_h) != GT)	//Appending to Temporary Dividend.
		{
			if (dividend_h == NULL)
			{
				// printf("finished original dividend\n");
				flag = 1;
				break;
			}
			ret = dl_insert_last (&temp_dividend_h, &temp_dividend_t, dividend_h->data);
			dividend_h = dividend_h->next;
		}
		strip_leading_zeroes(&temp_dividend_h);
		// pretty_print_list ("temp dividend", temp_dividend_h);
		// pretty_print_list ("divisor",divisor_h);

		
		// printf ("------------------------------\n");
		
		int multiplier = 0;
		while(1)
		{
			dl_delete_list (&temp_product_h, &temp_product_t);
			dl_delete_list (&quotient_h, &quotient_t);
			dl_insert_last (&quotient_h, &quotient_t, multiplier);
			ret = multiplication (&quotient_h, &quotient_t, &divisor_h, &divisor_t, &temp_product_h, &temp_product_t);
			strip_leading_zeroes (&temp_product_h);
			if (ret == FAILURE)
				printf ("Multiplication Operation failed.\n");
			if (compare_LL_lt(temp_product_h, temp_dividend_h) == GT)
				break;
			multiplier++;
		}
		strip_leading_zeroes (&temp_product_h);
		// printf("after finding apt multiple of divisor\n");
		// pretty_print_list ("temp_dividend",temp_dividend_h);
		// pretty_print_list ("temp_prod closest multiple gt",temp_product_h);
		// pretty_print_list ("multiplier",quotient_h);
		if (flag == 1)
			break;

		// printf ("*************************************\n");
		
		ret = dl_insert_last (headR, tailR, multiplier-1);
		dl_delete_list (&quotient_h, &quotient_t);
		
		Dlist* temp_sum_h = NULL;
		Dlist* temp_sum_t = NULL;
		ret = addition (&temp_dividend_h, &temp_dividend_t, &divisor_h, &divisor_t, &temp_sum_h, &temp_sum_t);	//Instead of recalculating new product with (quotient->data - 1), we added Divisor to the Dividend.
		if (ret == FAILURE)
			printf ("Addition Operation failed.\n");
		dl_delete_list (&temp_dividend_h, &temp_dividend_t);
		
		// pretty_print_list ("temp_sum before subtraction",temp_sum_h);
		// pretty_print_list ("temp_prod <= above",temp_product_h);
		ret = subtraction (&temp_sum_h, &temp_sum_t, &temp_product_h, &temp_product_t, &temp_dividend_h, &temp_dividend_t);	//Calculating Remainder and storing in 'temp_dividend_h'.
		if (ret == FAILURE)
			printf ("Subtraction Operation failed.\n");

		// pretty_print_list("remainder before next iteration",temp_dividend_h);
		strip_leading_zeroes(&temp_dividend_h);
		dl_delete_list (&temp_sum_h, &temp_sum_t);
		dl_delete_list (&temp_product_h, &temp_product_t);	
	}

	// printf ("After Division:\n");
	// printf ("Resulting quotient: ");
	// pretty_print_list ("",*headR);
	// printf ("Divisor: ");
	// pretty_print_list ("",divisor_h);
	printf ("Remainder: ");
	pretty_print_list ("",temp_dividend_h);
	return SUCCESS;
}

int strip_leading_zeroes (Dlist** head)
{
	if (*head == NULL)
		return FAILURE;

	while (count_nodes(*head) > 1 && (*head)->data == 0)
	{
		// printf("#nodes = %d\n", count_nodes(*head));
		*head = (*head)->next;
		free ((*head)->prev);
		(*head)->prev = NULL;
	}
	free ((*head)->prev);
	(*head)->prev = NULL;
	return SUCCESS;
}
