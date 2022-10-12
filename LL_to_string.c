#include "apc.h"

int LL_to_str (Dlist* head, Dlist* tail, char sign, char* data)
{
	int pos = 0;
	data [pos++] = sign;
	char buffer [5];
	if (head == NULL)
	{
		data [pos++] = '0';
	}
	else
	{
		while (head != NULL)
		{
			ret = sprintf (buffer, "%d", head->data);

			for (int i = 0; i < ret; i++)
			{
				data [pos++] = buffer [i];
			}

			head = head->next;
		}
	}

	data [pos] = '\0';

	return 1;
}
