////////////////////////////////////////////////////////////////////////////////
// Main File: 537ps.c
// This File: process.c
//
////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <ctype.h>
#include <getopt.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "process.h"
#include "processIDS.h"

ArgStruct * processArgs(int argc, char *argv[]){
	int totalOptions = 0;
	char *pid = NULL;

	int p = 0; 
	int pDash = 0; //-p-
	int s = 0;
	int sDash = 0; //-s-
    int S = 0;
	int SDash = 0; //-S-
	int U = 0;
	int UDash = 0; //-U-
	int v = 0;
	int vDash = 0; //-v-
	int c = 0;
	int cDash = 0; //-c-
	int i = 0;
    int opt; //holds option
	while(i < argc){
		// get options from the command line
		opt = getopt (argc, argv, "s::U::S::v::c::p::");
		if(opt != -1){
			switch(opt)
			{
			case 's':
				if((optarg != NULL) && (strcmp("-", optarg) == 0)){
					sDash = 1;
				}else if((optarg != NULL)){
					printf("error:pid syn error\n");
					return NULL;
				}else{
					s = 1;
				}
				break;


			case 'S':
				if((optarg != NULL) && (strcmp("-", optarg) == 0)){
					SDash = 1;
				}else if((optarg != NULL)){
					printf("error:pid syn error\n");
					return NULL;
				}else{
					S = 1;
				}
				break;

	
			case 'p':
				if((optarg != NULL) && (strcmp("-", optarg) == 0)){
					pDash = 1;
				}else if((optarg != NULL)){
					if(numCheck(optarg)){
						pid = optarg;
						p = 1;
					}else{
					    printf("error:pid syn error\n");
						return NULL;
					}
	  			}else{
	    				p = 1;
				}
	  			break;

			case 'U':
				if((optarg != NULL) && (strcmp("-", optarg) == 0)){
					UDash = 1;
				}else if((optarg != NULL)){
					printf("error:pid syn error\n");
					return NULL;
				}else{
					U = 1;
				}
				break;

			
			case 'v':
				if((optarg != NULL) && (strcmp("-", optarg) == 0)){
					vDash = 1;
				}else if((optarg != NULL)){
					printf("error:pid syn error\n");
					return NULL;
				}else{
					v = 1;
				}
				break;

			case 'c':
				if((optarg != NULL) && (strcmp("-", optarg) == 0)){
					cDash = 1;
				}else if((optarg != NULL)){
					printf("error:pid syn error\n");
					return NULL;
				}else{
					c = 1;
				}
				break;

			case ':':
              	printf("tag needs a value\n");
				return NULL;
             	break;

			case '?':
				printf("error:pid syn error\n");
				return NULL;
				break;

			default:
			break;
			}

		totalOptions++;
		}
		i++;
	}

     int extra = (argc-totalOptions)-1;
	// should be 1 arg extra, the pid

	if(extra == 1){
		if(numCheck(argv[optind])){
			pid = argv[optind];
		}else{
			printf("ERROR: pid is not a number.\n");
            return NULL;
			
		}
	}
	 
	if(extra > 1){
		printf("ERROR: only one pid accepted.\n");
        return NULL;
	}

	// assign flags to return object
	ArgStruct *allArgs;
	allArgs = (ArgStruct*) calloc(1, sizeof(ArgStruct)+sizeof(pid));
	allArgs->p = p;
	allArgs->pDash = pDash;
	allArgs->s = s;
	allArgs->sDash = sDash;
	allArgs->S = S;
	allArgs->SDash = SDash;
	allArgs->U = U;
	allArgs->UDash = UDash;
	allArgs->c = c;
	allArgs->cDash = cDash;
	allArgs->v = v;
	allArgs->vDash = vDash;
	allArgs->processId = pid;
	return allArgs;
}


