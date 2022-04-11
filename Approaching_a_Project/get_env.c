#include <stdio.h>
#include <stdlib.h>

/**
 * main - gets an enviroment variable
 * @argc: argument counter
 * @argv: argument vector
 * Return: 0
 */

int main(int __attribute__((unused))argc, char __attribute__((unused))*argv[])
{
	char *my_env_var = getenv("PATH");

	if (my_env_var)
		printf("Var found: %s", my_env_var);
	else
		printf("Var not found.");

	return (0);
}
