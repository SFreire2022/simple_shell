#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
/**
 * main - main
 * Return: child and parent process id's
 */
int main(void)
{
	char ruta[] = "/usr/bin/ls";
	char *args[] = {"ls", "-l", "/tmp", NULL};
	pid_t pid;
	int get_pid;
	int get_ppid;
	int child_process;
	int i = 0;

	while (i < 5)
	{
		pid = fork();
		if (pid == 0)
		{
			if (execve(ruta, args, NULL) == -1)
			{
				printf("ERROR\n");
			}
		}
		else
		{
			get_pid = waitpid(-1, &child_process, 0);
			printf("child_p ID: %d\n", get_pid);
			get_ppid = getppid();
			printf("parent_p ID: %d\n", get_ppid);
		}
	i++;
	}
}
