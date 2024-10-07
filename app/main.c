#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

int main() {
  // Uncomment this block to pass the first stage
  printf("$ ");
  fflush(stdout);
  
  // Wait for user input
  char input[100];
  fgets(input, 100, stdin);
  input[strcspn(input, "\n")] = '\0';
  /*check the command exists ant its RX by user */
  const char* usr_bin = "/usr/bin";
  char path[4096];
  snprintf(path, sizeof(path), "%s/%s",usr_bin, input);
  int ar = access(path,  F_OK|R_OK|X_OK);
  if( ar == -1) {
    printf("%s: command not found\n", input);
    //perror("access");
    exit(errno);
  }

  return 0;
}
