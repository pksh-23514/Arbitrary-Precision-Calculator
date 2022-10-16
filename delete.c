#include "apc.h"

/* dl_insert_list : Delete all the Nodes of the DLL */

int dl_delete_list(Dlist **head, Dlist **tail)
{
	if (*head == NULL)			//If the LL is empty, the Delete operation cannot be performed.
		return FAILURE;

	while ((*head)->prev != NULL)		//Traverse till the Last node of the LL, deleting nodes one by one on the way.
	{
		*head = (*head)->next;		//Update 'head' to point to Next node.
		free ((*head)->prev);		//Free the Previous node.
		(*head)->prev = NULL;
	}

	free (*tail);				//Free the Last node.
	*head = *tail = NULL;			//Update the 'head' and 'tail' to NULL.
	return SUCCESS;
}
