//USER INTERFACE PRGORAM

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
//#include "manualLayoutver2.c"
//#include "ANJING.c"
//#include "ANJING.h"

typedef struct{
        char nama[3];
        int simbol;
        int netlist;
} pin;

typedef struct{
        char nama[3];
        char netlist[3][1];
} nl;


pin pcb[40][40];
char str[100];
int netlist_terakhir;
int n , m ;
int i,j,k;
int pilihan_netlist;
int temp_int;
char simbol_terpakai[];
//ukuran pcb, di isi saaat create atau load;

int is_exist_karakter(char simbol_terpakai[], char dicari){
    int i;
    int panjang;
    int found;
    found = 0;
    panjang = strlen(simbol_terpakai);
    for (i=0; i<=panjang-1; i++){
        if (simbol_terpakai[i]==dicari){
            found = 1;
        }
    }
    return (found);
}

void manual_layout(pin pcb[][40], int n_rows, int n_cols)
{
    int x_1, y_1, x_2, y_2, x_3, y_3;
    char input_user[2];
    printf("[Mode Layout]\n");                      //Inisialisasi Mode Manual Layout
    printf("Isi `q` atau `Q` untuk kembali ke menu\n");
    do{
        printf("Pilih Komponen (R,C,T,J): ");       //Pembacaan Komponen dari User
        scanf("%s", input_user);
        if ((strcmp(input_user,"q")==0)||(strcmp(input_user,"Q")==0)){  //Kasus Langsung Quit
            //do nothing
        }
        else{                                                           //Kasus Tidak Quit
            if (input_user[0] == 'T'){                                         //Kasus Input Transistor
                printf("Koordinat Kaki Te: ");                                      //Input Koordinat Kaki Transistor
                scanf("%d,%d", &x_1, &y_1);
                printf("Koordinat Kaki Tb: ");
                scanf("%d,%d", &x_2, &y_2);
                printf("Koordinat Kaki Tc: ");
                scanf("%d,%d", &x_3, &y_3);
            }
            else{                                                               //Kasus Input Bukan Transistor
                printf("Koordinat Kaki 1: ");                                       //Input Koordinat Kaki Komponen
                scanf("%d,%d", &x_1, &y_1);
                printf("Koordinat Kaki 2: ");
                scanf("%d,%d", &x_2, &y_2);
                x_3 = 0; y_3 = 0;
            }
            if (!((is_benar_komponen(input_user,                                //Cek Kebenaran Komponen dan Apakah Layout Kosong
                                    x_1, x_2, x_3,
                                    y_1, y_2, y_3)==1)
                &&(is_empty_layout(pcb, n_rows,
                                    n_cols, x_1,
                                    x_2, y_1,
                                    y_2, x_3,
                                    y_3, input_user)==1))){
                printf("-\t-\t-\t-\t-spesifikasi salah atau komponen menabrak\n");    //Jika Spesifikasi Salah
            }
            else{
                printf("-\t-\t-\t-\t-spesifikasi benar, komponen berhasil di input\n");//Jika Spesifikasi Benar
                if (input_user[0] == 'T'){                                          //Kasus Komponen Transistor
                    pcb[x_1-1][y_1-1].nama[0] = 'T';                                    //Input Kaki Transistor Pada Layout
                    pcb[x_1-1][y_1-1].nama[1] = 'e';
                    pcb[x_2-1][y_2-1].nama[0] = 'T';
                    pcb[x_2-1][y_2-1].nama[1] = 'b';
                    pcb[x_3-1][y_3-1].nama[0] = 'T';
                    pcb[x_3-1][y_3-1].nama[1] = 'c';
                }
                else{                                                               //Kasus Komponnen Bukan Transistor
                    strcpy(pcb[x_1-1][y_1-1].nama, input_user);                         //Input Kaki Komponen
                    strcpy(pcb[x_2-1][y_2-1].nama, input_user);
                }
            }
        }
    }while (!((strcmp(input_user,"q")==0)||(strcmp(input_user,"Q")==0)));       //Keluar Jika Input User Quit
}

