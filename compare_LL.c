#include "apc.h"

int compare_LL_lt(Dlist* a, Dlist*b) {
	// if(is_zero(a) && is_zero(b))
	// 	return EQ;
	// if(is_zero(a) && !is_zero(b))
	// 	return LT;
	// if(!is_zero(a) && is_zero(b))
	// 	return GT;
	if (count_nodes(a) == count_nodes(b)) {
		while(a != NULL && b != NULL ) {
			if (a->data == b->data) {
				a = a -> next;
				b = b -> next;
				continue;
			}
			return a->data < b->data ? LT : GT;
		}
		return EQ;
	}
	return count_nodes(a) < count_nodes(b) ? LT : GT;
}