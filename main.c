#include "apc.h"
#include "apc_test.h"

int main()
{
#if 1
	Dlist *head1, *tail1, *head2, *tail2, *headR, *tailR;
	char option, operator;
	Num num1, num2;
	char var1 [MAX_BUF], var2 [MAX_BUF], res [MAX_BUF];
	char signR;
	int ret;

	do
	{
		head1 = tail1 = NULL;
		head2 = tail2 = NULL;
		headR = tailR = NULL;

		ret = read_and_validate_args (&num1, &num2, var1, var2, &operator);
		//printf ("Return: %d\n", ret);
		if (ret == SUCCESS)
		{
			printf ("INFO: Reading of the Variables is done Successfully.\n");
			printf ("1st Operand: %s of size: %d and sign: %c\n", var1, num1.size, num1.sign);
			printf ("2nd Operand: %s of size: %d and sign: %c\n", var2, num2.size, num2.sign);
			printf ("Operation: %d\n", operator);
		
			ret = convert (var1, var2, num1.size, num2.size, &head1, &tail1, &head2, &tail2);
			if (ret == SUCCESS)
			{
				printf ("INFO: Conversion of Variables to Numeric Data is done Successfully.\n");
				if (head1 == NULL)
				{
					printf ("INFO: Variable 1 is 0.\n");
					print_list (head2);
				}
				else if (head2 == NULL)
				{
					print_list (head1);
					printf ("INFO: Variable 2 is 0.\n");
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
							ret = addition (&head1, &tail1, &head2, &tail2, &headR, &tailR);
							if (ret == SUCCESS)
							{
								printf ("INFO: Addition of the Variables is done Successfully.\n");
							}
							else
							{
								printf ("ERROR: Addition Operation Failed.\n");
							}
						}
						break;
					case SUB:	/* Call the function to perform the Subtraction operation */
						{
							ret = compare (var1, var2);
							if (ret >= 0)
							{
								ret = subtraction (&head1, &tail1, &head2, &tail2, &headR, &tailR);
							}
							else
							{
								ret = subtraction (&head2, &tail2, &head1, &tail1, &headR, &tailR);
							}

							if (ret == SUCCESS)
							{
								printf ("INFO: Subtraction of the Variables is done Successfully.\n");
							}
							else
							{
								printf ("ERROR: Subtraction Operation Failed.\n");
							}
						}
						break;
					case MUL:	/* Call the function to perform the Multiplication operation */
						{
							ret = multiplication (&head1, &tail1, &head2, &tail2, &headR, &tailR);
							if (ret == SUCCESS)
							{
								printf ("INFO: Multiplication of the Variables is done Successfully.\n");
							}
							else
							{
								printf ("ERROR: Multiplication Operation Failed.\n");
							}
						}
						break;
					case DIV:	/* Call the function to perform the Division operation */
						{
							ret = division (&head1, &tail1, &head2, &tail2, &headR, &tailR);
							//
							//
						}
						break;
					default: printf ("Invalid Input: Try again...\n");
				}

				printf ("Result: ");
				print_list (headR);
				memset (res, '\0', 500);
				ret = LL_to_str (headR, tailR, signR, res);
				printf ("Result: %s\n", res);
				printf ("Size: %d\n", ret);
			}
			else
			{
				if ((head1 == NULL) && (head2 == NULL))
				{
					printf ("INFO: Variable 1 is 0.\n");
					printf ("INFO: Variable 2 is 0.\n");

					if ((operator == ADD) || (operator == SUB) || (operator == MUL))
					{
						printf ("INFO: Result is 0.\n");
					}
					else if (operator == DIV)
					{
						printf ("INFO: Result is Undetermined.\n");
					}
				}
			}
		}
		
		__fpurge (stdin);
		printf ("Want to continue? Press [y/Y | n/N]: ");
		option = getchar ();
			
		getchar ();		//To remove the '\n' generated after scanf() in the Input Buffer.
		printf ("---------------------------------------------------------------\n");		
	} while (option == 'y' || option == 'Y');
#endif

	//run_all_tests ();
	return 0;
}
