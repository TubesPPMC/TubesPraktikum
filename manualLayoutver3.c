#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "manualLayoutver3.h"

void manual_layout(pin pcb[][40], int n_rows, int n_cols)
{
    int x_1, y_1, x_2, y_2, x_3, y_3;
    char input_user[2];
    printf("[Mode Layout]\n");
    printf("Isi `q` atau `Q` untuk kembali ke menu\n");
    do{
        printf("Pilih Komponen (R,C,T,J): ");
        scanf("%s", input_user);
        if ((strcmp(input_user,"q")==0)||(strcmp(input_user,"Q")==0)){
            //do nothing
        }
        else{
            if (input_user[0] == 'T'){
                printf("Koordinat Kaki Te: ");
                scanf("%d,%d", &x_1, &y_1);
                printf("Koordinat Kaki Tb: ");
                scanf("%d,%d", &x_2, &y_2);
                printf("Koordinat Kaki Tc: ");
                scanf("%d,%d", &x_3, &y_3);
            }
            else{
                printf("Koordinat Kaki 1: ");
                scanf("%d,%d", &x_1, &y_1);
                printf("Koordinat Kaki 2: ");
                scanf("%d,%d", &x_2, &y_2);
                x_3 = 0; y_3 = 0;
            }
            printf("cek kebenaran jarak kaki\n"); //debug)
            printf("hasil is_benar_komponen = %d\n",
                   is_benar_komponen(input_user,
                                    x_1, x_2, x_3,
                                    y_1, y_2, y_3));
            printf("hasil is_empty_layout = %d\n",
                   is_empty_layout(pcb, n_rows, n_cols,
                                   x_1, x_2,
                                   y_1, y_2, input_user));  //debug
            if (!((is_benar_komponen(input_user,
                                    x_1, x_2, x_3,
                                    y_1, y_2, y_3)==1)
                &&(is_empty_layout(pcb, n_rows,
                                    n_cols, x_1,
                                    x_2, y_1,
                                    y_2, input_user)==1))){
                printf("spesifikasi salah atau komponen menabrak\n");
            }
            else{
                printf("spesifikasi benar\n");
                if (input_user[0] == 'T'){
                    strcpy(pcb[x_1-1][y_1-1].name, input_user);
                    strcpy(pcb[x_2-1][y_2-1].name, input_user);
                    strcpy(pcb[x_3-1][y_3-1].name, input_user);
                }
                else{
                    strcpy(pcb[x_1-1][y_1-1].name, input_user);
                    strcpy(pcb[x_2-1][y_2-1].name, input_user);
                    /*printf("%s\n", pcb[x_1-1][y_1-1].name);
                    printf("%s\n", pcb[x_2-1][y_2-1].name);*/
                }
            }
        }
    }while (!((strcmp(input_user,"q")==0)||(strcmp(input_user,"Q")==0)));
}

void manual_routing(pin pcb[][40], int n_rows, int n_cols)
{
    int i;
    int x_target, y_target;
    char temp;
    char input_user;
    char masukan_koordinat[3];
    printf("[Mode Routing]\n");
    printf("Isi `q` atau `Q` untuk kembali ke menu\n");
    printf("Isi `n` atau `N` untuk memulai pada simpul (node) baru\n");
    do{
        printf("Pilih Simbol (!,@,#,$,%,^,&,*,(,)): ");
        do{
            scanf(" %c", &input_user);
            /*printf("berhasil di input\n");
            printf("input = %c\n", input_user); */
            if ((input_user=='q')||(input_user=='Q')
                ||(input_user=='n')||(input_user=='N')){
                //do nothing
            }
            else{
                i=1;
                /*printf("(review)input = %c\n", input_user);*/
                temp = input_user;
                /*printf("(review)temp = %c\n", temp);*/
                do{
                    printf("Koordinat %d: ", i);
                    scanf("%s", masukan_koordinat);
                    /*printf("input koordinat = %s\n", masukan_koordinat);


                    printf("(review)temp = %c\n", temp);*/
                    input_user = temp;
                    /*printf("(review)input user adalah '%c'\n", input_user); */
                    if ((strcmp(masukan_koordinat,"n")==0)||
                        (strcmp(masukan_koordinat,"N")==0)||
                        (strcmp(masukan_koordinat,"q")==0)||
                        (strcmp(masukan_koordinat,"Q")==0)){
                        printf("input koordinat n/N/q/Q = %s\n", masukan_koordinat);
                        input_user = masukan_koordinat[0];
                        //do nothing
                    }
                    else{
                        x_target = atoi(&masukan_koordinat[0]);
                        /*printf("x_target = %d\n", x_target);*/
                        y_target = atoi(&masukan_koordinat[2]);
                        /*printf("y_target = %d\n", y_target);*/
                        if (!(is_empty_routing(pcb,
                        n_rows, n_cols, x_target, y_target)==1)){
                            printf("ada jalur yang bertabrakan\n");
                        }
                        else{
                            /*printf("(review)input user adalah '%c'\n", input_user);*/
                            pcb[x_target-1][y_target-1].simbol=input_user;
                            i=i+1;
                            printf("berhasil input routing\n");
                            printf("diisi '%c'\n", pcb[x_target-1][y_target-1].simbol);
                        }
                    }
                    printf("(review)input = %c\n", input_user);
                }while (!((input_user=='q')||(input_user=='Q')
                    ||(input_user=='n')||(input_user=='N')));
            }
        }while (!((input_user=='q')||(input_user=='Q')
            ||(input_user=='n')||(input_user=='N')));
        printf("\n");
    }while (!((input_user=='q')||(input_user=='Q')));
    printf("\n");
}

