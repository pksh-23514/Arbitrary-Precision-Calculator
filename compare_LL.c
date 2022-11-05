#include "apc.h"

// int compare_LL_lt (Dlist* head1, Dlist* head2)
// {
// 	if (count_nodes (head1) > count_nodes (head2))
// 		return GT;
// 	else if (count_nodes (head1) < count_nodes (head2))
// 		return LT;
// 	else
// 	{
// 		if (head1 != NULL && head2 != NULL && head1->data > head2->data)	//List-1 Node's Data is greater than List-2 Node's Data.
// 			return GT;
		
// 		if (head1 != NULL && head2 != NULL && head1->data < head2->data)	//List-1 Node's Data is smaller than List-2 Node's Data.
// 			return LT;
		
// 		if (head1 != NULL && head2 != NULL && head1->data == head2->data)	//List-1 Node's Data is equal to List-2 Node's Data.
// 			return (compare_LL_lt (head1->next, head2->next));				//Recursive function call to Compare the Next Nodes of both the LLs.
// 	}
// }

int compare_LL_lt(Dlist* a, Dlist*b) {
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