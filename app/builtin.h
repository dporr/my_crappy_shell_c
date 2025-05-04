#ifndef CSHELL_BUILTIN_H
#define CSHELL_BUILTIN_H

#define N_BUILTINS 2
#define MAX_CMD_LEN 15
struct builtin {
    char cmd[MAX_CMD_LEN];
    int (*handler)(void*, size_t);
};

/*TODO: Make this a hashmap for efficient access*/
struct builtin builtins[N_BUILTINS];
void initialize_builtins();
int is_builtin(char* cmd);
int exit_handler(void* status, size_t arg_len);
int echo_handler(void* v_args, size_t arg_len);

#endif