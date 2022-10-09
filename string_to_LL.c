#include "apc.h"

int convert (char* var1, char* var2, int len1, int len2, Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2)
{
	int ret;
	if ((len1 == 0) && (len2 != 0))
	{
		ret = str_to_LL (var2, len2, head2, tail2);
	}
	else if ((len1 != 0) && (len2 == 0))
	{
		ret = str_to_LL (var1, len1, head1, tail1);
	}
	else
	{
		ret = str_to_LL (var1, len1, head1, tail1);
		ret = str_to_LL (var2, len2, head2, tail2);
	}

	return SUCCESS;
}

int str_to_LL (char* var, int len, Dlist** head, Dlist** tail)
{
	int bias = sizeof (int);
	int pos = len - bias;
	int data, ret;
	char temp [len + 1];
	strcpy (temp, var);

	while (pos >= 0)
	{
		data = atoi (temp + pos);
		ret = dl_insert_last (head, tail, data);
		if (ret == FAILURE)
		{
			printf ("ERROR: Node not created.\n");
			return FAILURE;
		}
		temp [pos] = '\0';
		pos = pos - bias;
	}

	if (temp [0] != '\0')
	{
		data = atoi (temp);
		ret = dl_insert_last (head, tail, data);
		if (ret == FAILURE)
		{
			printf ("ERROR: Node not created.\n");
			return FAILURE;
		}
	}

	return SUCCESS;
}
