#include "main.h"

/**
 * check_mode - Function to check interacting mode with the shell
 * @nread: Returned read value frim getline
 * @clon_av: array to be freed if first element is == exit.
 * @line: string to be freed if command is exit.
 */
void check_mode(ssize_t nread, char **clon_av, char *line)
{
	if (nread == EOF)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "\n", 1);
		free(line);
		free(clon_av);
		exit(EXIT_SUCCESS);
	}
	if (isatty(STDIN_FILENO))
		print_prompt();
}

/**
 * print_prompt - Function to generate the string and print the prompt
 */
void print_prompt(void)
{
	char *str1 = getenv("USER");
	char *str2 = "@";
	char *str3 = getenv("HOSTNAME");
	char *str4 = ":";
	char *str5 = getenv("PWD");
	char *str6 = "$ ";

	dprintf(STDOUT_FILENO, "%s%s%s%s%s%s", str1, str2, str3, str4, str5, str6);
}

/**
 * sig_trap - Function to trap the signal Ctrl+C and print_prompt again
 * @sig: Signal value (unused)
 */
void sig_trap(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	print_prompt();
}

/**
 * input_tokenizer - Function to split input string
 * into tokens using a given separator.
 * @line: Pointer to address of string to split.
 * @nread: length of string
 * @sep: argument as a separator.
 * Return: Address of mallocd array of tokens.
 */
char **input_tokenizer(char *line, ssize_t nread, const char *sep)
{
	char **clon_av = NULL;
	char *nullstr = NULL;
	ssize_t i = 0, j = 0;

	for (i = 0; i <= nread; i++)
	{
		if (*(line + i) == sep[0])
			*(line + i) = '\0';
		if (i == nread - 1)
			*(line + i) = '\0';
	}
	for (j = 1, i = 1; i <= nread; i++)
	{
		if (line[i - 1] == '\0' && line[i] != '\0')
		{
			j++;
		}
	}
	clon_av = malloc((j + 3) * sizeof(*clon_av));
	if (clon_av == NULL)
	{
		dprintf(2, "Error allocating memory for array of arguments\n");
		return (clon_av);
	}
	clon_av[j] = &nullstr[0];
	for (j = 0, i = 1; i <= nread; i++)
	{
		if ((i - 1) == 0 && line[i - 1] != '\0')
		{
			clon_av[j] = &line[i - 1];
			j++;
		}
		if (line[i - 1] == '\0' && line[i] != '\0')
		{
			clon_av[j] = &line[i];
			j++;
		}
	}
	return (clon_av);
}

/**
 * chk_fork_execve - Function to check command and execute as a child process
 * @clon_av: array of command and arguments.
 * @envp: array of env vars.
 * Return: 0 if ok.
 */
char *chk_fork_execve(char **clon_av, char **envp)
{
	pid_t pid;
	int status;
	char *string = NULL;

	string = chk_command(clon_av[0]);
	if (string == NULL)
		dprintf(STDERR_FILENO, "%s: command not found\n", clon_av[0]);
	else
	{
		pid = fork();
		if (pid == 0)
		{
			if (execve(string, clon_av, envp) == -1)
				dprintf(STDERR_FILENO, "%s: ERROR\n", clon_av[0]);
		}
		wait(&status);
	}
	return (string);
}
