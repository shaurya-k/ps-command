////////////////////////////////////////////////////////////////////////////////
// Main File: 537ps.c
// This File: process.h
//
////////////////////////////////////////////////////////////////////////////////
#ifndef PROJ1_PROCESS_H
#define PROJ1_PROCESS_H

typedef struct{
  int p;
  int pDash;
  int U;
  int UDash;
  int s;
  int sDash;
  int S;
  int SDash;
  int v;
  int vDash;
  int c;
  int cDash;
  char *processId;
} ArgStruct;

ArgStruct * processArgs(int argc, char *argv[]);

#endif
