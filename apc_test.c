#include "apc_test.h"
#include "apc.h"

void run_all_tests ()
{
	int totalPassedCases = 0;

	/* Addition Test Cases */
	{
		Sample test_cases [NUM_TESTCASES] = {{"123456", '+', '+', "987654", '+', "+1111110"}, {"123", '+', '+', "25", '+', "+148"}, {"9999", '+', '+', "1", '+', "+10000"}, 
{"0", '+', '+', "0", '-', "0"}, {"9999999999999999", '-', '+', "123456789", '+', "-9999999876543210"}, {"123", '-', '+', "25", '+', "-98"}, {"234679", '-', '+', "4659129", '-', "-4893808"}, 
{"9999", '-', '+', "", '+', "-9999"}, {"689318874", '+', '+', "897545768", '-', "-208226894"}, {"", '+', '+', "9999", '+', "+9999"}, {"99999", '-', '+', "99999", '+', "0"}, 
{"654123987321456987", '+', '+', "999999999999", '-', "+654122987321456988"}, {"754621326859", '+', '+', "123456789987456321", '-', "-123456035366129462"}, 
{"99999999999999999999999", '+', '+', "1111111111111111111111", '+', "+101111111111111111111110"}, {"00000000000000000", '+', '+', "00000000000000000000000", '+', "0"}};

		totalPassedCases += run_tests (test_cases, ADD);
	}

	/*Subtraction Test Cases */
	{
		Sample test_cases [NUM_TESTCASES] = {{"10000", '+', '-', "1", '+', "+9999"}, {"987654", '-', '-', "123456", '+', "-1111110"}, {"19999999999", '-', '-', "1", '+', "-20000000000"}, 
{"987456321123654789", '+', '-', "951753862248147963", '+', "+35702458875506826"}, {"9999", '-', '-', "", '+', "-9999"}, {"0", '-', '-', "00000000000000000", '-', "0"}, 
{"123", '-', '-', "98", '+', "-221"}, {"99999999999999999999999", '-', '-', "1111111111111111111111", '+', "-101111111111111111111110"}, {"99999", '-', '-', "11111", '-', "-88888"}, 
{"987456321123654789", '+', '-', "159753654852", '+', "+987456161369999937"}, {"654789321", '+', '-', "10000000000000000000000000000000", '+', "-9999999999999999999999345210679"}, 
{"0", '-', '-', "0", '+', "0"}, {"99999", '-', '-', "99999", '-', "0"}, {"456321", '+', '-', "789456", '+', "-333135"}, {"987456321", '-', '-', "123456789", '-', "-863999532"}};

		totalPassedCases += run_tests (test_cases, SUB);
	}

	/* Multiplication Test Cases */
	{
		Sample test_cases [NUM_TESTCASES] = {{"7", '+', '*', "10000001", '+', "+70000007"}, {"0", '-', '*', "0000000000000", '+', "0"}, {"11111111111", '+', '*', "11111", '+', "+123455555554321"}, 
{"99999", '+', '*', "99999999999999", '+', "+9999899999999900001"}, {"123456789", '-', '*', "852147963", '-', "+105203451264870807"}, {"98745", '-', '*', "369852147", '+', "-36521050255515"}, 
{"586172354997", '+', '*', "123456987753159852456", '-', "-72367073252105498442326574322632"}, {"", '+', '*', "123456", '-', "0"}, {"123456", '-', '*', "", '+', "0"}, 
{"11111111111111111111", '+', '*', "999999999999999999999", '+', "+11111111111111111110988888888888888888889"}, {"010", '+', '*', "101", '-', "-1010"}, 
{"123456789", '+', '*', "987456321", '+', "+121908186668413269"}, {"159753", '-', '*', "123698741", '-', "+19761244970973"}, {"77777777", '+', '*', "11111", '+', "+864188880247"}, 
{"1231234", '+','*', "12343", '+', "+2854121262"}};

		totalPassedCases += run_tests (test_cases, MUL);
	}
	
	printf("Passed %d Out of %d Cases.\n", totalPassedCases, (NUM_TESTCASES * 3));
}

/* Runs tests for the given Sample Test cases and a particular Operation.
   Operation -> Function under Test ('fut').
*/
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
			case MUL: multiplication (&head1, &tail1, &head2, &tail2, &headR, &tailR);
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