void manual_routing(pin pcb[][40], int n_rows, int n_cols)
{
    int i, j;
    int x_target, y_target, x_last, y_last;
    int jumlah_jalur_bertabrakan;
    char temp;
    char input_user, simbol_sementara;
    char masukan_koordinat[3];
    printf("[Mode Routing]\n");                                             //Inisiasi Mode Routing
    printf("Isi `q` atau `Q` untuk kembali ke menu\n");
    printf("Isi `n` atau `N` untuk memulai pada simpul (node) baru\n");
    do{
        printf("Pilih Simbol (!,@,#,$,%,^,&,*,(,)): ");
        do{
            scanf(" %c", &input_user);                                          //Baca Simbol Dari User
            if ((input_user=='q')||(input_user=='Q')                                //Kasus User Langsung Quit
                ||(input_user=='n')||(input_user=='N')){
                //do nothing
            }
            else{                                                                   //Kasus User Tidak Quit
                printf("is_exist_karakter = %d\n", is_exist_karakter(simbol_terpakai, input_user));
                simbol_sementara = input_user;
                if (!(is_exist_karakter(simbol_terpakai, input_user)==1)){
                    i=1;
                    x_last = -99; y_last = -99;         //Jika Belum Ada X dan Y Terakhir
                    temp = input_user;
                    do{
                        printf("Koordinat %d: ", i);                                        //Input Koordinat ke-i
                        scanf("%s", masukan_koordinat);
                        input_user = temp;
                        if ((strcmp(masukan_koordinat,"n")==0)||                                //Kasus Jika Quit
                            (strcmp(masukan_koordinat,"N")==0)||
                            (strcmp(masukan_koordinat,"q")==0)||
                            (strcmp(masukan_koordinat,"Q")==0)){
                            input_user = masukan_koordinat[0];
                            //do nothing
                        }
                        else{                                                                   //Kasus Jika Tidak Quit
                            x_target = atoi(&masukan_koordinat[0]);
                            y_target = atoi(&masukan_koordinat[2]);
                            if ((x_last == -99)&&(y_last == -99)) {                                 //Kasus Belum Ada X dan Y Last
                                x_last = x_target;          //X dan Y dari input pertama menjadi X dan Y Terakhir
                                y_last = y_target;
                                i = i + 1;
                            }
                            else {
                                jumlah_jalur_bertabrakan = 0;                                       //Kasus Input Kedua dst
                                if (x_last == x_target){                                                //Transverse Ke Y jika X sama
                                        for(j = (y_last); j <= (y_target); j++)
                                        {
                                            if (is_empty_routing(pcb, n_rows, n_cols,
                                                                    x_target, j) != 1)
                                            {
                                                jumlah_jalur_bertabrakan=jumlah_jalur_bertabrakan+1;
                                            }
                                        }
                                }
                                else if (y_last == y_target){                                           //Transverse Ke X jika Y sama
                                        for(j = (x_last); i <= (x_target); i++)
                                        {
                                            if (is_empty_routing(pcb, n_rows, n_cols,
                                                                    j, y_target) != 1)
                                            {
                                                jumlah_jalur_bertabrakan=jumlah_jalur_bertabrakan+1;
                                            }
                                        }
                                }
                                if (pcb[x_last-1][y_last-1].simbol ==input_user ){                  //Kasus Jika Jalur Sambung Menyambung
                                    jumlah_jalur_bertabrakan=jumlah_jalur_bertabrakan-1;
                                }
                                if (jumlah_jalur_bertabrakan > 0){
                                    printf("-\t-\t-\t-\t-ada jalur yang bertabrakan\n");            //Jika jalur tabrakan ada, maka jangan input
                                }
                                else{                                                               //Jika jalur tidak tabrakan, isi jalur
                                    if (x_last == x_target){
                                        for(j = (y_last); j <= (y_target); j++)
                                        {
                                            pcb[x_target-1][j-1].simbol=input_user;
                                            pcb[x_target-1][j-1].netlist=netlist_terakhir + 1;
                                        }
                                    }
                                    else if (y_last == y_target){
                                            for(j = (x_last); j <= (x_target); j++)
                                            {
                                                pcb[j-1][y_target-1].simbol=input_user;
                                                pcb[j-1][y_target-1].simbol=netlist_terakhir + 1;
                                            }
                                    }
                                    i=i+1;
                                    x_last = x_target; //Jika Bukan Input pertama, X dan Y sekarang mnejadi X
                                    y_last = y_target;      // dan Y Last Untuk Input Berikutnya
                                    printf("-\t-\t-\t-\t-berhasil input routing\n");
                                    }
                                }
                            }
                        }while (!((input_user=='q')||(input_user=='Q')                          //Keluar jika user quit atau ganti node
                            ||(input_user=='n')||(input_user=='N')));
                    temp_int=strlen(simbol_terpakai);
                    printf("panjang array simbol_terpakai = %d\n", temp_int);
                    simbol_terpakai[temp_int]=simbol_sementara;
                    printf("karakter %c diisi pada array simbol_terpakai\n", simbol_terpakai[temp_int]);
                    netlist_terakhir = netlist_terakhir + 1;
                    } else {
                        printf("-simbol ini sudah dipakai sebelumnya pada jalur berbeda.\n");
                        printf("-jika anda ingin melanjutkan jalur sebelumnya,\n");
                        printf("--anda harus melihat netlist yang ada pada jalur tersebut\n");
                        printf("--dan menginput netlist pada jalur baru secara manual.\n");
                        printf("-jika anda akan membuat jalur terpisah, maka anda tidak perlu\n");
                        printf("--menginput netlist secara manual.\n");
                        printf("-netlist akan dilanjutkan dengan netlist terakhir yang ada.\n");
                        printf("-Input pilihan anda\n");
                        printf("\t(1=lanjutkan netlist pada jalur yang sudah ada)\n");
                        printf("\t(2=bedakan netlist sebagai jalur terpisah)\n");
                        printf("Pilihan: ");
                        scanf("%d", &pilihan_netlist);
                        if (pilihan_netlist == 1){ //ini
                            printf("Input netlist yang akan dilanjutkan: ");
                            scanf("%d", &pilihan_netlist);
                            /////////////////////////////////////////////////
                            i=1;
                            x_last = -99; y_last = -99;         //Jika Belum Ada X dan Y Terakhir
                            temp = input_user;
                            do{
                                printf("Koordinat %d: ", i);                                        //Input Koordinat ke-i
                                scanf("%s", masukan_koordinat);
                                input_user = temp;
                                if ((strcmp(masukan_koordinat,"n")==0)||                                //Kasus Jika Quit
                                    (strcmp(masukan_koordinat,"N")==0)||
                                    (strcmp(masukan_koordinat,"q")==0)||
                                    (strcmp(masukan_koordinat,"Q")==0)){
                                    input_user = masukan_koordinat[0];
                                    //do nothing
                                }
                                else{                                                                   //Kasus Jika Tidak Quit
                                    x_target = atoi(&masukan_koordinat[0]);
                                    y_target = atoi(&masukan_koordinat[2]);
                                    if ((x_last == -99)&&(y_last == -99)) {                                 //Kasus Belum Ada X dan Y Last
                                        x_last = x_target;          //X dan Y dari input pertama menjadi X dan Y Terakhir
                                        y_last = y_target;
                                        i = i + 1;
                                    }
                                    else {
                                        jumlah_jalur_bertabrakan = 0;                                       //Kasus Input Kedua dst
                                        if (x_last == x_target){                                                //Transverse Ke Y jika X sama
                                                for(j = (y_last); j <= (y_target); j++)
                                                {
                                                    if (is_empty_routing(pcb, n_rows, n_cols,
                                                                            x_target, j) != 1)
                                                    {
                                                        jumlah_jalur_bertabrakan=jumlah_jalur_bertabrakan+1;
                                                    }
                                                }
                                        }
                                        else if (y_last == y_target){                                           //Transverse Ke X jika Y sama
                                                for(j = (x_last); i <= (x_target); i++)
                                                {
                                                    if (is_empty_routing(pcb, n_rows, n_cols,
                                                                            j, y_target) != 1)
                                                    {
                                                        jumlah_jalur_bertabrakan=jumlah_jalur_bertabrakan+1;
                                                    }
                                                }
                                        }
                                        if (pcb[x_last-1][y_last-1].simbol ==input_user ){                  //Kasus Jika Jalur Sambung Menyambung
                                            jumlah_jalur_bertabrakan=jumlah_jalur_bertabrakan-1;
                                        }
                                        if (jumlah_jalur_bertabrakan > 0){
                                            printf("-\t-\t-\t-\t-ada jalur yang bertabrakan\n");            //Jika jalur tabrakan ada, maka jangan input
                                        }
                                        else{                                                               //Jika jalur tidak tabrakan, isi jalur
                                            if (x_last == x_target){
                                                for(j = (y_last); j <= (y_target); j++)
                                                {
                                                    pcb[x_target-1][j-1].simbol=input_user;
                                                    pcb[x_target-1][j-1].netlist=pilihan_netlist;
                                                }
                                            }
                                            else if (y_last == y_target){
                                                    for(j = (x_last); j <= (x_target); j++)
                                                    {
                                                        pcb[j-1][y_target-1].simbol=input_user;
                                                        pcb[j-1][y_target-1].simbol=pilihan_netlist;
                                                    }
                                            }
                                            i=i+1;
                                            x_last = x_target; //Jika Bukan Input pertama, X dan Y sekarang mnejadi X
                                            y_last = y_target;      // dan Y Last Untuk Input Berikutnya
                                            printf("-\t-\t-\t-\t-berhasil input routing\n");
                                            }
                                        }
                                    }
                                }while (!((input_user=='q')||(input_user=='Q')                          //Keluar jika user quit atau ganti node
                                    ||(input_user=='n')||(input_user=='N')));

                            /////////////////////////////////////////////////
                        } else if (pilihan_netlist==2){
                            //################################################
                            i=1;
                            x_last = -99; y_last = -99;         //Jika Belum Ada X dan Y Terakhir
                            temp = input_user;
                            do{
                                printf("Koordinat %d: ", i);                                        //Input Koordinat ke-i
                                scanf("%s", masukan_koordinat);
                                input_user = temp;
                                if ((strcmp(masukan_koordinat,"n")==0)||                                //Kasus Jika Quit
                                    (strcmp(masukan_koordinat,"N")==0)||
                                    (strcmp(masukan_koordinat,"q")==0)||
                                    (strcmp(masukan_koordinat,"Q")==0)){
                                    input_user = masukan_koordinat[0];
                                    //do nothing
                                }
                                else{                                                                   //Kasus Jika Tidak Quit
                                    x_target = atoi(&masukan_koordinat[0]);
                                    y_target = atoi(&masukan_koordinat[2]);
                                    if ((x_last == -99)&&(y_last == -99)) {                                 //Kasus Belum Ada X dan Y Last
                                        x_last = x_target;          //X dan Y dari input pertama menjadi X dan Y Terakhir
                                        y_last = y_target;
                                        i = i + 1;
                                    }
                                    else {
                                        jumlah_jalur_bertabrakan = 0;                                       //Kasus Input Kedua dst
                                        if (x_last == x_target){                                                //Transverse Ke Y jika X sama
                                                for(j = (y_last); j <= (y_target); j++)
                                                {
                                                    if (is_empty_routing(pcb, n_rows, n_cols,
                                                                            x_target, j) != 1)
                                                    {
                                                        jumlah_jalur_bertabrakan=jumlah_jalur_bertabrakan+1;
                                                    }
                                                }
                                        }
                                        else if (y_last == y_target){                                           //Transverse Ke X jika Y sama
                                                for(j = (x_last); i <= (x_target); i++)
                                                {
                                                    if (is_empty_routing(pcb, n_rows, n_cols,
                                                                            j, y_target) != 1)
                                                    {
                                                        jumlah_jalur_bertabrakan=jumlah_jalur_bertabrakan+1;
                                                    }
                                                }
                                        }
                                        if (pcb[x_last-1][y_last-1].simbol ==input_user ){                  //Kasus Jika Jalur Sambung Menyambung
                                            jumlah_jalur_bertabrakan=jumlah_jalur_bertabrakan-1;
                                        }
                                        if (jumlah_jalur_bertabrakan > 0){
                                            printf("-\t-\t-\t-\t-ada jalur yang bertabrakan\n");            //Jika jalur tabrakan ada, maka jangan input
                                        }
                                        else{                                                               //Jika jalur tidak tabrakan, isi jalur
                                            if (x_last == x_target){
                                                for(j = (y_last); j <= (y_target); j++)
                                                {
                                                    pcb[x_target-1][j-1].simbol=input_user;
                                                    pcb[x_target-1][j-1].netlist=netlist_terakhir + 1;
                                                }
                                            }
                                            else if (y_last == y_target){
                                                    for(j = (x_last); j <= (x_target); j++)
                                                    {
                                                        pcb[j-1][y_target-1].simbol=input_user;
                                                        pcb[j-1][y_target-1].simbol=netlist_terakhir + 1;
                                                    }
                                            }
                                            i=i+1;
                                            x_last = x_target; //Jika Bukan Input pertama, X dan Y sekarang mnejadi X
                                            y_last = y_target;      // dan Y Last Untuk Input Berikutnya
                                            printf("-\t-\t-\t-\t-berhasil input routing\n");
                                            }
                                        }
                                    }
                                }while (!((input_user=='q')||(input_user=='Q')                          //Keluar jika user quit atau ganti node
                                    ||(input_user=='n')||(input_user=='N')));
                            //################################################
                        netlist_terakhir=netlist_terakhir+1;
                        }
                    }
                }
            }while (!((input_user=='q')||(input_user=='Q')                              //Keluar jika user quit atau ganti node
                ||(input_user=='n')||(input_user=='N')));
            printf("\n");
        }while (!((input_user=='q')||(input_user=='Q')));                           //Keluar jika user quit
        printf("\n");
}

