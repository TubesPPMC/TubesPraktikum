#ifndef STORAGE_H
#define STROAGE_H
#include "TipeData.h"

//Prosedur untuk pembuatan project 
void NewProject(fname *nama, BesarMatriks *bm);
void SaveProject(PCB Board, fname *nama, BesarMatriks *bm);
void LoadProject(PCB *Board,fname *nama);

#endif

