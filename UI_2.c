//USER INTERFACE PRGORAM

#include<stdio.h>
#include<stdlib.h>
//#include "manualLayoutver2.c"
//#include "ANJING.c"
//#include "ANJING.h"

typedef struct{
        char nama[3];
        int simbol;
        int netlist;
} pin;


pin pcb[40][40];
int n = 10, m = 10;
int i,j,k;
//ukuran pcb, di isi saaat create atau load;






int is_empty_layout(pin pcb[][40], int n_rows, int n_cols,
                    int x_awal, int x_akhir,
                    int y_awal, int y_akhir)
{
    int i;
    int jumlah_pin_terisi;
    jumlah_pin_terisi=0;
    if (x_awal == x_akhir)
    {
        for(i = (y_awal-1); i <= (y_akhir-1); i++)
        {
            //debug printf("panjang string = %d\n", strlen(pcb[x_awal-1][i].nama));
            if (strlen(pcb[x_awal-1][i].nama) != 0)
            {
                jumlah_pin_terisi=jumlah_pin_terisi+1;
            }
        }
    }
    else if (y_awal == y_akhir)
    {
        for(i = (x_awal-1); i <= (x_akhir-1); i++)
        {
            //debug printf("panjang string = %d\n", strlen(pcb[i][y_awal-1].nama));
            if (strlen(pcb[i][y_awal-1].nama) != 0)
            {
                jumlah_pin_terisi=jumlah_pin_terisi+1;
            }
        }
    }
    else
    {
        printf("Komponen menyilang, dilarang menyilang\n");
        return 0;
    }
    if (jumlah_pin_terisi>0){
        return 0;
    }
    else{
        return 1;
    }
} 

int is_empty_routing(pin pcb[40][40], int n_rows, int n_cols,
                    int x_target, int y_target)
{
    printf("isi target = '%c'\n", pcb[x_target-1][y_target-1].simbol);
    if (pcb[x_target-1][y_target-1].simbol != ' '){
        return 0;
    }
    else{
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
            /*printf("cek kebenaran jarak kaki\n"); (debug)
            printf("hasil is_benar_komponen = %d\n",
                   is_benar_komponen(input_user,
                                    x_1, x_2, x_3,
                                    y_1, y_2, y_3));
            printf("hasil is_empty_layout = %d\n",
                   is_empty_layout(pcb, n_rows, n_cols,
                                   x_1, x_2,
                                   y_1, y_2)); */ //debug
            if (!((is_benar_komponen(input_user,
                                    x_1, x_2, x_3,
                                    y_1, y_2, y_3)==1)
                &&(is_empty_layout(pcb, n_rows,
                                    n_cols, x_1,
                                    x_2, y_1,
                                    y_2)==1))){
                printf("spesifikasi salah atau komponen menabrak\n");
            }
            else{
                printf("spesifikasi benar\n");
                if (input_user[0] == 'T'){
                    strcpy(pcb[x_1-1][y_1-1].nama, input_user);
                    strcpy(pcb[x_2-1][y_2-1].nama, input_user);
                    strcpy(pcb[x_3-1][y_3-1].nama, input_user);
                }
                else{
                    strcpy(pcb[x_1-1][y_1-1].nama, input_user);
                    strcpy(pcb[x_2-1][y_2-1].nama, input_user);
                }
            }
        }
    }while (!((strcmp(input_user,"q")==0)||(strcmp(input_user,"Q")==0)));
}

void menuawal(){	
int menu;
	
	printf("Menu:\n");
	printf("\t1. Buat Proyek Baru\n");
	printf("\t2. Muat Proyek dari Berkas\n");
	printf("\t3. Keluar");
	printf("\nMasukan :");
	scanf("%d",&menu);
	while ((menu>3) ||(menu<0)) {
		printf("Masukan salah");
		printf("\nMasukan :");
		scanf("%d",&menu);	
	}
	switch (menu){
		case 1 :
			{
				printf("createNewProject();\n");
		//	createnewProject();
			break;
			}
		case 2 :
			{
				printf("loadProject();\n");
		//	loadProject();
			break;
			}
		default :
			{
				exit(0);
			break;
			}
		}
	
}
int menuMode (){
	int out = 0;
	int mode;
	printf("[Menu Utama]\n");
	printf("Pilihan Mode\n");
	printf("\t1. Tampilkan Layout\n");
	printf("\t2. Layout Manual\n");
	printf("\t3. Tampilkan Routing\n");
	printf("\t4. Routing Manual\n");		
	printf("\t5. Layout Otomatis\n");
	printf("\t6. Routing Otomatis\n");
	printf("\t7. Design Rule Checker\n");
	printf("\t8. Simpan Proyek dan Keluar");
	printf("\nPilih Mode: ");
	scanf("%d",&mode);
	while ((mode>8) ||(mode<0)) {
		printf("Masukan salah");
		printf("\nPilih Mode: ");
		scanf("%d",&mode);	
	}
	switch (mode) {
	
		case 1: {
			printf("printlayout(...);\n");

			printf("[Layout Rangkaian pada PCB Dot Matriks]\n");
    		printf("\t");
    		for(i=0;i<m;i++){
        		printf("%d\t",i+1);
    			}printf("\n");


	    for (i=0;i<n;i++){
    	    printf("%d\t",i+1);
       			 for ( j=0;j<m;j++){
           		 printf("%s\t",pcb[i][j].nama);
        		}
       		 printf("\n");
  			}
			return 1;
			break;
		}
		
		case 2: {
			printf("manuallayout(...);\n");
			manual_layout(&pcb, n, m);
			printf("Bangsat %s",pcb[1][1].nama);
			printf("gagal %s",pcb[3][1].nama);
			return 1;
			break;
		}
		case 3: {
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
			return 1;
			break;
		}
		case 4: {
			printf("manualRout(...);\n");
			return 1;
			break;
		}
		case 5: {
			printf("autolayout(...);\n");
			return 1;
			break;
		}
		case 6: {
			printf("autorout(...);\n");
			return 1;
			break;
		}
		case 7: {
			printf("DRC(...);\n");
			return 1;
			break;
		}
		default :{
			printf("Exiting....\n");
			return 0;
			break;
		}

	}

}

int main() {
	
	int cek = 1;
	menuawal();
	do {
	cek = menuMode();
	if (cek == 0) {
		menuawal();
		menuMode();
	}
	else{
		menuMode();
	}
	} while (cek=1);
}
