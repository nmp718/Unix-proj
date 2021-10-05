// Nick was here
// And Jon too

#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>
#include <pwd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include "sh.h"

#define BUFFERMAX 128

char buffer[BUFFERMAX];

int sh( int argc, char **argv, char **envp )
{
  char *prompt = calloc(PROMPTMAX, sizeof(char));
  char *commandline = calloc(MAX_CANON, sizeof(char));
  char *command, *arg, *commandpath, *p, *pwd, *owd;
  char **args = calloc(MAXARGS, sizeof(char*));
  int uid, i, status, argsct, go = 1;
  struct passwd *password_entry;
  char *homedir;
  struct pathelement *pathlist;

  uid = getuid();
  password_entry = getpwuid(uid);               /* get passwd info */
  homedir = password_entry->pw_dir;		/* Home directory to start
						  out with*/
  
  if ( (pwd = getcwd(NULL, PATH_MAX+1)) == NULL )
  {
    perror("getcwd");
    exit(2);
  }
  owd = calloc(strlen(pwd) + 1, sizeof(char));
  memcpy(owd, pwd, strlen(pwd));
  prompt[0] = ' '; prompt[1] = '\0';

  /* Put PATH into a linked list */
  pathlist = get_path();

  char* arrows = ">> ";       // Prompt is for a user prefix for the working directory

  const char s[2] = " ";      // used for strtok to chop up strings
  //char *token;  

  char *exitval = "exit";     // Used for a string comparison for exit

  while ( go )
  {
    // print your prompt 

    pwd=getcwd(NULL, 0);      // Finds the current working directory
    printf("\n[%s]", pwd);      // Prints the current working directory
    printf("%s", arrows);       // arrows at the end of the directory

    /* get command line and process */

    /* check for each built in command and implement */
    
    
    if (fgets(buffer, BUFFERMAX, stdin) != NULL) {
      if (buffer[strlen(buffer) - 1] == '\n')buffer[strlen(buffer) - 1] = 0;              /* replace newline with null */  
      command = strtok(buffer, s);                                                        //Set first part of string as command
      printf("%s", command);
      //arg = strtok(NULL, s);                                                            // Set second part of string as argument
      
      printf("%s", arg);

      if(strcmp(command,"exit")==0){                                                      // If the command entered is exit, exit the shell
        exit(0);
      }
      if(strcmp(command,"pwd")==0){                                                       // If the command entered is pwd, print the current working directory
        pwd=getcwd(NULL, 0);                                                              // Finds the current working directory
        printf("\n[%s]", pwd);                                                              // Prints the current working directory
      }
      if(strcmp(command,"prompt")==0){                                                       // If the command entered is prompt
        if(strcmp(arg, "\0")==0){                                                               // if there is not argument for prompt
          printf("No argument");
        }
                                                                       
      }
      
    
    }
    

     /*  else  program to exec */
    {
       /* find it */
       /* do fork(), execve() and waitpid() */

      /* else */
        /* fprintf(stderr, "%s: Command not found.\n", args[0]); */
    }
  }
  return 0;
} /* sh() */

char *which(char *command, struct pathelement *pathlist ) //prints the first, will be used for executable. Step through linked list, take string, see if its executable, if not, increment to next
{
   /* loop through pathlist until finding command and return it.  Return
   NULL when not found. */

} /* which() */

char *where(char *command, struct pathelement *pathlist ) // prints all. Continue going to the list, create a string with all the answers, return that. 
{
  /* similarly loop through finding all locations of command */
} /* where() */

void list ( char *dir )
{
  /* see man page for opendir() and readdir() and print out filenames for
  the directory passed */
} /* list() */

