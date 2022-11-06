#include "apc.h"

int division_internal (Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR, Dlist **rem_h, Dlist **rem_t)
{

	if (is_zero(*head2)) {
		printf("divide by zero not allowed");
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
	int ret, flag;

	// if (compare_LL_lt(*head1, *head2) == EQ) {
	// 	int ret = dl_insert_last (headR, tailR, 1);
	// 	return ret;
	// }
	int iter = 0;

	while (1)
	{
		++iter;
		printf ("------------------------------\n");
		if (dividend_h == NULL && temp_dividend_h == NULL) {
			printf("division complete\n");
			break;
		}

		temp_dividend_h = *rem_h;
		temp_dividend_t = *rem_t;
		int compare_td_d = -1;
		while (1)	
		{
			compare_td_d = compare_LL_lt (temp_dividend_h, divisor_h); 
			if (compare_td_d == GT || compare_td_d == EQ || dividend_h == NULL) 
				break;
			
			// copy from original dividend until temp_dividend is greater than divisor 
			// or divisor ends
			dl_insert_last (&temp_dividend_h, &temp_dividend_t, dividend_h->data);
			dividend_h = dividend_h->next;
			// pretty_print_list("after making temp dividend", temp_dividend_h);
		}

		pretty_print_list("before removing zeros", temp_dividend_h);
		while(remove_leading_zero(&temp_dividend_h)) {
			dl_insert_last (headR, tailR, 0);
		}	
		pretty_print_list("after removing zeros", temp_dividend_h);
		if (temp_dividend_h == NULL) {
			continue;	
		}
		
		int multiplier = 0;
		int compare_tp_td = -1;
		// find closest mutiple of divisor, lte to temp_dividend
		// int iterj = 0;
		while(1)
		{
			// ++iterj;
			// if (iterj > 60) break;
			compare_tp_td = compare_LL_lt(temp_product_h, temp_dividend_h);
			// printf("compare_tp_td -> %d\n", compare_tp_td);

			if (compare_tp_td == GT || compare_tp_td == EQ) 
				break;

			// create new multiple
			dl_delete_list (&temp_product_h, &temp_product_t); // clean multiple
			dl_delete_list (&multiplier_h, &multiplier_t); // clean multiplier
			dl_insert_last (&multiplier_h, &multiplier_t, multiplier); // make new multiplier
			
			// calculate new multilple
			ret = multiplication (&multiplier_h, &multiplier_t, &divisor_h, &divisor_t, &temp_product_h, &temp_product_t);
			if (ret == FAILURE)
				printf ("Multiplication Operation failed in division.\n");
			
			remove_leading_zero(&temp_product_h); // multiplication adds extra leading 0, remove that
			
			// pretty_print_list("temp_product_in_loop", temp_product_h);

			multiplier++;
			if (multiplier > 9999) 
			{
				printf("multiplier cannot go beyond 9999, exiting\n");
				exit(0);
			}
		}

		pretty_print_list ("temp_dividend",temp_dividend_h);
		pretty_print_list ("temp_prod closest multiple gte",temp_product_h);
		pretty_print_list ("multiplier",multiplier_h);

		if (compare_tp_td == EQ) 
		{
			// temp dividend is exact multiple, add multiplier to quotient
			dl_insert_last (headR, tailR, multiplier_h->data);
			// no need to subtract from temp_dividend, since remainder will be 0
			dl_delete_list(&temp_dividend_h, &temp_dividend_t);
		}
		else if (compare_tp_td == GT)
		{
			// temp dividend is lesser, closest multiplier less than temp dividend 
			// is 1 less than current multiplier
			multiplier_h->data --;
			dl_insert_last (headR, tailR, multiplier_h->data);

			// delete current multiplier, this step can be optimised through subtraction
			dl_delete_list(&temp_product_h, &temp_product_t);
			ret = multiplication (&multiplier_h, &multiplier_t, &divisor_h, &divisor_t, &temp_product_h, &temp_product_t);
			if (ret == FAILURE)
				printf ("multiplication Operation failed in division.\n");		
			remove_leading_zero(&temp_product_h); // multiplication adds extra leading 0, remove that

			// calculate remainder, temp_dividend - temp_product
			ret = subtraction (&temp_dividend_h, &temp_dividend_t, &temp_product_h, &temp_product_t, rem_h, rem_t);
			if (ret == FAILURE)
				printf ("subtraction failed in division.\n");

			// not needed anymore

			pretty_print_list("remainder after subtraction", temp_dividend_h);
		}
		else 
		{
			printf ("impossible\n");
			exit(0);
		}

		// cleaning for next iteration
		dl_delete_list(&temp_dividend_h, &temp_dividend_t);
		dl_delete_list(&temp_product_h, &temp_product_t);
		dl_delete_list (&multiplier_h, &multiplier_t); 
		if (iter > 3) break;
	}

	// printf ("After Division:\n");
	printf ("Resulting quotient: ");
	pretty_print_list ("",*headR);
	// printf ("Divisor: ");
	// pretty_print_list ("",divisor_h);
	// printf ("Remainder: ");
	// pretty_print_list ("",temp_dividend_h);
	*rem_h = temp_dividend_h;
	*rem_t = temp_dividend_t;

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