int is_empty_layout(pin pcb[][40], int n_rows, int n_cols,
                    int x_awal, int x_akhir,
                    int y_awal, int y_akhir, char *input_user)
{
    int i;
    int jumlah_pin_terisi;
    jumlah_pin_terisi=0;
    if (x_awal == x_akhir)
    {
        for(i = (y_awal-1); i <= (y_akhir-1); i++)
        {
            //debug printf("panjang string = %d\n", strlen(pcb[x_awal-1][i].name));
            if (strlen(pcb[x_awal-1][i].name) != 0)
            {
                jumlah_pin_terisi=jumlah_pin_terisi+1;
            }
        }
    }
    else if (y_awal == y_akhir)
    {
        for(i = (x_awal-1); i <= (x_akhir-1); i++)
        {
            //debug printf("panjang string = %d\n", strlen(pcb[i][y_awal-1].name));
            if (strlen(pcb[i][y_awal-1].name) != 0)
            {
                jumlah_pin_terisi=jumlah_pin_terisi+1;
            }
        }
    }
    else
    {
        if (input_user[0]!='T'){
            printf("Komponen menyilang, dilarang menyilang\n");
            return 0;
        }
        else{
            return 1;
        }
    }
    if (jumlah_pin_terisi>0){
        return 0;
    }
    else{
        return 1;
    }
}

int is_empty_routing(pin pcb[][40], int n_rows, int n_cols,
                    int x_target, int y_target)
{
    /*char temp[3];*/
    printf("isi target = '%c'\n", pcb[x_target-1][y_target-1].simbol);
    /*printf("isi temp = '%c'\n", &temp[0]);*/
    if (!(pcb[x_target-1][y_target-1].simbol =='\0' )){
        printf("return 0\n");
        return 0;
    }
    else{
        printf("return 1\n");
        return 1;
    }
}

int is_benar_komponen(char *input_user,
                        int x_1, int x_2, int x_3,
                        int y_1, int y_2, int y_3)
{
    double jarak_antar_kaki;
    jarak_antar_kaki = sqrt(pow((x_1-x_2),2)
                            +pow((y_1-y_2),2));
    if (input_user[0]=='R')
    {
        if (jarak_antar_kaki>=4){
            return 1;
        }
        else{
            return 0;
        }
    }
    else if (input_user[0]=='C')
    {
        if (jarak_antar_kaki>=2){
            return 1;
        }
        else{
            return 0;
        }
    }
    else if (input_user[0]=='J')
    {
        if (jarak_antar_kaki>=1){
            return 1;
        }
        else{
            return 0;
        }
    }
    else if (input_user[0]=='T')
    {
        if (jarak_antar_kaki>=1){
            jarak_antar_kaki = sqrt(pow((x_2-x_3),2)
                            +pow((y_2-y_3),2));
            if (jarak_antar_kaki>=1){
                jarak_antar_kaki = sqrt(pow((x_3-x_1),2)
                            +pow((y_3-y_1),2));
                if (jarak_antar_kaki>=1){
                    return 1;
                }
                else{
                    return 0;
                }
            }
            else{
                return 0;
            }
        }
        else{
            return 0;
        }
    }
    else
    {
        return 0;
    }
}
