#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#define TRUE (1 == 1)

void check_mode(ssize_t nread);
void sig_trap(int sig);
void print_prompt(void);
char **input_tokenizer(char *line, ssize_t nread, char *sep);
char *chk_fork_execve(char **clon_av);
char *chk_command(char *command);
void chk_builtin(char **clon_av, char *line, char **envp);

#endif
