#include "main.h"

/**
 * main - Main program to get args from comand line or stdin
 * @ac: argument counter.
 * @av: argument vector (strings array).
 * Return: if ok return 0.
 */
int main(int ac, char **av, char **env)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread = 0, i = 0, j;
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
			/* Check interactive or non interactive */
			check_mode();
			/* Read the input */
			nread = getline(&line, &len, stdin);
			/* Catch the Interruption signal Ctrl+C and print the prompt again*/
			signal(SIGINT, sig_trap);
			/* proces input */
			clon_av = input_tokenizer(&line, nread, " ");
			/* Check comand and fork and execve */
			chk_fork_execve(&clon_av);
		}
	}
}
