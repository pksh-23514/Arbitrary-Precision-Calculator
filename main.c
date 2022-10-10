#include "apc.h"

int main()
{
	Dlist *head1, *tail1, *head2, *tail2, *headR, *tailR;
	char option, operator;
	Num num1, num2;
	char var1 [MAX_BUF], var2 [MAX_BUF];
	char signR;

	do
	{
		head1 = tail1 = NULL;
		head2 = tail2 = NULL;
		headR = tailR = NULL;

		int ret = read_and_validate_args (&num1, &num2, var1, var2, &operator);
		if (ret == SUCCESS)
		{
			printf ("INFO: Reading of the Variables is done Successfully.\n");
			printf ("1st Operand: %s of size: %d and sign: %c\n", var1, num1.size, num1.sign);
			printf ("2nd Operand: %s of size: %d and sign: %c\n", var2, num2.size, num2.sign);
			printf ("Operation: %d\n", operator);
		}

		ret = convert (var1, var2, num1.size, num2.size, &head1, &tail1, &head2, &tail2);
		if (ret == SUCCESS)
		{
			printf ("INFO: Conversion of Variables to Numeric Data is done Successfully.\n");
		}

		if (head1 == NULL)
		{
			printf ("INFO: Variable 1 is 0.\n");
			print_list (head2);
		}
		else if (head2 == NULL)
		{
			printf ("INFO: Variable 2 is 0.\n");
			print_list (head1);
		}
		else
		{
			print_list (head1);
			print_list (head2);
		}

		/* To obtain the value of 'signR' and change the Operation if required. */
		ret = result_sign (var1, var2, num1.sign, num2.sign, &signR, &operator);
		printf ("Result sign: %c\n", signR);
		printf ("Operation: %d\n", operator);
		
		switch (operator)
		{
			case ADD:	/* Call the function to perform the Addition operation */
				{
					//ret = addition (&head1, &tail1, &head2, &tail2, &headR, &tailR);
					//if (ret == SUCCESS)
					{
						//printf ("INFO: Addition of the Variables is done Successfully.\n");
					}
				}
				break;
			case SUB:	/* Call the function to perform the Subtraction operation */
				{
					//
					//
					//
				}
				break;
			case MUL:	/* Call the function to perform the Multiplication operation */
				{
					//
					//
					//
				}
				break;
			case DIV:	/* Call the function to perform the Division operation */
				{
					//
					//
					//
				}
				break;
			default: printf ("Invalid Input: Try again...\n");
		}

		printf ("Want to continue? Press [y/Y | n/N]: ");
		scanf ("\n%c", &option);

		getchar ();		//To remove the '\n' generated after scanf() in the Input Buffer.
		printf ("---------------------------------------------------------------\n");
	} while (option == 'y' || option == 'Y');

	return 0;
}
