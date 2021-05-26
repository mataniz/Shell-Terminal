#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>   // Definition for fork() and execve()
#include <errno.h>    // Definition for "error handling"
#include <sys/wait.h> // Definition for wait()

   /* Declarations for getline() */
   char *input = NULL;
   size_t capline = 0; // Capacity
   
   /* Declaration for strtok() */
   int i;
   char *token;
   char *array[512];

   
   /* Print out "prompt" */
   void displayPrompt(){
       printf("Strawberry: ");
   }

   /* Divide input line into tokens */
   void makeTokens(char *input){
       i = 0;
       token = strtok(input, "\n");
           while (token != NULL) {
               array[i++] = token; // Add tokens into the array
               token = strtok(NULL,";");
               token = strtok(NULL, "\n ");
           }
       array[i] = NULL;
   }
   /* Execute a command */
  void execute(){
      int pid = fork(); // Create a new process
               if (pid != 0) { // If not successfully completed
                   int s;
                   waitpid(-1, &s, 0); // Wait for process termination
           } else {
                   if(execvp(array[0], array) == -1){ // If returned -1 => something went wrong! If not then command successfully completed */
                   perror("Wrong command"); // Display error message
                   exit(errno);
               }
           }
  }


   int main(int argc, char *argv[]){
       if(argc == 1){
           displayPrompt();
          int i = 0,j=1;
          char temp [512]={0};
          char line[512] ={0};
          char str [20];
          const char semicolon[2] = ";";
          const char *command;
          while (fgets(temp, sizeof(temp),stdin)){
              displayPrompt();
              while(temp[i] != '\0'){
                  if(temp[i] == '#')
                      break;
                  else{
                      line[i] = temp[i];
                      i++;
                      }
                  
              }
              i=0;
              command = strtok(line, semicolon);
              while(command != NULL){
                  execute();
                  system(command);
                  command = strtok(NULL, semicolon);
              }
              j++;
              memset(&line[0],0,sizeof(line));
           }


           
      
      } else if(argc == 2){
       int i = 0,j=1;
       char temp [512]={0};
       char line[512] ={0};
       char str [20];
       const char semicolon[2] = ";";
       const char *command;
       char * file = argv[1];
       FILE* user_file = fopen(file,"r");
       while(!user_file){
           printf("File not found! Try again...\nFile name: ");
           scanf("%s",str);
           user_file = fopen(str,"r");

       }
       while (fgets(temp, sizeof(temp),user_file)){
           while(temp[i] != '\0' ){
               if(temp[i] == '#')
                   break;
               else{
                   line[i] = temp[i];
                   i++;
                   }
           }
           i=0;
           command = strtok(line, semicolon);

           while(command != NULL) {
               execute();
               system(command);
               command = strtok(NULL, semicolon);
           }
           j++;
           printf("\n[Line %d]: %s ---- End of execution ----\n\n",j, temp);
           memset(&line[0],0,sizeof(line));
       }
       printf("End of file");
       printf("\n\n\n== Done! ==");
       fclose(user_file);
   
   }
}

