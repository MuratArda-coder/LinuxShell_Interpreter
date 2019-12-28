#include<stdio.h>
#include<string.h>

struct ParseTable {
	int exists;
	char cmd[10];
	char par1[10];
	char par2[10];
	char par3[10];
};

struct ParseTable PT[3]; //Global ParseTable

void makeNull(struct ParseTable P[],int num);

void printParseTable();

void clearParseTable();

void MakeParseTable(char *command);
