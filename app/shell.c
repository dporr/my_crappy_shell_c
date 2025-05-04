#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

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