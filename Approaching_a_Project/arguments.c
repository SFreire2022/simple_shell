#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * main - Main program to get args from comand line
 * @ac: argument counter.
 * @av: argument vector (strings array).
 * Return: if ok return 0.
 */
int main(int ac, char **av)
{
	int i = 0;

	/* First argument is executable name only */
	printf("exe name=%s\n", av[0]);

	for (i = 1; av[i] != NULL; i++)
		printf("arg%d=%s\n", i, av[i]);

		return (0);
}
