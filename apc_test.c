#include "apc_test.h"
#include "apc.h"

void run_all_tests ()
{
	int totalPassedCases = 0;

	/* Addition Test Cases */
	{
		Sample test_cases [NUM_TESTCASES] = {{"123456", '+', '+', "987654", '+', "+1111110"}, {"123", '-', '+', "25", '+', "-98"}};

		totalPassedCases += runTests (test_cases, ADD);
	}

	/*Subtraction Test Cases */
	{
		Sample test_cases [NUM_TESTCASES] = {{"10000", '+', '-', "1", '+', "+9999"}, {"987654", '-', '-', "123456", '+', "-1111110"}};

		totalPassedCases += runTests (subtraction_cases, SUB);
	}

	printf("\npassed %d out of %d cases\n", totalPassedCases, (NUM_TESTCASES * 2));
}

// runs tests for given sample test cases and operation.
// operation - aka function under test (fut)

void run_tests (Sample inputArray [], Operation fut)
{
	int casesPassed = 0, ret;
	char operator = fut, signR, res [MAX_BUF];
	Dlist *head1, *tail1, *head2, *tail2, *headR, *tailR;

	for (int i = 0; i < NUM_TESTCASES; i++)
	{
		head1 = tail1 = NULL;
		head2 = tail2 = NULL;
		headR = tailR = NULL;

		convert (inputArray [i].operand1, inputArray [i].operand2, strlen (inputArray [i].operand1), strlen (inputArray [i].operand2), &head1, &tail1, &head2, &tail2);

		result_sign (inputArray [i].operand1, inputArray [i].operand2, inputArray [i].sign1, inputArray [i].sign2, &signR, &operator);
		
		switch (operator)
		{
			case ADD: addition (&head1, &tail1, &head2, &tail2, &headR, &tailR);
					  break;
			case SUB: subtraction (&head1, &tail1, &head2, &tail2, &headR, &tailR);
					  break;
		}

		ret = LL_to_str (headR, tailR, signR, res);

		if ((strncmp (inputArray [i].result, res, ret) == 0)
				casesPassed += 1;
	}

	return casesPassed;
}
