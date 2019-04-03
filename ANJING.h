#ifndef ANJING_H
#define ANJING_H
typedef struct{
        char nama[3];
        int simbol;
        int netlist;
} pin;
int n,m;
void printlayout(pin pcb[][40] ,int n, int m);
void printRout(pin pcb[][40],int n,int m);

#endif
