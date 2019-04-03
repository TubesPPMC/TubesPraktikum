#include "ANJING.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int i,j;

void printlayout(pin pcb[][m],int n,int m){
    printf("[Layout Rangkaian pada PCB Dot Matriks]\n");
    printf("\t");
    for(i=0;i<m;++i){
        printf("%d\t",i+1);
    }printf("\n");


    for (i=0;i<n;++i){
        printf("%d\t",i+1);
        for ( j=0;j<m;j++){
            printf("%s\t",pcb[i][j].nama);
        }
        printf("\n");
    }
}

void printRout(pin pcb[][m],int n,int m){
    printf("[Layout Rangkaian pada PCB Dot Matriks]\n");

    printf("\t");
    for( i=0;i<m;++i){
        printf("%d\t",i+1);
    }printf("\n");


    for (i=0;i<n;++i){
        printf("%d\t",i+1);
        for (j=0;j<m;j++){
            printf("%c\t",pcb[i][j].simbol);
        }
        printf("\n");
    }
}
