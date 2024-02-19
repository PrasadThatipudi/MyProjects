// Test function to test IsPrime()

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "IsPrimeOrNot.c"

void TestIsPrime();

void main()
{
	TestIsPrime();
} 

void TestIsPrime()
{
	char Inputs[30][5] = {"-1", "-3", "0", "1", "97b", "he","8", "24", "9", "235", "2", "3", "5"};
	bool ReturnValues[] = {false, false, false, false, true, false, false, false, false, false, true, true, true};

	int CountOfInputs = 13;
	int Counter;
	int TestStatus = 1;

	for (Counter = 0; Counter < CountOfInputs; Counter++)
	{
		if (IsPrime(Inputs[Counter]) != ReturnValues[Counter])
		{
			TestStatus = 0;
			break;
		}
	}

	if (TestStatus == 1)
	{
		printf("\nAll test cases passed!\n");
	}
	else
	{
		printf("\nFailed(%s)!", Inputs[Counter]);
	}
}
