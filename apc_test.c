#include "apc_test.h"
#include "apc.h"

void run_all_tests ()
{
	int totalPassedCases = 0;

	/* Addition Test Cases */
	{
		Sample test_cases [NUM_TESTCASES] = {{"123456", '+', '+', "987654", '+', "+1111110"}, {"123", '+', '+', "25", '+', "+148"}, {"9999", '+', '+', "1", '+', "+10000"}, 
{"0", '+', '+', "0", '-', "0"}, {"9999999999999999", '-', '+', "123456789", '+', "-9999999876543210"}, {"123", '-', '+', "25", '+', "-98"}, {"234679", '-', '+', "4659129", '-', "-4893808"}, 
{"9999", '-', '+', "", '+', "-9999"}, {"689318874", '+', '+', "897545768", '-', "-208226894"}, {"", '+', '+', "9999", '+', "+9999"}, {"9999", '-', '+', "9999", '+', "0"},
{"654123987321456987", '+', '+', "999999999999", '-', "+654122987321456988"}, {"754621326859", '+', '+', "123456789987456321", '-', "-123456035366129462"}, 
{"99999999999999999999999", '+', '+', "1111111111111111111111", '+', "+101111111111111111111110"}, {"00000000000000000", '+', '+', "00000000000000000000000", '+', "0"}};

		totalPassedCases += run_tests (test_cases, ADD);
	}

	/*Subtraction Test Cases */
	{
		//Sample test_cases [NUM_TESTCASES] = {{"10000", '+', '-', "1", '+', "+9999"}, {"987654", '-', '-', "123456", '+', "-1111110"}};

		//totalPassedCases += run_tests (test_cases, SUB);
	}

	printf("Passed %d Out of %d Cases.\n", totalPassedCases, (NUM_TESTCASES));
}

// runs tests for given sample test cases and operation.
// operation - aka function under test (fut)

int run_tests (Sample inputArray [], char fut)
{
	int casesPassed = 0, ret;
	char operator, signR, res [MAX_BUF];
	Dlist *head1, *tail1, *head2, *tail2, *headR, *tailR;

	//printf ("Operator before: %d\n", operator);
	for (int i = 0; i < NUM_TESTCASES; i++)
	{
		operator = fut;
		//printf ("Iteration: %d\n", i);
		head1 = tail1 = NULL;
		head2 = tail2 = NULL;
		headR = tailR = NULL;

		convert (inputArray [i].operand1, inputArray [i].operand2, strlen (inputArray [i].operand1), strlen (inputArray [i].operand2), &head1, &tail1, &head2, &tail2);

		//printf ("Inside Result fn():\n");
		result_sign (inputArray [i].operand1, inputArray [i].operand2, inputArray [i].sign1, inputArray [i].sign2, &signR, &operator);
		//printf ("Operator after: %d\n", operator);
		
		switch (operator)
		{
			case ADD: addition (&head1, &tail1, &head2, &tail2, &headR, &tailR);
					  break;
			case SUB: ret = compare (inputArray [i].operand1, inputArray [i].operand2);
					  if (ret >= 0)
						  subtraction (&head1, &tail1, &head2, &tail2, &headR, &tailR);
					  else
						  subtraction (&head2, &tail2, &head1, &tail1, &headR, &tailR);
					  break;
		}

		memset (res, '\0', 500);
		ret = LL_to_str (headR, tailR, signR, res) + 1;

		if ((strncmp (inputArray [i].result, res, ret) == 0))
				casesPassed += 1;
		else
		{
			printf ("Operand1: %s Sign1: %c\t", inputArray [i].operand1, inputArray [i].sign1);
			printf ("Operation: %c\t", inputArray [i].operation);
			printf ("Operand2: %s Sign2: %c\n", inputArray [i].operand2, inputArray [i].sign2);
			printf ("Expected Result: %s\n", inputArray [i].result);
			printf ("Calculated Result: %s\n\n", res);
		}

	}

	return casesPassed;
}
