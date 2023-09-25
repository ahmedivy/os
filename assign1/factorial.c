#include <stdio.h>

int main()
{
	int num;
	int factorial = 1;
	printf("Enter the number: ");
	scanf("%d", &num);
	for (int i = 1; i <= num; i++)
	{
		factorial *= i;
	}
	printf("The factorial of %d is %d\n", num, factorial);
}
