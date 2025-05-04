#ifndef CSHELL_SHELL_H
#define CSHELL_SHELL_H

#define SP  " " //separator
#define MAX_ARGS 15
int parse_cmd(char* args, char** pArgs, size_t pArgs_size);

#endif