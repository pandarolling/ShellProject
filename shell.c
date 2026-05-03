/************************************************************************************
* MyShell - simple unix shell.                                                      *
* By - Timothy Kurian and Shubham Yadav                                             *
* Description - A lightweight command-line interpreter implemented in C. It         *
* provides a standard REPL environment, supporting built-in commands                *
* (cd, help, exit) and external program execution using the                         *
* fork-exec-wait process model. Features dynamic memory management                  *
* for robust command parsing.                                                       *
************************************************************************************/
#include<sys/wait.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


/*
function declaration for builtin shell commands
*/
int mysh_cd(char ** args);
int mysh_exit(char ** args);
int mysh_help(char ** args);


/*
list of builtin commands, with their correspoding members
*/
char *builtin_str[] = {
   "cd",
   "help",
   "exit"
};

int (*builtin_func[]) (char **) = {
   &mysh_cd,
   &mysh_help,
   &mysh_exit
};

int mysh_num_builtins(){
   return sizeof(builtin_str)/sizeof(char *);
}


/*
change directory
args[0] is "cd" args[1] is the directory
returns 1 to continue execution
*/
int mysh_cd(char ** args){
   if(args[1] == NULL){
      fprintf(stderr, "mysh: expected arguments for \"cd\" \n");

   }else{
      if(chdir(args[1]) != 0){
         perror("mysh");
      }
   }

   return 1;

}


/*
print help 
returns 1 for continuing execution
*/
int mysh_help(char ** args){
   int i ;
   printf("MyShell program\n");
   printf("Type program names and hit enter\n");
   printf("Following are built in\n");

   for(i = 0; i < mysh_num_builtins(); i++){
      printf(" %s\n", builtin_str[i]);
   }

   printf("Use the man command for information on other programs.\n");
   return 1;

}


/*
exit function
returns 0 to terminate
*/

int mysh_exit(char **args){
   return 0;
}



/*
launch a program and  wait for it to terminate\
returns 1 to continue execution
*/

int mysh_launch(char **args){
   pid_t pid;
   int status;

   pid = fork();

   if(pid == 0){
      //child process
      if(execvp(args[0], args) == -1){
         perror("mysh");
      }
      exit(EXIT_FAILURE);
   }else if(pid < 0){
      perror("mysh: error in forking" );
   }else{
      do{
         waitpid(pid, &status, WUNTRACED);
      }while(!WIFEXITED(status) && !WIFSIGNALED(status));
   }


   return 1;
}




/*
Execute the tokens
*/
int mysh_execute(char ** args){
   int i ;

   if(args[0] ==NULL){
      return 1;

   }

   for(i =0; i < mysh_num_builtins(); i++){
      if(strcmp(args[0] , builtin_str[i]) == 0){
         return (*builtin_func[i])(args);
      }
   }

   return mysh_launch(args);
}



/*
readline function
*/
char * mysh_readline(){
#ifdef MYSH_USE_GETLINE
   char *line = NULL;
   size_t bufsize = 0;
   if(getline(&line, &bufsize, stdin) == -1){
     if(feof(stdin)){
	exit(EXIT_SUCCESS);
     }
     else{
      perror("mysh: getline\n");
      exit(EXIT_FAILURE);
     }  
}
   return line;

#else

#define MYSH_RL_BUFSIZE 1024
   int bufsize = MYSH_RL_BUFSIZE;
   int pos = 0;
   char *buffer = malloc(sizeof(char) * bufsize);
   int c;

   if(!buffer){
      fprintf(stderr, "mysh: allocation error");
      exit(EXIT_FAILURE);
   }

   while(1){
      c = getchar();

      if(c == EOF){
         exit(EXIT_SUCCESS);
      }else if(c == '\n'){
         buffer[pos] = '\0';
         return buffer;
      }else{
         buffer[pos] = c;
      }
      pos++;

      if(pos >= bufsize ){
         bufsize += MYSH_RL_BUFSIZE;
         buffer = realloc(buffer, bufsize);
         if(!buffer){
            fprintf(stderr, "mysh : allocation error\n");
            exit(EXIT_FAILURE);
         }
      }
   }

#endif
}

/*
Split line into tokens
*/

#define MYSH_TOK_BUFSIZE 64;
#define MYSH_TOK_DELIM " \t\n\r\a"
   
char ** mysh_splitline(char *line )
{
   int bufsize = MYSH_TOK_BUFSIZE;
   int position = 0;
   char **tokens = malloc(bufsize * sizeof(char *));
   char * token, **tokens_backup;

   if(!tokens){
      fprintf(stderr, "mysh: allocation error\n");
      exit(EXIT_FAILURE);
   }

   token = strtok(line, MYSH_TOK_DELIM );
   while(token != NULL){
      tokens[position] = token;
      position++;

      if(position>= bufsize){
         bufsize += MYSH_TOK_BUFSIZE;
         tokens_backup = tokens;
         tokens = realloc(tokens, bufsize* sizeof(char *));
         if(!tokens){
            free(tokens_backup);
            fprintf(stderr, "mysh: allocation error\n");
            exit(EXIT_FAILURE);
         }
      }

      token = strtok(NULL, MYSH_TOK_DELIM);
   }

   tokens[position] = NULL;
   return tokens;
}

/*
   looping function
*/
void mysh_loop(){
   char *line;
   char **args;
   int status;

   do{
      printf("mysh>");
      line  = mysh_readline();
      args = mysh_splitline(line);
      status = mysh_execute(args);
      
      free(line);
      free(args);
      
   }while(status);

}

/*
   main entry point 
*/
int main(){

   //this loop performs all the input,output and executing of the shell
   mysh_loop();

return 0;
}
