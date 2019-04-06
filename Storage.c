#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Storage.h"
#define kosong ""
void NewProject(fname *nama, BesarMatriks *bm)
{	
	char Nama[100];
	printf("====== Membuat Proyek Baru ======\n");
	printf("Masukkan nama proyek: ");
	gets(Nama);
	strcpy(nama->namaFile_Layout,Nama);
	strcpy(nama->namaFile_Routing,Nama);
	//Buat memastikan agar gak inputnya gak idiot
	printf("Masukkan ukuran PCB NxM (N,M<40): ");
	int m,n;
	scanf("%d %d" ,&n,&m);
	bm->m = m;
	bm->n = n;
	FILE *fp_layout;
	strcat(nama->namaFile_Layout, "_Layout.csv");
	fp_layout = fopen(nama->namaFile_Layout,"w");//untuk membuat file Layout
	FILE *fp_routing;
	strcat(nama->namaFile_Routing, "_Routing.csv");
	fp_routing = fopen(nama->namaFile_Routing,"w");//untuk membuat file Routing
	fclose(fp_routing);
	fclose(fp_layout);
}
void SaveProject(PCB Board, fname *nama, BesarMatriks *bm)
{
	int I,J,K;
	char empty [3] = {'\0'};
	char *c= NULL;
	char *temp = "";
	FILE *fp_layout;
	fp_layout = fopen(nama->namaFile_Layout,"w");
	FILE *fp_routing;
	fp_routing = fopen(nama->namaFile_Routing,"w");
	for (I=0; I<bm->m; I++)
	{
		for (J=0; J<bm->n; J++)
		{
			if (strcmp(Board.pin[I][J].Name,empty) == 0 )
			{
				fprintf(fp_layout," ,");
			}else if (strcmp(Board.pin[I][J].Name,empty) != 0 )
			{
				fprintf(fp_layout,"%s,",Board.pin[I][J].Name);
			}			
		}
		fprintf(fp_layout,"\n");
	}
	for (I=0; I<bm->m; I++)
	{
		for (J=0; J<bm->n; J++)
		{	
			if (Board.pin[I][J].Simbol == *temp)
			{
				fprintf(fp_routing," ,");
			}else
			{
				fprintf(fp_routing,"%c,",Board.pin[I][J].Simbol);
			}			
		}
		fprintf(fp_routing,"\n");
	}
	fclose(fp_layout);
	fclose(fp_routing);
}
void LoadProject(PCB *Board,fname *nama)
{
	int I,J,N,L,hasil,x,cx;
	L=0;
	int Length;
	char emp = NULL;
	char empty [3];
	empty[0] = emp;
	char koma[3]={','};
	char str[2];
	char temp[3];
	char tempstr[160];
	FILE *fp_layout;
	fp_layout = fopen(nama->namaFile_Layout,"r");
	FILE *fp_routing;
	fp_routing = fopen(nama->namaFile_Routing,"r");
	I = 0;
	while (I < 5)
	{
		J = 0;
		while (J < 5)
		{
			fscanf(fp_layout, "%s",tempstr);
			//printf("|%s|",tempstr);
			//printf("%d\n",strlen(tempstr));
			if (strlen(tempstr) == 1)
			{
				strcpy(Board->pin[I][J].Name,empty);
				//printf("%d,%d -> %s\n",I,J,Board->pin[I][J].Name);
				J++;
			} else
			{
				cx = 0;
				if ((strlen(tempstr) == 3) || (strlen(tempstr) == 4) || (strlen(tempstr) == 5)) {
					for (x = 0; x < strlen(tempstr); x++) {
						if (tempstr[x] != ',') {
							str[0] = tempstr[x];
							strcat(temp,str);
							//printf("%c",temp[cx]);
							cx++;
						} else {
							//printf("\n");
							if (x != 0) {
								//printf("%s\n",temp);
								strcpy(Board->pin[I][J].Name,temp);
							} else {
								strcpy(Board->pin[I][J].Name,empty);
							}
							strcpy(temp,"");
							//printf("%d,%d -> %s\n",I,J,Board->pin[I][J].Name);
							J++;
						}
					}
				} else if (strlen(tempstr) > 5)
				{
					for (x = 0; x < strlen(tempstr); x++) {
						if (tempstr[x] != ',') {
							str[0] = tempstr[x];
							strcat(temp,str);
							//printf("%c",temp[cx]);
							cx++;
						}else {
							//printf("\n");
							if (x != 0) {
								//printf("%s\n",temp);
								strcpy(Board->pin[I][J].Name,temp);
							} else {
								strcpy(Board->pin[I][J].Name,empty);
							}
							strcpy(temp,"");
							//printf("%d,%d -> %s\n",I,J,Board->pin[I][J].Name);
							J++;
						}
					}
				}
			}
		}
		I++;
	}
	fclose(fp_layout);
	fclose(fp_routing);
}


	

