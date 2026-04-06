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
