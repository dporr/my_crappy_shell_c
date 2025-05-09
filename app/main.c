#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "builtin.h"
#include <limits.h> //PATH__MAX, NAME_MAX

#include "shell.h"

int main() {
  initialize_builtins();
  for(;;) {
    // Uncomment this block to pass the first stage
    printf("$ ");
    fflush(stdout);
    // Wait for user input
    char input[100];
    fgets(input, 100, stdin);
    input[strcspn(input, "\n")] = '\0';
    char* args[MAX_ARGS] = {0};
    int arg_len = parse_cmd(input, args, MAX_ARGS);
    if(arg_len == -1)
    {
      fprintf(stderr, "Failed to parse args!");
      exit(EXIT_FAILURE);
    }
    // printf("Execute: %s\n", args[0]);
    int idx = is_builtin(args[0]);
    char f_path[PATH_MAX] = {0};
    if(idx != -1)
    {
      int ret = builtins[idx].handler((void*) &args[1],
       /*ignore the comand name at idx 0*/ --arg_len);
       //TODO: Do error checking after calling the handler
    } else if(exists_in_path(args[0],f_path, PATH_MAX-1) != -1){
      /*for and execve inside child */
      execvp_child(args[0], &args[0]);
    }else{
        fprintf(stderr, "%s: command not found\n", args[0]);
    }
  }
  return 0;
}


