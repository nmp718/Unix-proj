// Nick Peterson was here
// And Jonathan Adams too

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
  int uid, i, status, argsct, go = 1;                         // argsct is args count, number of arguments
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

  pwd=getcwd(NULL, 0);      // Finds the current working directory

  while ( go )
  {
    // print your prompt 

    printf("\n%s[%s]", prompt, pwd);      // Prints the current working directory
    printf("%s", arrows);       // arrows at the end of the directory

    /* get command line and process */

    /* check for each built in command and implement */
    
    
    
    if (fgets(buffer, BUFFERMAX, stdin) != NULL) {
      if (strlen(buffer)>1){                                                                // if the user actually inputs something
        if (buffer[strlen(buffer) - 1] == '\n')buffer[strlen(buffer) - 1] = 0;              /* replace newline with null */  
          //args[0] = malloc(sizeof(char*));
          //args[0] = strtok(buffer,s);                  //command = strtok(buffer, s);                                                        
      
            //printf("Working here");

          args[0]=strtok(buffer,s);                   //Set first part of string as command

          int i=0;

          while (args[i++]!=NULL){
            args[i]=strtok(NULL,s);
          } //note the ; this just loops this with no code inside of it.

          args[i]=NULL;

          //now args array contains all of the arguments (command is in args[0]) and I is the count of how many arguments.

      

        //printf("%s", args[0]);                            // A test to see what the command argument is                    

        //args[1] = strtok(NULL, s);                                                            // Set second part of string as argument (can maybe use s instead of \n)
      
        //printf("\n%s", args[1]);
        if(strcmp(args[0],"exit")==0){                                                      // If the command entered is exit, exit the shell
          exit(0);
        }
        else if(strcmp(args[0],"pwd")==0){                                                       // If the command entered is pwd, print the current working directory
          //pwd=getcwd(NULL, 0);                                                              // Finds the current working directory
          printf("\n[%s]", pwd);                                                              // Prints the current working directory
        }
        else if(strcmp(args[0],"prompt")==0){                                                       // If the command entered is prompt
          pwd=getcwd(NULL, 0);
          if(args[1]==NULL){                                                               // if there is not argument for prompt
            printf("Enter Prompt: ");
            fgets(buffer, BUFFERMAX, stdin);
            strcpy(prompt,buffer);
            prompt[strlen(prompt)-1]='\0';                      //Removes the newline char from prompt
          }
          else{                                                             // When there is an argument with the prompt
            printf("\nWith an argument");
            strcpy(prompt,args[1]);   //Make sure prompt does not get overwritten
          }
        }
        else if(strcmp(args[0],"ls")==0){
          DIR *d;
          struct dirent *dir;
          if(args[1]==NULL){                    //When no file location is specified
            d=opendir(pwd);
          }
          else{                                 //When args is a specific folder
            d=opendir(args[1]);
          }
          if (d) {
            while ((dir = readdir(d)) != NULL) {
              printf("%s\n", dir->d_name);
            }
          closedir(d);
          }
        }
        else if(strcmp(args[0],"cd")==0){
          if(args[1]==NULL){                            //cd to home directory
            strcpy(pwd,homedir);
            chdir(pwd);
          }
          else if(strcmp(args[1],"-")==0){              //cd to prev directory
            chdir("..");
            pwd = getcwd(NULL, 0);
          }
          else if(opendir(args[1]) != NULL){      //cd to specified directory
            if(*args[1]=='/'){            //Checks if connecting to a specific directory
              strcpy(pwd,args[1]);
              chdir(pwd);
            }
            else{                         //If connecting to a child directory
              strcat(pwd,"/");
              strcat(pwd,args[1]);
              chdir(pwd);
            }
            pwd = getcwd(NULL, 0);          //Call getcwd to purify any errors in new pwd
          }
          else{
            printf("\nFile not found.");
          }
        }
        else if(strcmp(args[0],"pid")==0){                 // Prints the current pid
          pid=getpid();
          printf("%d",pid);
        }
        else if(strcmp(args[0],"printenv")==0){                 // Prints the environment
          if(args[1]==NULL){                                // if there is no argument
            printf("printing environment");
            int i;
            for(i=0;envp[i] != NULL; i++){
            printf("\n%s",envp[i]);
            }
          }
          else if(args[2]!=NULL){                      // Too many arguments
            printf("printenv: Too many arguments.");        
          }
          else{                                         // Just one argument
            printf("%s: ",args[1]);           //prints the env variable
            printf("%s", getenv(args[1]));  // 
          }
        
        }
        else if(strcmp(args[0],"setenv")==0){                 // Prints the environment
          if(args[1]==NULL){                                // if there is no argument
            int i;
            for(i=0;envp[i] != NULL; i++){
            printf("\n%s",envp[i]);
            }
          }
          else if(args[3]!=NULL){                      // Too many arguments
            printf("setenv: Too many arguments.");        
          }
          else if(args[1] !=NULL && args[2]!=NULL) {                  // Two arguments
            setenv(args[2],getenv(args[1]),1);                        // 
          }
          else if(args[2]==NULL){                     // one argument
            unsetenv(args[1]); 
          }
        }
        else if(strcmp(args[0],"which")==0 && args[1]!=NULL){                 // Which command
          which(args[1],pathlist);
          
        }
        else if(strcmp(args[0],"where")==0 && args[1]!=NULL){                 // Where command
          where(args[1],pathlist);
          
        }
        else{             // FORKED STUFF GOES HERE
          pid = fork();
          if(pid == -1) {perror("Error"); exit(0);}
          else if(pid == 0){
            if(execve(args[0],&args[0],NULL) == -1){
              perror("Cannot execute");
              exit(1);
            }
          }
          else{
            waitpid(pid,&status,WUNTRACED);
          }
        }
      }
    }
    
    /*pid=fork();
    if(pid==0){
      execve(,args[1]);
    }
    else{
      waitpid(pid);
    }*/
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

    pathlist = get_path();
    while (pathlist) {         // WHICH
    //sprintf(command, "%s/gcc", pathlist->element);
    if (access(pathlist->element, X_OK) == 0) {
      printf("[%s", pathlist->element);
      printf("/%s]\n",command);
      break;
    }
    pathlist = pathlist->next;
  }

   /* loop through pathlist until finding command and return it.  Return
   NULL when not found. */

} /* which() */

char *where(char *command, struct pathelement *pathlist ) // prints all. Continue going to the list, create a string with all the answers, return that. 
{

  pathlist = get_path();
    while (pathlist) {         // WHERE
      sprintf(command, "%s/gcc", pathlist->element);
      if (access(command, F_OK) == 0)
        printf("[%s]\n", command);
      pathlist = pathlist->next;
    }

  /* similarly loop through finding all locations of command */
} /* where() */

void list ( char *dir )
{
  /* see man page for opendir() and readdir() and print out filenames for
  the directory passed */
} /* list() */

