#include <stdio.h>
#include <string.h> //strtok
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h> //access
#include <limits.h> //PATH__MAX, NAME_MAX

#include "shell.h"

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

int exists_in_path(char* cmd, char* f_path, size_t f_path_size){
  if(cmd == NULL || strlen(cmd) > NAME_MAX || f_path == NULL || f_path_size <= 0){
    perror("exist_in_path");
    return -1;
  }
  char* path = strdup(getenv((const char*) "PATH"));
  #define MAX_PATH_ELEMENTS 30 //Would be to crazy to have a path that is too long xD
  char* pSection[MAX_PATH_ELEMENTS] = {0};
  //Split the path
  char* token = strtok(path, ":");
  int idx = 0;
  while(token != NULL && idx < MAX_PATH_ELEMENTS -1){
    pSection[idx++] = token;
    token = strtok(NULL, ":");
  }
  pSection[idx] = NULL;
  idx = 0;
  while(pSection[idx] != NULL){
    snprintf(f_path, f_path_size, "%s/%s", pSection[idx], cmd);
    // printf("Will Check: %s", f_path);
    int err = access(f_path, R_OK|X_OK);
    if(err == 0){
      return 0;
    }
    idx++;
  }
  f_path = NULL;
  return -1;
}