#include "apc_test.h"
#include "apc.h"
#define NUM_TESTCASES 10;
Sample addition_tests[NUM_TESTCASES];
Sample subraction_tests[NUM_TESTCASES];

void create_test ()
{
	/* Addition Test Cases */
	{
		Sample data [50] = {{"123456", '+', '+', "987654", '+', "+1111110"}, {"123", '-', '+', "25", '+', "-98"}};
	}

	/*Subtraction Test Cases */
	{
		Sample data [50] = {{"1000000", '+', '-', "1", '+', "+999999"}};
	}
} 


void RunAllTests() {
	int totalPassedCases = 0;
	totalPassedCases += runTests(addition_cases, addition);
	totalPassedCases += runTests(subtraction_cases, subtraction);
	printf("\npassed %d out of %d cases\n", totalPassedCases, NUM_TESTCASES*2);
}

typedef int (*operation) (Dlist**, Dlist**, Dlist**, Dlist**, Dlist**, Dlist**);

// runs tests for given sample test cases and operation 
// operation - aka function under test (fut)
void runTests(sample[] inputArray, operation fut) {
	int casesPassed = 0;
	for (int i = 0; i < NUM_TESTCASES; i++) {
		input = inputArray[i];
		// convert to ll and call the operation
		// int result  = *fut(input.op1, input.op2, input.Operator);
		// compare result and expected output in case, increment cases passed
		// pretty print accordingly - both positive and negative scenarios
	}
	return casesPassed;
}
