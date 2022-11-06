#include "apc.h"

int modulus (Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
	Dlist* quot_h = NULL;
	Dlist* quot_t = NULL;

	int ret = division_internal (head1, tail1, head2, tail2, &quot_h, &quot_t, headR, tailR);

	dl_delete_list (&quot_h, &quot_t);
	return ret;
}
