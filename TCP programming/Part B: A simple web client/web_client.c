#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#define BUFFLEN 2500
#define SIM_LENGTH 50

/*Main sources that we use:
  https://shapeshed.com/unix-wget
  https://stackoverflow.com/questions/15337932/how-to-include-the-command-wget-on-my-c-source-code
  https://www.includehelp.com/c-programs/delete-a-specified-file-using-the-system-function.aspx
  https://stackoverflow.com/questions/2029103/correct-way-to-read-a-text-file-into-a-buffer-in-c */


int main(int argc, char* argv[]) {
  char* web_address;
  FILE *fp;
  char BUFF[BUFFLEN];
  
  
  /*Checks if given value in the command-line*/
  if (argc != 2) 
  {
    perror("Usage: hostnamelookup <hostname>\n");
    exit(1);
  }
  

  /*Takes the web address from the command-line*/
  web_address = argv[1];
  char wget[SIM_LENGTH] = "wget ";
  strcat(wget, web_address);

  printf("the web address: %s\n",web_address);

  printf("system(%s)...\n",wget);
  
  /*The system func is used to execute a shell command,
    The wget command is a command line utility for downloading files from the Internet,
    So we will write into system - ("wget 'web_address'") to download the website.
    for example('web_address' == www.stackoverflow.com)*/
  system(wget);

  printf("\n\n");
  printf("printing...\n\n");

  /*Opening a FILE to read the index.html we got from system("wget 'web_address'") command*/
  fp = fopen("index.html", "r");
  if(fp != NULL)
  {
    /*Cope the FILE index.html to a buffer and printing it (2500 letters at a time)*/
    while (fgets(BUFF, 2500, fp))
    {
      printf("%s",BUFF);
    }
  }
  /*If FILL is NULL or could not open exit*/
  else
  {
    printf("File is NULL\n");
    exit(1);
  }
  
  /*close FILE*/
  fclose(fp);

  printf("\n");

  /*Delete index.html by system("rm 'FILE name'") commend*/
  system("rm index.html");
  
  exit(0);
}
