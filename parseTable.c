#include "parseTable.h"

void makeNull(struct ParseTable P[],int num) {
	int i=0;
	for(i;i<10;i++) {
		P[num].cmd[i]='\0';
		P[num].par1[i]='\0';
		P[num].par2[i]='\0';
		P[num].par3[i]='\0';
	}
}

void clearParseTable() {
	PT[0].exists=0;
	makeNull(PT,0);
	strcpy(PT[0].cmd,";");
	strcpy(PT[0].par1,";");
	strcpy(PT[0].par2,";");
	strcpy(PT[0].par3,";");

	PT[1].exists=0;
	makeNull(PT,1);
	strcpy(PT[1].cmd,";");
	strcpy(PT[1].par1,";");
	strcpy(PT[1].par2,";");
	strcpy(PT[1].par3,";");

	PT[2].exists=0;
	makeNull(PT,2);
	strcpy(PT[2].cmd,";");
	strcpy(PT[2].par1,";");
	strcpy(PT[2].par2,";");
	strcpy(PT[2].par3,";");
}

void printParseTable() {
	printf("Command1 %d; %s %s %s %s\n",PT[0].exists,PT[0].cmd,PT[0].par1,PT[0].par2,PT[0].par3);
	printf("Command2 %d; %s %s %s %s\n",PT[1].exists,PT[1].cmd,PT[1].par1,PT[1].par2,PT[1].par3);
	printf("Assignment %d; %s %s %s %s\n",PT[2].exists,PT[2].cmd,PT[2].par1,PT[2].par2,PT[2].par3);
}

