////////////////////////////////////////////////////////////////////////////////
// Main File: 537ps.c
// This File: processIDS.c
//
////////////////////////////////////////////////////////////////////////////////
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <dirent.h>
#include <getopt.h>
#include <ctype.h>

int numCheck(char *arg){
	int i = 0;
	while(*(arg+i) != '\0'){ //null check
		if(!(isdigit(*(arg+i))) ){ //num check
			return 0;
		}
		i++;
	}
	return 1;//true condition if all are nums 
}


// @return list of process ids
char ** readPIDS(){
	static const char *proc = "/proc/";
	static const char *status = "/status";

    char *pid;
	DIR *check;
	struct dirent *open;
	int proID = 0;
	int userUID = getuid();
	
	// directory is valid or not
	if ((check = opendir("/proc")) == NULL){
		fprintf(stderr, "wrong directory");
		return NULL;
	}
	
    char ** list;
	int count = 0;
	list = (char **) calloc((200000), sizeof(char *));
    // the while loop that iterates through /proc
	while((open = readdir(check)) != NULL){
        
		if(numCheck(open->d_name)){
			pid = open->d_name;
			int size = (sizeof(pid)+sizeof(status)+sizeof(proc));
			char *fileAdd; 
			fileAdd = calloc(size, sizeof(char)); // create filepath
			strcat(fileAdd, proc);
			strcat(fileAdd, pid);
			strcat(fileAdd, status);
			
			// stat file	
			FILE *file;
			file = fopen(fileAdd, "r");
			free(fileAdd);
			if (file == 0){
			}else{
				int next = 0;
				char *status;
				status = (char *) calloc(300, sizeof(char *));
				while (1 == (fscanf(file,"%s",status))){
					if(next){
                        //get the UID
						proID = atoi(status);
						break;
					}
					if(strcmp("Uid:",status) == 0){
						next = 1;
					}
				}
				free(status);
				if (proID == userUID) {
						*(list+count) = pid;
						count++;
				}
			}
			fclose(file);	
		}
	}
	return list;
}
