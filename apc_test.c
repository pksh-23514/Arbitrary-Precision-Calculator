#include "apc_test.h"

Sample data [50];

void create_test ()
{
	/* Addition Test Cases */
	data [0] = {"123456", '+', '+', "987654", '+', "1111110", '+'};
	data [1] = {"123", '-', '+', "25", '+', "98", '-'};

	/*Subtraction Test Cases */
	data [2] = {"1000000", '-', "1", "999999"};
} 
