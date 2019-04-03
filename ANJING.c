#include "ANJING.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printlayout(pin pcb[40][40],int n,int m){
    printf("[Layout Rangkaian pada PCB Dot Matriks]\n");

    printf("/t");
    for(int i=0;i<m;++i){
        printf("%d/t",i);
    }printf("/n");


    for (int i=0;i<n;++i){
        printf("%d/t",i);
        for (int j=0;j<m;++j){
            printf("%s/t",pcb[i][j].nama);
        }
        printf("/n");
    }
}

void printRout(pin pcb[n][m],int n,int m){
    printf("[Layout Rangkaian pada PCB Dot Matriks]\n");

    printf("/t");
    for(int i=0;i<m;++i){
        printf("%d/t",i);
    }printf("/n");


    for (int i=0;i<n;++i){
        printf("%d/t",i);
        for (int j=0;j<m;++j){
            printf("%c/t",pcb[i][j].simbol);
        }
        printf("/n");
    }
}
