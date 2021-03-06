#include "parseTable.h"
#include <stdlib.h>

struct SymbolTable {
	char symbol[10];
	int value;
};
struct SymbolTable ST[20];


//////////////////////////////////////////////
////////////  PART 2 ////////////////////////
void echo(char *str);				//+
void cp(char *fs, char *fd);			//+
int wc(char opt, char *fname);			//+
void cat(char *fname);				//+
int expr(char *opnd1, char opr, char *opnd2);	//+
void assign(char *lhs, int value);		//+
//////////////////////////////////////////////
//////////////////////////////////////////////

void printSymbolTable();
int compareCommand(char *com1,char *com2);
void returnstr(char *str);//Remove ';'
int SearchSymbolTable(char *par);

int main() {
	
	char command[40];
	int countsym=0;
	int num=0;
	char tmpfile[10];
	
	printf(">>>");
	fgets(command,40,stdin);
	clearParseTable();
	while(compareCommand("-1",command)==0) {
		MakeParseTable(command);
		//printSymbolTable();
		//printParseTable();
		if((PT[2].exists==1 && PT[num].par1[0]==';')) {
			if(SearchSymbolTable(PT[2].par1)) {
				assign(PT[2].par1,atoi(PT[num].cmd)); //atoi = ASCII TO Int	
			}
			else {
				strcpy(ST[countsym].symbol,PT[2].par1);
				ST[countsym].value=atoi(PT[num].cmd); //atoi = ASCII TO Int
				countsym++;
			}
		}
		else if(compareCommand(PT[num].cmd,"echo;")) {
			echo(PT[num].par1);
		} 
		else if(compareCommand(PT[num].cmd,"cp;")) {
			returnstr(PT[num].par1);
			returnstr(PT[num].par2);
			cp(PT[num].par1,PT[num].par2);
		}
		else if(compareCommand(PT[num].cmd,"wc;")) {
			if(PT[num].par2[0]==';'){
				returnstr(PT[num].par1);
				wc(PT[num].par2[0],PT[num].par1);
				strcpy(tmpfile,PT[num].par1);
			}
			else {
				returnstr(PT[num].par1);
				returnstr(PT[num].par2);
				wc(PT[num].par1[0],PT[num].par2);
				strcpy(tmpfile,PT[num].par2);
			}
		}
		else if(compareCommand(PT[num].cmd,"cat;")) {
			returnstr(PT[num].par1);
			cat(PT[num].par1);
			strcpy(tmpfile,PT[num].par1);
		}
		else if(compareCommand(PT[num].cmd,"expr;")) {
			returnstr(PT[num].par1);
			returnstr(PT[num].par3);
			expr(PT[num].par1, PT[num].par2[0], PT[num].par3);
		}
		else if(compareCommand(PT[num].cmd,"assign;")) {
			int num=atoi(PT[num].par2);
			assign(PT[0].par1, num);
		}
		else
			printf("COMMAND NOT FOUND!!!\n");

		if (PT[1].exists==1 && num!=1) {
			num++;
			if(compareCommand(PT[num].cmd,"wc;")) {
				wc(PT[num].par1[0],tmpfile);

			}
			else if(compareCommand(PT[num].cmd,"cat;")) {
				cat(tmpfile);
			}
			else
				printf("COMMAND NOT FOUND!!!\n");
		}

		printf(">>>");
		//printSymbolTable();
		clearParseTable();
		fgets(command,40,stdin);
		num=0;
	}

	return 0;
}
void returnstr(char *str) {
	int i;
	for(i=0;str[i]!='\0';i++) {
		if(str[i]==';')
			str[i]='\0'; //remove ;
	}
}	

