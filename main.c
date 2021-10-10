#include "sh.h"
#include <signal.h>
#include <stdio.h>

void sig_handler(int signum); 

int main( int argc, char **argv, char **envp )
{
  /* put signal set up stuff here */
  signal(SIGINT,sig_handler);     //ctrl-c
  signal(SIGTSTP,sig_handler);    //ctrl-z

  return sh(argc, argv, envp);
}

void sig_handler(int signum)
{
  /* define your signal handler */
  switch(signum){
    case SIGINT:
      printf("caught C\n");
      break;
    case SIGTSTP:
      printf("caught Z\n");
      break;
    default:
      printf("caught a signal\n");
  }
}

