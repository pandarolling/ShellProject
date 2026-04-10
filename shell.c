/************************************************************************************
* MyShell - simple unix shell.                                                      *
* By - Timothy Kurian and Shubham Yadav                                             *
* Description -                                                             
************************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>


/*
Execute the tokens
*/
int mysh_execute(char ** args){
   
}

/*
Split line into tokens
*/
char ** mysh_splitline(char * line){

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
         exit(EXIT_SUCCESS);
      }else{
         buffer[pos] = c;
      }
      pos++;

      if(pos >= bufsize ){
         bufsize += MYSH_RL_BUFSIZE;
         buffer = realloc(buffer, bufsize);
      }
   }

#endif
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
