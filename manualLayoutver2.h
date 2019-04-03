#ifndef MANUALLAYOUTVER2_H
#define MANUSLLSYOUTVER2_H

typedef struct{
        char name[3];
        int simbol;
        int netlist;
} pin;

void manual_layout(pin pcb[][40], int n_rows, int n_cols);

void manual_routing(pin pcb[][40], int n_rows, int n_cols);

int is_empty_layout(pin pcb[][40], int n_rows, int n_cols,
                    int x_awal, int x_akhir,
                    int y_awal, int y_akhir);

int is_empty_routing(pin pcb[][40], int n_rows, int n_cols,
                    int x_target, int y_target);
int is_benar_komponen(char *input_user,
                        int x_1, int x_2, int x_3,
                        int y_1, int y_2, int y_3);
#endif