void MakeParseTable(char *command) {
	int beforeAssign=0;
	int count=0;
	int com=1,i;
	
	int fincom=1;
	int finpar1=1,cntpar1=0;
	int finpar2=1,cntpar2=0;
	int finpar3=1,cntpar3=0;

	//printf("%s",command);

	
		
	for(i=0;i<40;i++) { //Look the command && Making Parse Table 
		if(command[i]=='`' || command[i]=='$' || command[i]=='-')
			i=i+1;
		if(command[i]=='\n' || command[i]=='\0') {
			com=1;beforeAssign=0;
			fincom=1;count=0;
			finpar1=1;cntpar1=0;
			finpar2=1;cntpar2=0;
			finpar3=1;cntpar3=0;
			break;
		}
		else if(com==1) {
			if(command[i]!=' ' && fincom && command[i]!='=' && command[i]!='|') {
				PT[0].exists=1;
				if(command[i]=='"') {
					i=i+1;
					for(i;command[i]!='"';i++)
						PT[0].cmd[count]=command[i];
						count++;
				}
				else
					PT[0].cmd[count]=command[i];

				if(command[i+1]==' ' || command[i+1]=='\n') {
					fincom=0;
					PT[0].cmd[count+1]=';';
				}
				count++;
			}
			else if(command[i]=='=' && command[i]!='|') {
				strcpy(PT[0].cmd,";");
				PT[0].exists=0;
				PT[2].exists=1;
				count=0;
				fincom=1;
				for(beforeAssign;beforeAssign<i;beforeAssign++)
					PT[2].par1[beforeAssign]=command[beforeAssign];
				PT[2].par1[beforeAssign]=';';
			}
			else if(command[i]!=' ' && finpar1 && command[i]!='|') {
				if(command[i]=='"') {
					i=i+1;
					for(i;command[i]!='"';i++) {
						PT[0].par1[cntpar1]=command[i];
						cntpar1++;
					}

				}
				else
					PT[0].par1[cntpar1]=command[i];
				if(command[i+1]==' ' || command[i+1]=='\n') {
					finpar1=0;
					PT[0].par1[cntpar1+1]=';';
				}
				cntpar1++;
			}
			else if(command[i]!=' ' && finpar2 && command[i]!='|') {
				if(command[i]=='"') {
					i=i+1;
					for(i;command[i]!='"';i++) {
						PT[0].par2[cntpar2]=command[i];
						cntpar2++;
					}
				}
				else
					PT[0].par2[cntpar2]=command[i];

				if(command[i+1]==' ' || command[i+1]=='\n') {
					finpar2=0;
					PT[0].par2[cntpar2+1]=';';
				}
				cntpar2++;
			}
			else if(command[i]!=' ' && finpar3 && command[i]!='|') {
				if(command[i]=='"') {
					i=i+1;
					for(i;command[i]!='"';i++) {
						PT[0].par3[cntpar3]=command[i];
						cntpar3++;
					}
				}
				else
					PT[0].par3[cntpar3]=command[i];

				if(command[i+1]==' ' || command[i+1]=='\n') {
					finpar3=0;
					PT[0].par3[cntpar3+1]=';';
				}
				cntpar3++;
			}

			else if(command[i]=='|') {
				com=2;beforeAssign=0;
				fincom=1;count=0;
				finpar1=1;cntpar1=0;
				finpar2=1;cntpar2=0;
				finpar3=1;cntpar3=0;
				}
		}
		else if(com==2) {
			if(command[i]!=' ' && fincom && command[i]!='=') {
				PT[1].exists=1;
				if(command[i]=='"') {
					i=i+1;
					for(i;command[i]!='"';i++) {
						PT[1].cmd[count]=command[i];
						count++;
					}
				}
				else
					PT[1].cmd[count]=command[i];

				if(command[i+1]==' ' || command[i+1]=='\n') {
					fincom=0;
					PT[1].cmd[count+1]=';';
				}
				count++;
			}
			else if(command[i]=='=') {
				strcpy(PT[0].cmd,";");
				PT[0].exists=1;
				PT[2].exists=1;
				count=0;
				fincom=1;
				for(beforeAssign;beforeAssign<i;beforeAssign++) {
					PT[2].par2[beforeAssign]=command[beforeAssign];	
				}
				PT[2].par2[beforeAssign]=';';
			}
			else if(command[i]!=' ' && finpar1 && !fincom) {
				if(command[i]=='"') {
					i=i+1;
					for(i;command[i]!='"';i++) {
						PT[1].par1[cntpar1]=command[i];
						cntpar1++;
					}
				}
				else
					PT[1].par1[cntpar1]=command[i];

				if(command[i+1]==' ' || command[i+1]=='\n') {
					finpar1=0;
					PT[1].par1[cntpar1+1]=';';
				}
				cntpar1++;
			}
			else if(command[i]!=' ' && finpar2 && !finpar1) {
				if(command[i]=='"') {
					i=i+1;
					for(i;command[i]!='"';i++) {
						PT[1].par2[cntpar2]=command[i];
						cntpar2++;
					}
				}
				else
					PT[1].par2[cntpar2]=command[i];

				if(command[i+1]==' ' || command[i+1]=='\n') {
					finpar2=0;
					PT[1].par2[cntpar2+1]=';';
				}
				cntpar2++;
			}
			else if(command[i]!=' ' && finpar3 && !finpar1 && finpar2) {
				if(command[i]=='"') {
					i=i+1;
					for(i;command[i]!='"';i++) {
						PT[1].par3[cntpar3]=command[i];
						cntpar3++;
					}
				}
				else
					PT[1].par3[cntpar3]=command[i];

			if(command[i+1]==' ' || command[i+1]=='\n') {
					finpar3=0;
					PT[1].par3[cntpar3+1]=';';
				}
				cntpar3++;
			}
		}
	}
	/*
	printf("*********************\n");
	printf("com1 cmd:%s\n",PT[0].cmd);
	printf("com1 par1:%s\n",PT[0].par1);
	printf("com1 par2:%s\n",PT[0].par2);
	printf("com1 par3:%s\n",PT[0].par3);
	printf("com2 cmd:%s\n",PT[1].cmd);
	printf("com2 par1:%s\n",PT[1].par1);
	printf("com2 par2:%s\n",PT[1].par2);
	printf("com2 par3:%s\n",PT[1].par3);
	printf("*********************\n");
	printParseTable();
	*/
	
}






