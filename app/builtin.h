#ifndef CSHELL_BUILTIN_H
#define CSHELL_BUILTIN_H

#define N_BUILTINS 1
#define MAX_CMD_LEN 15
struct builtin {
    char cmd[MAX_CMD_LEN];
    int (*handler)(void*);
};

/*TODO: Make this a hashmap for efficient access*/
struct builtin builtins[N_BUILTINS];
void initialize_builtins();
int is_builtin(char* cmd);
int exit_handler(void* status);


#endif