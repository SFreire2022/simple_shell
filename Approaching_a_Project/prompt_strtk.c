#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#define TRUE (1 == 1)

void _IRQ(int sig);

void _IRQ(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n$ ", 3);
}

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
	ssize_t nread = 0, i = 0, j;
/*	char *prompt = "user@host:/ruta/completa";*/
	char **clon_av = NULL;
	char sep[] = " "; /* Separator */

	if (ac > 1)
	{
		/* Read from file mode function*/
		/* For future development */
		printf("Reading from file isn't developed yet ;)\n");
	}
	else
	{
		while (TRUE)
		{
			/* interactive function */
			/* Must capture Ctrl+c signal to avoid interuption */
			/* before free the thast malloc perfomed by getline */
			if (nread == EOF)
			{
				if (isatty(STDIN_FILENO))
					write(STDOUT_FILENO, "\n", 1);
/*				free(line);*/
				exit(EXIT_SUCCESS);
			}
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "$ ", 2);
			nread = getline(&line, &len, stdin);
			signal(SIGINT, _IRQ);
			if (strcmp(line, "exit\n") == 0)
			{
				free(line);
				exit(EXIT_SUCCESS);
			}
			/* Tokenizer function */
			for (i = 0; i <= nread; i++)
			{
				if (*(line + i) == sep[0])
					*(line + i) = '\0';
				if (i == nread - 1)
					*(line + i) = '\0';
			}
			j = 1;
			for (i = 1; i <= nread; i++)
			{
				/* Malloc pointers to strings */
				if (line[i - 1] == '\0' && line[i] != '\0')
				{
					j++;
				}
			}
			clon_av = malloc(j * sizeof(*clon_av));
			j = 0;
			for (i = 1; i <= nread; i++)
			{
				if ((i - 1) == 0 && line[i - 1] != '\0')
				{
					clon_av[j] = &line[i - 1];
					printf("token[%ld] -> %s\n", j, clon_av[j]);
					j++;
				}
				if (line[i - 1] == '\0' && line[i] != '\0')
				{
					clon_av[j] = &line[i];
					printf("token[%ld] -> %s\n", j, clon_av[j]);
					j++;
				}
			}
			write(STDOUT_FILENO, line, nread);
			free(line);
			free(clon_av);
			line = NULL;
			len = 0;
		}
	}
	exit(EXIT_SUCCESS);
}
