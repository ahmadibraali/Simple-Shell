#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>
// ## Global Variables ##
time_t now;//variable to hold current time
int x;//the result of execvp to know the executed happend or not
int background;//flag to indicate the background proccess

void cmd_split(char *line,char **arg)//function to take the line and splited to arguments
{
    while(*line !='\0')//while the line didn't end
        {
	 while(*line==' ' || *line=='\t') //while the current charactar of  line has space or a tab repalce it with  a null
		{	*line='\0';
			line++;
		}
		*arg=line;
		arg++;
		while(*line!=' ' && *line!='\t' && *line!='\0')//while the current character of line is not (space, tab, null) and if the line is entered then replace it with null and move to next character
		{
		if(*line=='\n')
            *line='\0';
            line++;
		}
        }
	line--;//to check on the last caracter (before \0)
	if(*line=='&')//if it is & (with a space before it or not) then change backgroun indicator to 1 (command will execute in background) and replace & with a \0
		{if(*(line-1)!='\0')//ex: gedit &
            {
            printf("\t\t\t\t##Background Process##\n");
			background=1;
			*line='\0';
            }
		else//ex: gedit&
		{
			printf("\t\t\t\t##Background Process##\n");
			background=1;
			*arg--='\0';
		}
		}
	else  //if not then it's executed in the forground
		{
			printf("\t\t\t\t##Foreground Process##\n");
		}
	*arg='\0';

}
//################################//
//################################//

void signalhandler(int signal)//function to open the log file and to see if there is a signal then it will type the message
{
	//printf("cought signal %d \n",signal);//to indicate the signal was cought
	FILE *ptr;
	ptr=fopen("log_file.txt","a+");//create log file (if doesn't exist), and append messages to it (if not empty)
	if(ptr==NULL)
	{
		printf("error in creating log file\n" );///if there is no file then there is an error
		exit(1);
	}

	if(signal==SIGCHLD)//if the signal happend then print the message in log file
	{
		time(&now);//to print the time of the termination
		fprintf(ptr,"the child is terminated\t|\t%s",ctime(&now));
		wait(NULL);
	}
}
//################################//
//################################//
void execute(char **arg)//function that execute the command and handle the procceses
{
	pid_t pid;
	pid=fork();//to create dublicate proccess

	signal(SIGCHLD,signalhandler);//to check on the signal of the child (terminated or not)

	if(pid>=0)
	{
		if(pid==0)//if there is a child run command
		{
			x=execvp(arg[0],arg);
			if(strcmp(arg[0],"\n")==0)//to check if empty command
			{
				x=0;//not error
			}
		}
	       else
		{
			if(background==0)//check if forground (background=0)then wait,otherwise if background (background=1) don't wait
			{
				wait(NULL);
			}
		}
	}
	else //else (fork failed) print error msg
	{   printf("fork is failed\n");	}
}
//################################//
//################################//

int main()
{
	char line[512];
	char *arg[128];
	printf("\t\t\t\t## ZOokA SHELL ## \n");
	while(1)
	{
		printf("Zooka >");
		gets(line);//get line
		if(strlen(line)==0) continue;//no thing ? again
		if(strlen(line) > 511)//too long
		{
			printf("ERROR:COMMAND MUST BE LESS THAN 512,TRY AGAIN.\n");
			continue;
		}
		cmd_split(line,arg);    //split the line and save in arg
		if(strcmp(arg[0],"cd")==0)// check if the command is cd
		{
			chdir(arg[1]);
		}
		else if(strcmp(arg[0],"exit")==0)// exit ?
			exit(1);
		else
		{
			execute(arg);
			if(x!=0) //Error Handling
				perror("ERROR:");
		}
	background=0;//return
	}
	return 0;
}