int is_empty_layout(pin pcb[][40], int n_rows, int n_cols,
                    int x_1, int x_2,
                    int y_1, int y_2,
                    int x_3, int y_3, char *input_user)
{
    int i;
    int jumlah_pin_terisi;
    jumlah_pin_terisi=0;    //Kasus normal dan bukan komponen transistor
    if (x_1 == x_2)             //Cek semua Y jika X sama
    {
        for(i = (y_1-1); i <= (y_2-1); i++)
        {
            if (strlen(pcb[x_1-1][i].nama) != 0)
            {
                jumlah_pin_terisi=jumlah_pin_terisi+1;
            }
        }
    }
    else if (y_1 == y_2)        //Cek semua X jika Y sama
    {
        for(i = (x_1-1); i <= (x_2-1); i++)
        {
            if (strlen(pcb[i][y_1-1].nama) != 0)
            {
                jumlah_pin_terisi=jumlah_pin_terisi+1;
            }
        }
    }
    else
    {
        if (input_user[0]!='T'){    //Jika kaki komponen menyilang dan bukan transistor maka spesifikasi salah
            printf("Komponen menyilang, dilarang menyilang\n");
            return 0;
        }
        else{                       //Jika kaki komponen menyilang tapi transistor
            if (strlen(pcb[x_1-1][y_1-1].nama) != 0){   //hanya cek apakah pada posisi kaki terdapat komponen lain
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
	printf("\n Routing disimpan dalam berkas %s fie",fil);
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

void saveProject_Net(char *fil,int n, int m, pin pcb[][40]){
	printf("\n Routing disimpan dalam berkas %s fie",fil);
    FILE *fp;
    char *net;
    net = strcat(fil,"_net.csv");
    fp = fopen(net,"w+");
    for (i=0 ; i<40; i ++){
    	for (j=0; j<40; j++){

    	fprintf(fp,"%d;", pcb[i][j].netlist );
		}
		fprintf(fp,"\n");
	}
    fclose(fp);
    printf("\n %s file created",net);
}
void createnewProject(){
	printf("====== Membuat Proyek Baru ======\n");
	printf("Masukkan nama proyek: ");
	scanf("%s",str);
	printf("Masukkan ukuran PCB NxM (N,M<40): ");
	scanf("%d,%d", &n, &m);
	}

void loadProject_net(pin pcb[][40], char *st){

	FILE *fp;
	char *nam;
    nam = strcat(st,"_net.csv");
    fp = fopen(nam,"r+");
	if (fp == NULL)
    {
        printf("Error! file doesnt exist");
        // Program exits if file pointer returns NULL.
        exit(1);
    }
    char c;
   	int i,j,k,w, net, hasil;
	i= 0;
	k=0;
	j=0;
	w=0;
	int temp;
	hasil = 0;
	printf("file open succes\n");
	while( w < 3198 ){
		c=fgetc(fp);
		net = c - '0';
		printf("data ke %d = %d\n",w,net);
		w++;
		switch (c) {

		case ';' : {
			if (temp == 0){
			pcb[j][i].netlist = 0;
			}else{
			pcb[j][i].netlist= temp;
			}
			printf("i,j =%d,%d\n",i,j);
			i++;
			k=0;
			temp=0;
			break;
		}
		case '\n' : {
			j++;
			i=0;

			break;
		}

		default :{
			temp = net;
			printf("%d\n",temp);
			k++;
			if (temp>hasil){hasil=temp;
			}
			break;
		}
	}

}
	netlist_terakhir = hasil;
	fclose(fp);}


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
			char chr2[100];
			strcpy(chr,str);
			strcpy(chr1,str);
			strcpy(chr2,str);
			loadProject_layout(&pcb,chr);
			loadProject_rout(&pcb,chr1);
			loadProject_net(&pcb,chr2);
			free (chr);
			free (chr1);
			free (chr2);
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
	printf("\t8. Tampilkan Pesebaran\n");
	printf("\t9. Simpan Proyek dan Keluar");
	printf("\nPilih Mode: ");
	scanf("%d",&mode);
	while ((mode>9) ||(mode<0)) {
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
            FILE* inp;
            char nf[100];
            printf("Masukkan File DRC (dalam format .txt): ");
            scanf("%s",nf);
            inp = fopen(nf,"r");
            char arr[100][50];
            int i = 0;
            while(1){
                char r = (char)fgetc(inp);
                int k = 0;
                while(r!='\t' && !feof(inp)){
                    arr[i][k++] = r;
                    r = (char)fgetc(inp);
                }
                arr[i][k]=0;
                if(feof(inp)){
                    break;
                }
                i++;
            }

            int j;
            nl li [100];

            for(j = 0;j<=i;j=j+3){
                printf("%s  ",arr[j]);
                strcpy(li[j].nama,arr[j]);
            }

            for(j = 0;(j<=i);j=j+1){
                if((j%3 == 1)){
                    printf("~%s~",arr[j]);
                    strcpy(li[j].netlist[0],arr[j]);
                } else if ((j%3 == 2)) {
                    printf("!%s!",arr[j]);
                    strcpy(li[j].netlist[1],arr[j]);
                }
            }

            int k1,k2,k3,k4,k5,k6;
            int cek=0;
            char tempo[10],nama1[10],nama2[10];

            for(k1=0;k1<=9;k1++){
                strcpy(tempo,li[k1].netlist[0]);
                strcpy(nama1,li[k1].nama);
                for(k2=0;k2<=9;k2++){
                    if(strcmp(li[k2].netlist[0],tempo)){
                        strcmp(li[k2].netlist,NULL);
                        strcpy(nama2,li[k2].nama);
                        for (i=0;i<5;i++){
                            for ( j=0;j<m;j++){
                                for(k5=0;k5<n;k5++){
                                    for(k6=0;k6<n;k6++){
                                        if(strcmp(pcb[i][j].nama,li[k1].nama)){
                                            if(strcmp(pcb[k5][k6].nama,li[k2].nama)){
                                                if(strcmp(pcb[i][j].simbol,pcb[k5][k6].simbol)){
                                                    cek = cek+1;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }

            printf("%d/%d Rule is Checked",cek,7);
			return 1;
			break;
		}
		case 8: {
			printf("[Pesebaran Netlist Rangkaian pada PCB Dot Matriks]\n");
			printf("\t");
   				for( i=0;i<m;++i){
    			printf("%d\t",i+1);
    		}printf("\n");

	    	for (i=0;i<n;++i){
    	    printf("%d\t",i+1);
       			 for (j=0;j<m;j++){
        	    printf("%d\t",pcb[i][j].netlist);
        		}
       		 printf("\n");
   			 }

			return 1;
			break;
		}
		default :{
			char chr[100];
			char chr2[100];
			strcpy(chr,str);
			strcpy(chr2,str);
			saveProject_Layout(str,n,m,pcb);
			saveProject_Rout(chr,n,m,pcb);
			saveProject_Net(chr2,n,m,pcb);
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
