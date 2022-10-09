#include "apc.h"

/* dl_insert_last : Insert a New node as the Last node of the DLL */

int dl_insert_last (Dlist **head, Dlist **tail, int data)
{
	Dlist* new = (Dlist*) malloc (sizeof (Dlist));	//Dynamic memory allocation to create the Node.
	if (new == NULL)				//If the memory is not allocated, the Insertion operation cannot be performed.
		return FAILURE;

	new->data = data;

	if (*head == NULL)	//If the LL is empty, update the LL with 'new' as th only Node.
	{
		new->prev = NULL;	//Since 'new' is the only node; the 'prev' shall point to NULL.
		new->next = NULL;	//Since 'new' is the only node; the 'next' shall point to NULL.
		*head = *tail = new;	//Since 'new' is the only node; both 'head' and 'tail' shall point to 'new'.
		return SUCCESS;
	}
	else			//Otherwise, the 'new' shall be updated as the Last node of the LL and 'tail' shall be updated.
	{
		new->next = NULL;		//Since 'new' is the Last node; the 'next' shall point to NULL.
		new->prev = *tail;		//The 'prev' shall point to the node being pointed by 'tail'.
		(*tail)->next = new;		//The previous Last node pointed by 'tail' shall point to 'new'.
		*tail = new;			//The 'tail' shall point to 'new'.
		return SUCCESS;
	}
}