int compareCommand(char *com1,char *com2) {
	int i=0;
	for(i;com1[i]!=';' && com1[i]!='\0';i++) {
		if(com1[i]!=com2[i])
			return 0;//if two strings are NOT same
	}
	return 1;//if two strings are same
}
void printSymbolTable() {
	int count=0;
	printf("Symbol	Value\n");
	for(count;ST[count].symbol[0]!='\0';count++) {
		printf("%s	%d\n",ST[count].symbol,ST[count].value);
	}
}
int SearchSymbolTable(char *par) {
	int count=0;
	for(count;ST[count].symbol[0]!='\0';count++) {
		if(compareCommand(par,ST[count].symbol))
			return count+1;//in symbol table
	}		
	return 0;//NOT in symbol table
}
void echo(char *str) {
	int count=SearchSymbolTable(str);
	if(count)
		printf("%d\n",ST[count-1].value);
	else {
		returnstr(PT[0].par1);
		printf("%s\n",PT[0].par1);
	}
}
void cp(char *fs, char *fd) {
	FILE *fptr1, *fptr2;
	char contents;
	fptr1 = fopen(fs, "r");//Open one file for reading 
	
	if(fptr1 == NULL) {
		printf("Not such file exist\n"); 
	}
	else {
		fptr2 = fopen(fd, "w");//Open another file for writing
		contents = fgetc(fptr1);// Read contents from file 
		while (contents != EOF) { 
			fputc(contents, fptr2); 
			contents = fgetc(fptr1); 
		}
		fclose(fptr1);//Close files
		fclose(fptr2);//Close files
	}
}
int wc(char opt, char *fname) {
	FILE *fp = fopen(fname,"r");
	char contents;
	int line=0,word=0,bit=0;
	if(fp == NULL) {
		printf("Not such file exist\n"); 
	}
	else {
		contents = fgetc(fp);
		while (contents != EOF){
			if (contents == '\n')
				line++;
			if (contents == ' ' || contents == '\n') {
				word++;
				while(contents == ' ') {
					contents = fgetc(fp);
				}
			}
			if (contents != ' ' && contents != '\n')
				bit++;
			contents = fgetc(fp);
		}
		fclose(fp);
		if(opt=='l') {
			printf("%d\n",line);
			return line;
		}
		else if(opt=='w') {
			printf("%d\n",word);
			return word;
		}
		else if(opt=='c') {
			printf("%d\n",bit);
			return bit;
		}
		else if(opt==';') {//If No Command
			printf("%d	%d	%d\n",line,word,bit);
		}
		else {
			printf("Command Not Found!!!\n");
		}
			
	}
}
void cat(char *fname) {
	FILE *fp = fopen(fname,"r");
	char contents;
	if(fp == NULL) {
		printf("Not such file exist\n"); 
	}
	else {
		contents = fgetc(fp);
		while (contents != EOF){
			printf("%c",contents);
			contents = fgetc(fp);
		}
	}
}
int expr(char *opnd1, char opr, char *opnd2) {
	int num1=SearchSymbolTable(opnd1);
	int num2=SearchSymbolTable(opnd2);
	int numOfSymbol=0;
	int result=0;
	if(num1) 
		num1=ST[num1-1].value;
	else
		num1=atoi(opnd1);
	
	if(num2) 
		num2=ST[num2-1].value;
	else
		num2=atoi(opnd2);
	for(numOfSymbol;ST[numOfSymbol].symbol[0]!='\0';numOfSymbol++);
	//find the number of elements in symbol table

	//printf("num1:%d\n",num1);
	//printf("num2:%d\n",num2);

	if(opr=='+') {
		result=num1+num2;
	}
	if(opr=='*') {
		result=num1*num2;
	}
	if(opr=='/') {
		result=num1/num2;
	}
	if(opr=='%') {
		result=num1%num2;
	}
	if(opr=='s') {//subtract '-' can not find in parse table since it is a special character
		result=num1-num2;
	}
	printf("result:%d\n",result);
	if(PT[2].exists) {
		assign(PT[2].par1,result);
	}
	return result;

}
void assign(char *lhs, int value) {

	int ifin=SearchSymbolTable(lhs);
	int numOfSymbol=0;
	
	if(ifin){
		ST[ifin-1].value=value;
	}
	else {
		for(numOfSymbol;ST[numOfSymbol].symbol[0]!='\0';numOfSymbol++);
		ST[numOfSymbol].value=value;
		strcpy(ST[numOfSymbol].symbol,lhs);
	}
}













