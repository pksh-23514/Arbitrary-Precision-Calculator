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
			{
				if (pos == 1)
					ret = sprintf (buffer, "%d", head->data);
				else
					ret = sprintf (buffer, "%04d", head->data);
			}
			else
			{
				if (pos != 1)
					ret = sprintf (buffer, "%04d", 0);
				else
					ret = 0;
			}

			for (int i = 0; i < ret; i++)
			{
				data [pos++] = buffer [i];
			}

			head = head->next;
		}
	}

	printf ("%s %d\n", data, strlen (data));
	if ((strcmp (data, "+") == 0) || (strcmp (data, "-") == 0))
	{
		memset (data, '0', 1);
	}
	
	data [pos] = '\0';

	return (pos - 1);	//Returns the Size of the Result without the Sign.
}
