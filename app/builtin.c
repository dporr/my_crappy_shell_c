#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h> //PATH__MAX, NAME_MAX

#include "builtin.h"

struct builtin builtins[N_BUILTINS];

int is_builtin(char* cmd){
    // printf("Truing... %s", cmd);
    for(int i = 0; i < N_BUILTINS; i++){
      if(strncmp(builtins[i].cmd, cmd, MAX_CMD_LEN) == 0) return i;
    }
    return -1;
  }
  
  int exit_handler(void* vargs, size_t arg_len){
    /*Check that status makes sense */
    if(arg_len != 1) return -1;
    char** argv = (char**) vargs;
    int err = atoi(argv[0]);
    exit(err);
  }
  
  int echo_handler(void* vargs, size_t arg_len){
    char** argv = (char**) vargs;
    for(int i = 0; i < arg_len; i++)
      printf("%s ", argv[i]); //TODO: Nasty space after the last arg... fix, someday.
    printf("\n");
  }
  
  int type_handler(void* vargs, size_t arg_len){
    if(vargs == NULL || arg_len <= 0) return -1;
    char** argv = (char**) vargs;
    int idx = -1;
    if(idx = is_builtin(argv[0]) != -1){
      printf("%s is a shell builtin\n", argv[0]);
      return idx;
    }
    //Check if cmd is in path
    char f_path[PATH_MAX] = {0};
    int err = exists_in_path(argv[0], f_path, PATH_MAX);
    if( err == -1 || f_path == NULL) {
      fprintf(stderr, "%s: not found\n", argv[0]);
      return -1;
    }
    printf("%s is %s\n", argv[0], f_path);
    return idx;
  }
  
  void initialize_builtins() {
    builtins[0] = (struct builtin) {.cmd="exit", .handler = exit_handler};
    builtins[1] = (struct builtin) {.cmd="echo", .handler = echo_handler};
    builtins[2] = (struct builtin) {.cmd="type", .handler = type_handler};
  }