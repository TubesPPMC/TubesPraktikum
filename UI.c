//USER INTERFACE PRGORAM

#include<stdio.h>
#include<stdlib.h>
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
			return 1;
			break;
		}
		case 2: {
			printf("manuallayout(...);\n");
			return 1;
			break;
		}
		case 3: {
			printf("printRout(...);\n");
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
