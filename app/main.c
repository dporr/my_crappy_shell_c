#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "builtin.h"
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
    #define MAX_ARGS 15
    char* args[MAX_ARGS] = {0};
    int ret = parse_cmd(input, args, MAX_ARGS);
    if(ret == -1)
    {
      fprintf(stderr, "Failed to parse args!");
      exit(EXIT_FAILURE);
    }
    // printf("Execute: %s\n", args[0]);
    int idx = is_builtin(args[0]);
    if(idx != -1)
    {
      int ret = builtins[idx].handler(0);
    } else {
      /*check the command exists ant its RX by user */
      const char* usr_bin = "/usr/bin";
      char path[4096];
      snprintf(path, sizeof(path), "%s/%s",usr_bin, input);
      int ar = access(path,  F_OK|R_OK|X_OK);
      if( ar == -1) {
        fprintf(stderr, "%s: command not found\n", input);
      }
    }
  }
  return 0;
}

int parse_cmd(char* args, char** pArgs, size_t pArgs_size){
  //split by space -> ["cmd","arg1", "arg2"...]
  if(args == NULL || pArgs == NULL || pArgs_size <= 0) return -1;
  size_t idx = 0;
  char* token = strtok(args, " ");
  while(token != NULL && idx < pArgs_size - 1)
  {
    // printf("TOKEN: %s\n", token);
    pArgs[idx] = token;
    token = strtok(NULL, " ");
    idx++;
  } 
  pArgs[idx] = NULL;
  return idx; // number of parsed argumnets
}

int is_builtin(char* cmd){
  for(int i = 0; i < N_BUILTINS; i++){
    if(strncmp(builtins[i].cmd, cmd, MAX_CMD_LEN) != 0) return -1;
  }

}

int exit_handler(void* status){
  exit(0);
}
struct builtin handle_exit =  {
  .cmd="exit",
  .handler = exit_handler
};

void initialize_builtins() {
  builtins[0] = handle_exit;
}