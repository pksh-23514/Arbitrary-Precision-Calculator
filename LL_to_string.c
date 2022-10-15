#include "apc.h"

int LL_to_str (Dlist* head, Dlist* tail, char sign, char* data)
{
	int pos = 0, ret;
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
			if (head->data != 0)
				ret = sprintf (buffer, "%d", head->data);
			else
				ret = sprintf (buffer, "%04d", 0);

			for (int i = 0; i < ret; i++)
			{
				data [pos++] = buffer [i];
			}

			head = head->next;
		}
	}

	data [pos] = '\0';

	return SUCCESS;
}
