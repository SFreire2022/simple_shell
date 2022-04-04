#include <stdio.h>
#include <string.h>

/**
 * main - Main program to tokenize args from comand line
 * Return: if ok return 0.
 */
int main(__attribute__((unused))int ac, char **av)
{
	char *str = av[1];

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
