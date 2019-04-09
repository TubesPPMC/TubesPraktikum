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
char str[100];
int n , m ;
int i,j,k;
//ukuran pcb, di isi saaat create atau load;

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
            /*printf("cek kebenaran jarak kaki\n"); //debug)
            printf("hasil is_benar_komponen = %d\n",
                   is_benar_komponen(input_user,
                                    x_1, x_2, x_3,
                                    y_1, y_2, y_3));
            printf("hasil is_empty_layout = %d\n",
                   is_empty_layout(pcb, n_rows, n_cols,
                                   x_1, x_2,
                                   y_1, y_2, input_user));*/  //debug
            if (!((is_benar_komponen(input_user,
                                    x_1, x_2, x_3,
                                    y_1, y_2, y_3)==1)
                &&(is_empty_layout(pcb, n_rows,
                                    n_cols, x_1,
                                    x_2, y_1,
                                    y_2, x_3,
                                    y_3, input_user)==1))){
                printf("-\t-\t-\t-\t-spesifikasi salah atau komponen menabrak\n");
            }
            else{
                printf("-\t-\t-\t-\t-spesifikasi benar, komponen berhasil di input\n");
                if (input_user[0] == 'T'){
                    pcb[x_1-1][y_1-1].nama[0] = 'T';
                    pcb[x_1-1][y_1-1].nama[1] = 'e';
                    pcb[x_2-1][y_2-1].nama[0] = 'T';
                    pcb[x_2-1][y_2-1].nama[1] = 'b';
                    pcb[x_3-1][y_3-1].nama[0] = 'T';
                    pcb[x_3-1][y_3-1].nama[1] = 'c';
                    /*printf("koordinat Tc = %d , %d\n", x_3, y_3);
                    printf("%s\n", pcb[x_3-1][y_3-1].nama);*/
                }
                else{
                    strcpy(pcb[x_1-1][y_1-1].nama, input_user);
                    strcpy(pcb[x_2-1][y_2-1].nama, input_user);
                    /*printf("%s\n", pcb[x_1-1][y_1-1].nama);
                    printf("%s\n", pcb[x_2-1][y_2-1].nama);*/
                }
            }
        }
    }while (!((strcmp(input_user,"q")==0)||(strcmp(input_user,"Q")==0)));
}

