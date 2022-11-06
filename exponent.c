#include "apc.h"

int exponent (Dlist** head1, Dlist** tail1, Dlist** head2, Dlist** tail2, Dlist** headR, Dlist** tailR)
{
	Dlist* zero_h = NULL;
	Dlist* zero_t = NULL;
	Dlist* one_h = NULL;
	Dlist* one_t = NULL;
	Dlist* two_h = NULL;
	Dlist* two_t = NULL;
	Dlist* temp_h = NULL;
	Dlist* temp_t = NULL;

	int ret = dl_insert_last (&zero_h, &zero_t, 0);
	ret = dl_insert_last (&one_h, &one_t, 1);
	ret = dl_insert_last (&two_h, &two_t, 2);
	ret = dl_insert_last (headR, tailR, 1);

	Dlist* base_h = NULL;
	Dlist* base_t = NULL;

	while (compare_LL_lt (*head2, zero_h) != LT)
	{
		if ((*tail2)->data & 1)
		{
			//Odd Exponent scenario.
			ret = multiplication (head1, tail1, headR, tailR, &temp_h, &temp_t);
			// strip_leading_zeroes (&temp_h);
			dl_delete_list (headR, tailR);
			*headR = temp_h;
			*tailR = temp_t;
			temp_h = NULL;
			temp_t = NULL;

			pretty_print_list ("Result if Odd: ", *headR);
		}

		// strip_leading_zeroes (head1);
		ret = copy_LL (*head1, *tail1, &base_h, &base_t);	//Duplicating the Base.
		pretty_print_list ("Duplicate Base: ", base_h);

		ret = multiplication (head1, tail1, &base_h, &base_t, &temp_h, &temp_t);
		dl_delete_list (head1, tail1);
		dl_delete_list (&base_h, &base_t);
		// strip_leading_zeroes (&temp_h);
		*head1 = temp_h;
		*tail1 = temp_t;
		temp_h = NULL;
		temp_t = NULL;
		pretty_print_list ("New Base: ", *head1);

		ret = division (head2, tail2, &two_h, &two_t, &temp_h, &temp_t);
		dl_delete_list (head2, tail2);
		*head2 = temp_h;
		*tail2 = temp_t;
		temp_h = NULL;
		temp_t = NULL;
		pretty_print_list ("New Exponent: ", *head2);
	}

	return SUCCESS;
}
