////////////////////////////////////////////////////////////////////////////////
// Main File: 537ps.c
// This File: 537ps.c
//
////////////////////////////////////////////////////////////////////////////////
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "process.h"
#include "processIDS.h"


//this method takes in a specific pid and the 
//struct object which had been modified to mirror
//the users args, then it goes throughs the options
//and prints accordingly
int printInfoByPid(char *pid, ArgStruct *arg){

    const char *cmdlineLocation = "/cmdline";
    const char *procLocation = "/proc/";
    const char *statLocation = "/stat";
    const char *statmLocation = "/statm";

	// the values for specified options
	char status = '\0';
	long int u = 0;
	long int s = 0;
	int size = 0;

    //assign proc and pid together since its easier to transfer that way
	char *data;
	data = (char *) calloc((sizeof(procLocation)+sizeof(pid)), sizeof(char));
	strcat(data, procLocation);
	strcat(data, pid);

	//setup stat file address
	char *statAddr;
	statAddr = (char *) calloc((sizeof(statLocation) + sizeof(data)), sizeof(char));
	strcat(statAddr,data);
	strcat(statAddr,statLocation);
    //open file from the address 
	FILE *statFile;
	statFile = fopen(statAddr, "r");
	free(statAddr);
	if (statFile == 0){
		//fopen returns 0, the NULL pointer, on failure
		perror("Cannot open stat file\n");
		free(data);
		return -1;
	}else{
		char *stat;
		stat = (char *) calloc(900, sizeof(char));
		int i = 0;
		while ((fscanf(statFile,"%s",stat)) == 1){
			// status
			if(i == 2){
				status = stat[0];
			}
			// u time
			if(i == 13){
				u = atoi(stat);
			}
			// s time
			if(i == 14){
				s = atoi(stat);
				break;
			}
			i++;
		}
		free(stat);
		fclose(statFile);
	}
	
	printf("%s: ", pid);
	if(arg->s){
		printf("%c ",status);
	}
	if(arg->UDash){
		//utime is printed by default
	}else{
		// print utime
		printf("utime=%lu ",u); 
	}
	if(arg->S){
		printf("stime=%lu ",s);
	}
    if(arg->cDash){
		//cmdline is printed by default
	}else{
		// get cmdline file
		char *cmdPath;
		cmdPath = calloc((sizeof(cmdlineLocation) + sizeof(data)), sizeof(char));
		strcat(cmdPath,data);
		strcat(cmdPath,cmdlineLocation);

		FILE *cmdFile;
		cmdFile = fopen(cmdPath, "r");
		free(cmdPath);
		if (cmdFile == 0){
			//fopen returns 0, the NULL pointer, on failure
			printf("ERROR with cmdFile\n");
			free(data);
			return -1;
		}else{
			char *cmd;
			cmd = calloc((900*2), sizeof(char));
			while ((fscanf(cmdFile,"%s",cmd)) == 1){
				// cmd line value is the first value
				printf("[%s] ", cmd);
				break;
			}
			free(cmd);
			fclose(cmdFile);
		}
	}
	if(arg->v){
		char *statmPath;
		statmPath = (char *) calloc((sizeof(statmLocation) + sizeof(data)), sizeof(char));
		strcat(statmPath,data);
		strcat(statmPath,statmLocation);

		FILE *statm_file;
		statm_file = fopen(statmPath, "r");
		free(statmPath);
		if (statm_file == 0){
			//fopen returns 0, the NULL pointer, on failure
			printf("ERROR with statm file\n");
			free(data);
			return -1;
		}else{
			char *statmParse;
			statmParse = (char *) calloc(900, sizeof(char));
			int i = 0;
			while ((fscanf(statm_file,"%s",statmParse)) == 1){
				if(i == 0){
					size = atoi(statmParse);
					break;
				}
			}
			free(statmParse);
			fclose(statm_file);
		}
		printf("virtual memory=%d ",size);
	}
	
	free(data);
	printf("\n");
	return 0;
}

//the primary function called which calls other 
//helper methods to construct the struct
//and print accordingly
int main(int argc, char *argv[]){

    ArgStruct *allArgs = processArgs(argc, argv);
    if(allArgs != NULL){

    }else{
        return -1;
    }

    if(!allArgs->p){ //this condition prints info for all pids
        if(allArgs->processId == NULL){
            
        }else{
            printf("error with -p\n");
            return -1;
        }

        char ** allPids = readPIDS();
        int iterate = 0;
        while(*(iterate + allPids) != NULL){

                if(printInfoByPid(*(iterate + allPids), allArgs)){
				// error happened while printing
				printf("\n");
				return -1;
			}
                  
            iterate++;
        }
    }

    else if(allArgs->p){  //this condition just prints info for specific pid
        if(allArgs->processId != NULL){
            
            if(printInfoByPid(allArgs->processId, allArgs)){
				// error
				printf("\n");
				return -1;
            }
        }
    }
}
