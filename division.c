#include "apc.h"

int division_internal (Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR, Dlist **rem_h, Dlist **rem_t)
{

	if (is_zero(*head2)) {
		printf("divide by zero not allowed\n");
		return FAILURE;
	}

	if (is_zero(*head1)) {
		int ret = dl_insert_last (headR, tailR, 0);
		return SUCCESS;
	}
	
	// printf ("------------------------------\n");
	Dlist* dividend_h = *head1;
	Dlist* dividend_t = *tail1;
	Dlist* divisor_h = *head2;
	Dlist* divisor_t = *tail2;
	Dlist* temp_dividend_h = NULL;
	Dlist* temp_dividend_t = NULL;
	Dlist* multiplier_h = NULL;
	Dlist* multiplier_t = NULL;
	Dlist* temp_product_h = NULL;
	Dlist* temp_product_t = NULL;
	Dlist* tempDiff_h = NULL;
	Dlist* tempDiff_t = NULL;
	Dlist* tempSum_h = NULL;
	Dlist* tempSum_t = NULL;
	int ret, flag;

	while (1)
	{
		// printf ("------------------------------\n");
		if (dividend_h == NULL) {
			// printf("division complete\n");
			break;
		}

		int compare_td_d = -1;
		while (1)	
		{
			
			// copy from original dividend until temp_dividend is greater than divisor 
			// or divisor ends
			dl_insert_last (&temp_dividend_h, &temp_dividend_t, dividend_h->data);
			dividend_h = dividend_h->next;
			// pretty_print_list("dividend", dividend_h);
			// pretty_print_list("temp dividend", temp_dividend_h);
			compare_td_d = compare_LL_lt (temp_dividend_h, divisor_h); 
			// printf("compare_td_d %d\n", compare_td_d);
			if (compare_td_d == GT || compare_td_d == EQ || dividend_h == NULL) 
				break;
			else {
				if (remove_leading_zero(&temp_dividend_h)) {
					dl_insert_last (headR, tailR, 0);
				}
			}
		}	

		// pretty_print_list("after removing zeros", temp_dividend_h);

		if (temp_dividend_h == NULL) {
			continue;
		}
	
		int compare_tp_td = -1;
		// find closest mutiple of divisor, lte to temp_dividend
		for(int multiplier = 0; multiplier < 10000; multiplier++)
		{
			// create new multiple
			dl_delete_list (&temp_product_h, &temp_product_t); // clean multiple
			dl_delete_list (&multiplier_h, &multiplier_t); // clean multiplier
			dl_insert_last (&multiplier_h, &multiplier_t, multiplier); // make new multiplier
			
			// calculate new multilple
			ret = multiplication (&multiplier_h, &multiplier_t, &divisor_h, &divisor_t, &temp_product_h, &temp_product_t);
			if (ret == FAILURE)
				printf ("multiplication operation failed in division.\n");
			remove_leading_zero(&temp_product_h); // multiplication adds extra leading 0, remove that

			compare_tp_td = compare_LL_lt(temp_product_h, temp_dividend_h);
			// printf("compare_tp_td -> %d\n", compare_tp_td);

			if (compare_tp_td == GT || compare_tp_td == EQ) 
				break;
			
		}

		// pretty_print_list ("temp_dividend",temp_dividend_h);
		// pretty_print_list ("temp_prod closest multiple gte",temp_product_h);
		// pretty_print_list ("multiplier",multiplier_h);

		if (compare_tp_td == EQ) 
		{
			// temp dividend is exact multiple, add multiplier to quotient
			dl_insert_last (headR, tailR, multiplier_h->data);
		}
		else if (compare_tp_td == GT)
		{
			// temp dividend is lesser, closest multiplier less than temp dividend 
			// is 1 less than current multiplier
			dl_insert_last (headR, tailR, multiplier_h->data - 1);

			ret = addition (&temp_dividend_h, &temp_dividend_t, &divisor_h, &divisor_t, &tempSum_h, &tempSum_t);
			if (ret == FAILURE)
				printf ("multiplication Operation failed in division.\n");		

			temp_dividend_h = tempSum_h;
			temp_dividend_t = tempSum_t;
			tempSum_h = NULL;
			tempSum_t = NULL;

			// pretty_print_list("temp dividend, before subtration", temp_dividend_h);
			// pretty_print_list("temp product, before subtration", temp_product_h);
		}
		else 
		{
			printf ("impossible\n");
			// pretty_print_list("TEMP div", temp_dividend_h);
			// pretty_print_list("prod <= ", temp_product_h);
			exit(0);
		}

		// calculate remainder, temp_dividend - temp_product
		ret = subtraction (&temp_dividend_h, &temp_dividend_t, &temp_product_h, &temp_product_t, &tempDiff_h, &tempDiff_t);
		if (ret == FAILURE)
			printf ("subtraction failed in division.\n");
		// pretty_print_list("remainder after subtraction bz", tempDiff_h);
		
		while(remove_leading_zero(&tempDiff_h));

		// pretty_print_list("remainder after subtraction az", tempDiff_h);
		
		dl_delete_list(&temp_dividend_h, &temp_dividend_t);
		temp_dividend_h = tempDiff_h;
		temp_dividend_t = tempDiff_t;
		tempDiff_h = NULL;
		tempDiff_t = NULL;
	}

	// assigning remainder
	*rem_h = temp_dividend_h;
	*rem_t = temp_dividend_t;
	temp_dividend_h  = NULL;
	temp_dividend_t = NULL;
	
	// printf ("After Division:\n");
	// printf ("Resulting quotient: ");
	// pretty_print_list ("",*headR);
	// printf ("Divisor: ");
	// pretty_print_list ("",divisor_h);
	// printf ("Remainder: ");
	// pretty_print_list ("",*rem_h);
	return SUCCESS;
}

int division (Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
	Dlist* rem_h = NULL;
	Dlist* rem_t = NULL;

	int ret = division_internal (head1, tail1, head2, tail2, headR, tailR, &rem_h, &rem_t);
	
	dl_delete_list (&rem_h, &rem_t);
	return ret;
}