#include "main.h"

/**
 * check_mode - Function to check interacting mode with the shell
 * @nread: Returned read value frim getline
 */
void check_mode(ssize_t nread)
{
	if (nread == EOF)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "\n", 1);
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
	char *str3 = getenv("HOST");
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
	/* Malloc pointers to strings */
	clon_av = malloc(j * sizeof(*clon_av));
	if (clon_av == NULL)
	{
		dprintf(2, "Error allocating memory for array of arguments\n");
		return (&clon_av);
	}
	for (j = 0, i = 1; i <= nread; i++)
	{
		if ((i - 1) == 0 && line[i - 1] != '\0')
		{
			clon_av[j] = &line[i - 1];
			printf("token[%ld] -> %s\n", j, clon_av[j]);/*for debug*/
			j++;
		}
		if (line[i - 1] == '\0' && line[i] != '\0')
		{
			clon_av[j] = &line[i];
			printf("token[%ld] -> %s\n", j, clon_av[j]);/*for debug*/
			j++;
		}
	}
	return (&clon_av);
}

/**
 * chk_fork_execve - Function to check command and execute as a child process
 * @clon_av: array of command and arguments.
 * Return: 0 if ok.
 */
char *chk_fork_execve(char **clon_av)
{
	pid_t pid;
	int status;
	char *string = NULL;

	string = chk_command(clon_av[0]);
	if (string == NULL)
		dprintf(STDERR_FILENO, "%s: command not found", clon_av[0]);
	else
	{
		pid = fork();
		if (pid == 0)
		{
			if (execve(string, clon_av, envp) == -1)
				dprintf(STDERR_FILENO, "%s: command not found", clon_av[0]);
		}
		wait(&status);
	}
	return (&string);
}

/**
 * chk_command - Function to check command and return string including path
 * @command: string to check if exixt and is a command.
 * Return: Address to allocated string containig .
 */
char *chk_command(char *command)
{
	struct stat st;
	char **path = NULL;
	char *env_path = getenv("PATH"), *string = NULL;
	int length = strlen(env_path), i, flag = 0;

	string = malloc(sizeof(char) * 1024);
	path = input_tokenizer(&env_path, length, ":");
	for (i = 0; path[i] != NULL; i++)
	{
		strcpy(string, path[i]);
		strcat(string, "/");
		strcat(string, command);
		if (stat(string, &st) == 0)
		{
			flag = 1;
			free(path);
			return (&string);
		}
	}
	if (flag == 0)
	{
		free(string);
		free(path);
		return (NULL);
	}
}

/**
 * chk_builtin - Function to check command
 * @clon_av: array to be freed if first element is == exit.
 * @line: string to be freed if command is exit.
 * @envp: Array of environment vars.
 */
void chk_builtin(char **clon_av, char *line, char **envp)
{
	int i = 0;

	if (strcmp(clon_av[0], "exit") == 0)
	{
		free(line);
		free(clon_av);
		exit(EXIT_SUCCESS);
	}
	if (strcmp(clon_av[0], "env") == 0)
	{
		for (i = 0; envp[i]; i++)
			dprintf(STDERR_FILENO, "%s\n", envp[i]);
	}
}
