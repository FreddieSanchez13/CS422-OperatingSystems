#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* prompt = "xxx>";
char cmd[128];
size_t len = sizeof(cmd);
char* lineptr = &cmd[0];
char* str;
char* parmlist[20];

void main(int argc, char* argv[]){
	char line[128];
	int n;
	int mypid;			// PID of original process
	int cpid;			// Child process pid
	cpid = mypid;
	int status;

	printf("Shell Starting...\n");
	while(1){
		printf("%s ", prompt);
		n = getline(&lineptr, &len, stdin);
		lineptr[--n] = 0;			//replace new-line with new character
		str = strtok(lineptr," ");
		int i =0;
		while(str!=NULL){
			if(i>=sizeof(parmlist)) break; //Makes sure buffer overflows cannot happen.
			parmlist[i++] = str;
			printf("word[%d]: %s\n",i,str);
			str = strtok(NULL," ");
		}
		parmlist[i] = NULL;
		if (strcmp(lineptr,"exit")==0) break;
		cpid = fork();
		if (cpid == 0){		// Tests if this is the child process
			execvp(parmlist[0],parmlist);
			printf("Error! Your exec failed!\n\n");
			exit(0);		//Makes child terminate
			sleep(5);
		}
		wait(&status);
	}

}
