#include "main.h"

/**
 * main - Main program to get args from comand line or stdin
 * @ac: argument counter.
 * @av: argument vector (strings array).
 * @envp: array of environment vars.
 * Return: if ok return 0.
 */
int main(int ac, __attribute__((unused))char **av, char **envp)
{
	char *line = NULL, *string = NULL;
	size_t len = 0;
	ssize_t nread = 0;
	char **clon_av = NULL;

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
			/* check input to detect EOF */
			check_input(line, nread);
			/* Catch the Interruption signal Ctrl+C and print the prompt again*/
			signal(SIGINT, sig_trap);
			/* proces input */
			clon_av = input_tokenizer(line, nread, " ");
			/* chk builtin cmd */
			if (!chk_builtin(clon_av, line, envp))
			{
			/* Check comand and fork and execve */
			string = chk_fork_execve(clon_av, envp);
			}
			/* clean memory */
			free(line);
			free(clon_av);
			if (string != NULL)
				free(string);
			/* reset for realloc getline */
			line = NULL;
			len = 0;
		}
	}
	return (0);
}
