#ifndef APC_TEST_H
#define APC_TEST_H

#define NUM_TESTCASES 11
#define MAX_BUF 500

struct test
{
	char operand1 [MAX_BUF];
	char sign1;
	char operation;
	char operand2 [MAX_BUF];
	char sign2;
	char result [MAX_BUF];
};

typedef struct test Sample;

/* Function Declarations */

void run_all_tests ();

int run_tests (Sample [], char);
#endif
