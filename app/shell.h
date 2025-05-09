#ifndef CSHELL_SHELL_H
#define CSHELL_SHELL_H

#define SP  " " //separator
#define MAX_ARGS 15
int parse_cmd(char* args, char** pArgs, size_t pArgs_size);
int exists_in_path(char* cmd, char* result, size_t result_s);
int execvp_wrapper(const char *file, char *const argv[]);
#endif