void manual_routing(pin pcb[][40], int n_rows, int n_cols)
{
    int i, j;
    int x_target, y_target, x_last, y_last;
    int jumlah_jalur_bertabrakan;
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
                x_last = -99; y_last = -99;
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
                        /*printf("input koordinat n/N/q/Q = %s\n", masukan_koordinat);*/
                        input_user = masukan_koordinat[0];
                        //do nothing
                    }
                    else{
                        x_target = atoi(&masukan_koordinat[0]);
                        /*printf("x_target = %d\n", x_target);*/
                        y_target = atoi(&masukan_koordinat[2]);
                        /*printf("y_target = %d\n", y_target);*/
                        if ((x_last == -99)&&(y_last == -99)) {
                            x_last = x_target;
                            y_last = y_target;
                            i = i + 1;
                        }
                        else {
                            jumlah_jalur_bertabrakan = 0;
                            if (x_last == x_target){
                                    for(j = (y_last); j <= (y_target); j++)
                                    {
                                        if (is_empty_routing(pcb, n_rows, n_cols,
                                                                x_target, j) != 1)
                                        {
                                            jumlah_jalur_bertabrakan=jumlah_jalur_bertabrakan+1;
                                        }
                                    }
                            }
                            else if (y_last == y_target){
                                    for(j = (x_last); i <= (x_target); i++)
                                    {
                                        if (is_empty_routing(pcb, n_rows, n_cols,
                                                                j, y_target) != 1)
                                        {
                                            jumlah_jalur_bertabrakan=jumlah_jalur_bertabrakan+1;
                                        }
                                    }
                            }
                            if (pcb[x_last-1][y_last-1].simbol ==input_user ){
                                jumlah_jalur_bertabrakan=jumlah_jalur_bertabrakan-1;
                            }
                            if (jumlah_jalur_bertabrakan > 0){
                                printf("-\t-\t-\t-\t-ada jalur yang bertabrakan\n");
                            }
                            else{
                                /*printf("(review)input user adalah '%c'\n", input_user);*/
                                if (x_last == x_target){
                                    for(j = (y_last); j <= (y_target); j++)
                                    {
                                        pcb[x_target-1][j-1].simbol=input_user;
                                    }
                                }
                                else if (y_last == y_target){
                                        for(j = (x_last); j <= (x_target); j++)
                                        {
                                            pcb[j-1][y_target-1].simbol=input_user;
                                        }
                                }
                                i=i+1;
                                x_last = x_target;
                                y_last = y_target;
                                printf("-\t-\t-\t-\t-berhasil input routing\n");
                                /*printf("diisi '%c'\n", pcb[x_target-1][y_target-1].simbol);*/
                            }
                        }
                    }
                    /*printf("(review)input = %c\n", input_user);*/
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
                    int x_1, int x_2,
                    int y_1, int y_2,
                    int x_3, int y_3, char *input_user)
{
    int i;
    int jumlah_pin_terisi;
    jumlah_pin_terisi=0;
    if (x_1 == x_2)
    {
        for(i = (y_1-1); i <= (y_2-1); i++)
        {
            //debug printf("panjang string = %d\n", strlen(pcb[x_awal-1][i].nama));
            if (strlen(pcb[x_1-1][i].nama) != 0)
            {
                jumlah_pin_terisi=jumlah_pin_terisi+1;
            }
        }
    }
    else if (y_1 == y_2)
    {
        for(i = (x_1-1); i <= (x_2-1); i++)
        {
            //debug printf("panjang string = %d\n", strlen(pcb[i][y_awal-1].nama));
            if (strlen(pcb[i][y_1-1].nama) != 0)
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
            if (strlen(pcb[x_1-1][y_1-1].nama) != 0){
                jumlah_pin_terisi = jumlah_pin_terisi + 1;
            }
            if (strlen(pcb[x_2-1][y_2-1].nama) != 0){
                jumlah_pin_terisi = jumlah_pin_terisi + 1;
            }
            if (strlen(pcb[x_3-1][y_3-1].nama) != 0){
                jumlah_pin_terisi = jumlah_pin_terisi + 1;
            }
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
    /*printf("isi target(%d,%d) = '%c'\n", x_target, y_target, pcb[x_target-1][y_target-1].simbol);*/
    /*printf("isi temp = '%c'\n", &temp[0]);*/
    if (!(pcb[x_target-1][y_target-1].simbol =='\0' )){
        /*printf("return 0\n");*/
        return 0;
    }
    else{
        /*printf("return 1\n");*/
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

void saveProject_Layout(char *filename,int n, int m, pin pcb[][40]){
	printf("\n Layout disimpan dalam berkas %s_layout.csv file",filename);
    FILE *fp;
    char *layout;
    layout = strcat(filename,"_layout.csv");
    fp = fopen(layout,"w+");
    int i,j;
    for (i=0 ; i<40; i ++){
    	for (j=0; j<40; j++){
    	fprintf(fp,"%s;", pcb[i][j].nama);	
		}
    	fprintf(fp,"\n");
	}//inisiasi
    fclose(fp);
    printf("\n %s file created",layout);
}
void saveProject_Rout(char *fil,int n, int m, pin pcb[][40]){
	printf("\n Layout disimpan dalam berkas %s fie",fil);
    FILE *fp;
    char *rout;
    rout = strcat(fil,"_rout.csv");
    fp = fopen(rout,"w+");
    for (i=0 ; i<40; i ++){
    	for (j=0; j<40; j++){
		 
    	fprintf(fp,"%c;", pcb[i][j].simbol );
		}
		fprintf(fp,"\n");
	}
    fclose(fp);
    printf("\n %s file created",rout);
}
void createnewProject(){
	printf("====== Membuat Proyek Baru ======\n");
	printf("Masukkan nama proyek: ");
	scanf("%s",str);
	printf("Masukkan ukuran PCB NxM (N,M<40): ");
	scanf("%d,%d", &n, &m);
	}

void loadProject_layout(pin pcb[][40], char *st){

	FILE *fp;
	char *nam;
    nam = strcat(st,"_layout.csv");
    fp = fopen(nam,"r+");
	if (fp == NULL)
    {
        printf("Error! file doesnt exist");
        // Program exits if file pointer returns NULL.
        exit(1);      
    }
   char c; 
   	int i,j,k,w;
	i= 0;
	k=0;
	j=0;
	w=0;
	char temp[5];
	printf("file open succes\n");
	while( w <1647 ){
		
		c=fgetc(fp);
		
		w++;
		switch (c) {
		
		case ';' : {
			if (temp == NULL){
			strcpy(pcb[j][i].nama, " ");	
			}else{
			strcpy(pcb[j][i].nama, temp);
			}
			
			i++;
			k=0;
			temp[0]='\0';
			break;
		}
		case '\n' : {
			j++;
			i=0;
			
			break;
		}
		
		default :{
			temp[k] = c;
			k++;
			break;
		}
	}
			
}
	
	fclose(fp);}
	
void loadProject_rout(pin pcb[][40] ,char *st ){	
	FILE *fp;
	char *Rout;
	Rout = strcat(st,"_rout.csv");
    fp = fopen(Rout,"r+");
	if (fp == NULL)
    {
        printf("Error! file doesnt exist");
        // Program exits if file pointer returns NULL.
        exit(0);      
    }
    char c; 
	int i,j,k,w;
	i= 0;
	k=0;
	j=0;
	w=0;
	char temp;
	printf("file open succes\n");
	while( (w<3236)){
		
		c=fgetc(fp);
		w++;
		switch (c) {
		
		case ';' : {
			if (temp == NULL){
			pcb[j][i].simbol = ' ';	
			}else{
			pcb[j][i].simbol = temp;

			}
			i++;
			if (i>39){
				j++;
				i=0;
			}
			temp ='\0';
			k=0;
			break;
		}
		case '/n' : {
			j++;
			i=0;
			
			break;
		}
		
		default :{

			temp = c;
			k++;
			break;
		}
	}
			
}
	
	fclose(fp);
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
				createnewProject();
			break;
			}
		case 2 :
			{
				printf("loadProject();\n");
				printf("====== Membuka Proyek  ======\n");
				printf("Masukkan nama proyek: ");
				scanf("%s",str);
			printf("Masukkan ukuran PCB NxM (N,M<40): ");
			scanf("%d,%d", &n, &m);
			char chr[100];
			char chr1[100];
			strcpy(chr,str);
			strcpy(chr1,str);
			loadProject_layout(&pcb,chr);
			loadProject_rout(&pcb,chr1);
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
	printf("%d %d", n,m);
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
			manual_routing(&pcb, n, m);
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
			char chr[100];
			strcpy(chr,str);			
			saveProject_Layout(str,n,m,pcb);
			saveProject_Rout(chr,n,m,pcb);
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
		cek = menuMode();
	}
	else{
		menuMode();
	}
	} while (cek=1);
}
