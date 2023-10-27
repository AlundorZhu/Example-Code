#ifndef CANVAS_H
#define CANVAS_H

typedef struct Canvas_struct{
    int row;
    int col;
    char command;
    int row_start;
    int col_start;// for Write/erase
    int row_end;
    int col_end; // for Write command
    int new_size_row;
    int new_size_col; // for resize command
    char row_or_col;
    int position; // for add/delete command
    int marked_row;
    int marked_col;
    char mark;
    FILE* the_file; // for s/l command
    char** the_canvas;
}Canvas;

void create_canvas(Canvas* small_man);
void print_matrix (Canvas BIG_man);
void clean_up(Canvas* small_man);
void rearrange_point_diagonally(Canvas* artist);
void rearrange_point(Canvas* artist);

#endif
