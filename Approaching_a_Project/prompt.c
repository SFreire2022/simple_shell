#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#define TRUE (1 == 1)

/**
 * main - Main program to get args from comand line or stdin
 * @ac: argument counter.
 * @av: argument vector (strings array).
 * Return: if ok return 0.
 */
int main(int ac, char **av)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread, i;
	char *prompt = "user@host:/ruta/completa";
	char *token = NULL;

	if (ac > 1)
	{
		/* Stand alone mode function*/
		/* First argument is executable name only */
		printf("exe name=%s\n", av[0]);

		for (i = 1; av[i] != NULL; i++)
			printf("arg%ld=%s\n", i, av[i]);
	}
	else
	{
		while (TRUE)
		{
			/* interactive function */
			/* Must capture Ctrl+c signal to avoid interuption */
			/* before free the thast malloc perfomed by getline */
			printf("%s$", prompt);
			nread = getline(&line, &len, stdin);
			if (strcmp(line, "exit\n") == 0)
			{
				free(line);
				exit(EXIT_SUCCESS);
			}
			/*set token*/
			token = strtok(line, " ");
			/* Keep printing tokens while one of the */
			/* delimiters present in line[].*/
			while (token != NULL)
			{
				printf("%s\n", token);
				token = strtok(NULL, " ");
			}
			fwrite(line, nread, 1, stdout);
			free(line);
			line = NULL;
			len = 0;
		}
	}
	exit(EXIT_SUCCESS);
}
