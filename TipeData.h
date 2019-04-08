#ifndef TIPEDATA_H
#define TIPEDATA_H
typedef struct
//untuk Tipe Nama File yang ingin disave
{
	char namaFile_Layout[100];
	char namaFile_Routing[100];
}fname;

typedef struct
// structure memuat jumlah baris dan kolom dalam PCB
{
	int m,n;	
}BesarMatriks;

typedef struct
// structure untuk koordinat
{
	int x;
	int y;
}koordinat;
typedef struct
// structure memuat nilai-nilai dalam pin
{
	char Name[3];
	char Simbol;
	int NetList;
} Pin;
typedef struct
{
	Pin pin[40][40];
} PCB;
#endif
