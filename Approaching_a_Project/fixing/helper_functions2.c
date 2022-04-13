#include "main.h"

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
	int length = strlen(env_path), i;

	string = malloc(sizeof(char) * 1024);
	if (stat(command, &st) == 0)
	{
		strcpy(string, command);
		return (string);
	}
	path = input_tokenizer(env_path, length, ":");
	for (i = 0; path[i] != NULL; i++)
	{
		strcpy(string, path[i]);
		strcat(string, "/");
		strcat(string, command);
		if (stat(string, &st) == 0)
		{
			free(path);
			return (string);
		}
	}
	free(string);
	free(path);
	return (NULL);
}

/**
 * chk_builtin - Function to check command
 * @clon_av: array to be freed if first element is == exit.
 * @line: string to be freed if command is exit.
 * @envp: Array of environment vars.
  * Return: 1 if builtin command was detected and executed.
 */
int chk_builtin(char **clon_av, char *line, char **envp)
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
			dprintf(STDOUT_FILENO, "%s\n", envp[i]);
		/* avoid try to exec bin */
		return (1);
	}
	if (strcmp(clon_av[0], "help") == 0)
	{
		dprintf(STDOUT_FILENO, "This is the help example\n");
		/* avoid try to exec bin */
		return (1);
	}
	return (0);
}

/**
 * check_input - Function to check input to detect EOF, free buffer and exit
 * @line: buffer to be freed if EOF was detected
 * @nread: Returned read value from getline
 */
void check_input(char *line, ssize_t nread)
{
	if (nread == EOF)
	{
		free(line);
		exit(EXIT_SUCCESS);
	}
}
