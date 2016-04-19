#include <stdio.h>
//#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
  char fullCommand[80];
  char command[80];
  int option=0;
  pid_t pid;
  do {
      printf("prompt> ");
    fgets(fullCommand, sizeof fullCommand, stdin);
    sscanf(fullCommand, "%s", command);  //get first command

    if (strcmp(command, "quit") == 0){
      option = 1;
    }
    else{
      option = 2;
    }

    switch(option){
    case 1:
      break;
    case 2:
      pid = fork();
      if (pid == 0){
          printf("child\n");
      }
      else if(pid == -1) {
          printf("failed\n");
      }
      else{
          printf("parent\n");
      }
      break;
    }
  }
  while(option == 3 && option == 1);

  return 0;
}
