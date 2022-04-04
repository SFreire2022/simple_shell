#include <stdio.h>
#include <string.h>

/**
 * main - Main program to tokenize args from comand line
 * Return: if ok return 0.
 */
int main(void)
{
	char str[] = "Simple Shell Project by Martín and Seba";

    /* Returns first token* */
	char *token = strtok(str, " ");

	/* Keep printing tokens while one of the */
	/* delimiters present in str[].*/
	while (token != NULL)
	{
		printf("%s\n", token);
		token = strtok(NULL, " ");
	}

	return (0);
}
