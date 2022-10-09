#include "apc.h"

int read_and_validate_args (Num* num1, Num* num2, char* var1, char* var2, char* operator)
{
	printf ("Enter the Expression to be evaluated:\n");

	char ch;
	int pos = 0, flag = 0;
	num1->temp = (char*) malloc (MAX_BUF * sizeof (char));		//Dynamic memory allocation for Temporary Buffers to extract the Operator and Operands.
	num2->temp = (char*) malloc (MAX_BUF * sizeof (char));
	num1->temp [pos] = '\0';	//Initializing the Buffers as empty originally.
	num2->temp [pos] = '\0';

	while ((ch = getchar()) != '\n')	//The loop shall run to extract the First Operand and the Operation to be performed.
	{
		//printf ("Char: %c\n", ch);
		if (pos == 0 && flag == 0)		//First character can either be '+', '-' or a digit.
		{
			switch (ch)		//To check if the number is Positive or Negative. Other operators are Invalid.
			{
				case '+':
				case '-': num1->sign = ch;
						  flag = 1;
						  break;
				case '*':
				case '/': printf ("ERROR1: Invalid Expression.\n");
						  break;
			}
			
			//printf ("Sign NUM1: %c and flag: %d\n", num1->sign, flag);
			if (isdigit (ch) && flag == 0)		//If the first character is a Digit, store in the Buffer string and make the number sign as Positive by default.
			{
				num1->temp [pos++] = ch;
				num1->sign = '+';
			}
			else if (flag == 0)		//If any other character appears (say '.' or ';' etc.), the Operation shall be terminated.
			{
				printf ("ERROR2: Invalid Expression.\n");
				return FAILURE;
			}
		}
		else
		{
			if (isdigit (ch))		//To store the digits in Buffer string.
			{
				num1->temp [pos++] = ch;
			}
			else if ((*operator = is_operator (ch)) != UNSUPPORTED)		//Check if the character is an Operator or not. This is for the main Operation to be performed.
			{
				if ((pos == 1) && ((num1->temp [0] == '+') || (num1->temp [0] == '-')))		//If the second character is an operator and 'temp' has no numerical value.
				{
					num1->temp [0] = '\0';		//Initialize 'temp' as '\0'.
					break;
				}
				else	//If the character is an Operator and 'temp' has some numerical value; that is the end of reading the First number.
				{
					break;
				}
			}
			else	//If any other character appears (say '.' or ';' etc.), the Operation shall be terminated.
			{
				printf ("ERROR3: Invalid Expression.\n");
				return FAILURE;
			}
		}
	}
	num1->temp [pos] = '\0';	//End the Temporary Buffer with '\0'.
	num1->size = strlen (num1->temp);	//To get the Size of the First Operand.
	//printf ("Temp1: %s of size: %d and sign: %c\n", num1->temp, num1->size, num1->sign);
	//printf ("Operation: %d\n", *operator);

	pos = 0, flag = 0;
	
	while ((ch = getchar ()) != '\n')		//
	{
		//printf ("%c\n", ch);
		if (pos == 0 && flag == 0)	//First character can either be '+', '-' or a digit.
		{
			switch (ch)		//To check if the number is Positive or Negative. Other operators are Invalid.
			{
				case '+':
				case '-': num2->sign = ch;
						  flag = 1;
						  break;
				case '*':
				case '/': printf ("ERROR4: Invalid Expression.\n");
						  break;
			}
			
			//printf ("Sign NUM2: %c and flag: %d\n", num2->sign, flag);
			if (isdigit (ch) && flag == 0)	//If the first character is a Digit, store in the Buffer string and make the number sign as Positive by default.
			{
				num2->temp [pos++] = ch;
				num2->sign = '+';
			}
			else if (flag == 0)	//If any other character appears (say '.' or ';' etc.), the Operation shall be terminated.
			{
				printf ("ERROR5: Invalid Expression.\n");
				return FAILURE;
			}
		}
		else
		{
			if (isdigit (ch))
			{
				num2->temp [pos++] = ch;
			}
			else
			{
				printf ("ERROR6: Invalid Expression.\n");
				return FAILURE;
			}
		}
	}
	num2->temp [pos] = '\0';
	num2->size = strlen (num2->temp);
	if (num2->size == 0)
		num2->sign = '+';
	//printf ("Temp2: %s of size: %d and sign: %c\n", num2->temp, num2->size, num2->sign);

	if (num1->size == 0)
	{
		strcpy (var1, "0");
	}
	else
	{
		strcpy (var1, num1->temp);
	}

	if (num2->size == 0)
	{
		strcpy (var2, "0");
	}
	else
	{
		strcpy (var2, num2->temp);
	}

	free (num1->temp);
	free (num2->temp);
	num1->temp = NULL;
	num2->temp = NULL;

	return SUCCESS;
}

Operation is_operator (char ch)
{
	Operation opt;
	switch (ch)
	{
		case '+': opt = ADD;
				  break;
		case '-': opt = SUB;
				  break;
		case '*': opt = MUL;
				  break;
		case '/': opt = DIV;
				  break;
		case '%': opt = MOD;
				  break;
		default: opt = UNSUPPORTED;
	}

	return opt;
}

int compare (char* var1, char* var2)
{
	int i = 0;
	while ((var1 [i] != '\0') && (var1 [i] == var2 [i]))
		i++;

	if (var1 [i] > var2 [i])
		return 1;
	else if (var1 [i] == var2 [i])
		return 0;
	else
		return -1;
}
