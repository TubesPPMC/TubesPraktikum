#ifndef MANUALLAYOUT_H
#define MANUSLLSYOUT_H

typedef struct pin{
	char nama[3];
	char simbol;
	int net;

}pin;

void printlayout(pin pcb[n][m],int n,int m);
void printRout(pin pcb[n][m],int n,int m);

#endif
