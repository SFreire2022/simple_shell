#include <stdio.h>
#include<string.h>
/**
 * main - strtok without using strtok
 * Return: Always 0
 */

int main(void)
{
	char str[43] = "This is the strok function without strtok";
	char chr[] = " ";
	int i, j;

	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == chr[0])
			str[i] = '\0';
	}
	for (j = 0; j < i; j++)
	{
		if (str[j] != '\0')
			printf("%c", str[j]);
		else if (str[j - 1] != '\0' && str[j] == '\0')
			printf("\n");
	}
	printf("\n");
	return (0);
}
