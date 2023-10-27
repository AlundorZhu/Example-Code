#include <stdlib.h>
#include <stdio.h>
#include "canvas.h"

void create_canvas(Canvas* small_man){
    small_man->the_canvas = (char**)calloc(small_man->row, sizeof(char*));
    for(int i = 0; i < small_man->row; ++i){
        small_man->the_canvas[i] = (char*)calloc(small_man->col, sizeof(char));
        for(int j = 0; j < small_man->col; ++j){
            small_man->the_canvas[i][j] = '*';
        }
    }
}

void print_matrix (Canvas BIG_man){
    if(BIG_man.row < 10 && BIG_man.col < 10){
        for(int i = BIG_man.row - 1; i >= 0; --i) {
            printf("%2d", i);
            for(int j = 0; j < BIG_man.col; ++j) {
                printf(" %c", BIG_man.the_canvas[i][j]);
            }
            printf(" \n");
        }
        printf("  ");
        for(int i = 0; i < BIG_man.col; ++i){
            printf(" %d", i);
        }
        printf(" \n");
    }else{
        for(int i = BIG_man.row - 1; i >= 0; --i) {
            printf("%2d", i);
            for(int j = 0; j < BIG_man.col; ++j) {
                printf("  %c", BIG_man.the_canvas[i][j]);
            }
            printf(" \n");
        }
        printf("  ");
        for(int i = 0; i < BIG_man.col; ++i){
            printf("%3d", i);
        }
        printf(" \n");
    }
}

void rearrange_point(Canvas* artist){ // starts always < ends
    int temp;
    if(artist->row_start > artist->row_end){
        temp = artist->row_start;
        artist->row_start = artist->row_end;
        artist->row_end = temp;
    }
    if(artist->col_start > artist->col_end){
        temp = artist->col_start;
        artist->col_start = artist->col_end;
        artist->col_end = temp;
    }
}

void rearrange_point_diagonally(Canvas* artist){
    int temp_x, temp_y;
    if(artist->row_start > artist->row_end && artist->col_start > artist->col_end){ // SWAP!!
        temp_y = artist->row_start;
        temp_x = artist->col_start;
        artist->row_start = artist->row_end;
        artist->col_start = artist->col_end;
        artist->row_end = temp_y;
        artist->col_end = temp_x;
    }else if(artist->row_start < artist->row_end && artist->col_start > artist->col_end){ // SWAP!!
        temp_y = artist->row_start;
        temp_x = artist->col_start;
        artist->row_start = artist->row_end;
        artist->col_start = artist->col_end;
        artist->row_end = temp_y;
        artist->col_end = temp_x;
    }
}

void clean_up(Canvas* small_man){
    for (int i = 0; i < small_man->row; ++i) {
        free(small_man->the_canvas[i]);
    }
    free(small_man->the_canvas);
    small_man->the_canvas = NULL;
}
