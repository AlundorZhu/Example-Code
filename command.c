#include <stdlib.h>
#include <stdio.h>
#include "canvas.h"
#include "command.h"


void print_help(){
    printf("Commands:\n");
    printf("Help: h\n");
    printf("Quit: q\n");
    printf("Draw line: w row_start col_start row_end col_end\n");
    printf("Resize: r num_rows num_cols\n");
    printf("Add row or column: a [r | c] pos\n");
    printf("Delete row or column: d [r | c] pos\n");
    printf("Erase: e row col\n");
    printf("Save: s file_name\n");
    printf("Load: l file_name\n");
}

void command_directory(Canvas* artist){
    switch(artist->command){
        case 'h':
            print_help();
            break;
        case 'q':
            quit(artist);
            break;
        case 'w':
            draw(artist);
            break;
        case 'r':
            resize(artist);
            break;
        case 'a':
            add(artist);
            break;
        case 'd':
            Delete(artist);
            break;
        case 'e':
            erase(artist);
            break;
        case 's':
            save(artist);
            break;
        case 'l':
            load(artist);
            break;
    default:
        printf("something wrong!!!\n");
        break;
    }
}

void draw(Canvas* artist){
    if(artist->row_start == artist->row_end){ // horizontal drawing, always drawing from left to right
        rearrange_point(artist);
        for(int i = artist->col_start; i <= artist->col_end; ++i){
            if(artist->the_canvas[artist->row_start][i] != '*' && artist->the_canvas[artist->row_start][i] != '-'){
                artist->the_canvas[artist->row_start][i] = '+';
            }else{
                artist->the_canvas[artist->row_start][i] = '-';
            }
        }
    }else if(artist->col_start == artist->col_end){ // vertical drawing, always drawing from top to bottom
        rearrange_point(artist);
        for(int k = artist->row_start; k <= artist->row_end; ++k){
            if(artist->the_canvas[k][artist->col_start] != '*' && artist->the_canvas[k][artist->col_start] != '|'){
                artist->the_canvas[k][artist->col_start] = '+';
            }else{
                artist->the_canvas[k][artist->col_start] = '|';
            }
        }
    }else if(abs(artist->row_end - artist->row_start) / abs(artist->col_end - artist->col_start) == 1){
        /*
        diagonally
        --------> work this way!!
        1 0 0 0 2
        0 1 0 2 0
        0 0 + 0 0
        0 2 0 1 0
        2 0 0 0 1
        */
        rearrange_point_diagonally(artist);
        int x, y;
        if(artist->row_start <= artist->row_end && artist->col_start <= artist->col_end){
            for(y = artist->row_start, x = artist->col_start; y <= artist->row_end && x <= artist->col_end; ++y, ++x){ // 1
                if(artist->the_canvas[y][x] != '*' && artist->the_canvas[y][x] != '/'){
                    artist->the_canvas[y][x] = '+';
                }else{
                    artist->the_canvas[y][x] = '/';
                }
            }
        }else{
            for(y = artist->row_start, x = artist->col_start; y >= artist->row_end && x <= artist->col_end; --y, ++x){ // 2
                if(artist->the_canvas[y][x] != '*' && artist->the_canvas[y][x] != '\\'){
                    artist->the_canvas[y][x] = '+';
                }else{
                    artist->the_canvas[y][x] = '\\';
                }
            }
        }
    }
}

void resize(Canvas* artist){
    int old_row = artist->row;
    int old_col = artist->col;
    int row_difference = abs(artist->new_size_row - artist->row);
    int col_difference = abs(artist->new_size_col - artist->col);
    artist->row = artist->new_size_row;
    artist->col = artist->new_size_col;
    if(artist->new_size_row > old_row){ // number of rows is enlarged, fill them up
		artist->the_canvas = (char**)realloc(artist->the_canvas, artist->new_size_row * sizeof(char*));
	    for(int i = 0; i < row_difference; ++i){ // enlarge the rows first, to initialize values
	        artist->the_canvas[old_row + i] = (char*)calloc(artist->new_size_col, sizeof(char));
	    }
        for(int z = 0; z < row_difference; ++z){
            for(int w = 0; w < artist->col; ++w){
                artist->the_canvas[old_row + z][w] = '*';
            }
        }
    }else{ // number of row decreased
		for(int i = 0; i < row_difference; ++i){
			free(artist->the_canvas[old_row - 1 - i]);
		}
		artist->the_canvas = (char**)realloc(artist->the_canvas, artist->new_size_row * sizeof(char*));
	}

    if(artist->new_size_col > old_col){ // second step, number of cols is enlarged, fill them up
		for(int i = 0; i < artist->new_size_row; ++i){
	        artist->the_canvas[i] = (char*)realloc(artist->the_canvas[i], artist->new_size_col * sizeof(char));
	    }
        for(int z = 0; z < col_difference; ++z){
            for(int w = 0; w < artist->row; ++w){
                artist->the_canvas[w][old_col + z] = '*';
            }
        }
    }else{ // number of cols is decreased
		for(int i = 0; i < artist->new_size_row; ++i){
	        artist->the_canvas[i] = (char*)realloc(artist->the_canvas[i], artist->new_size_col * sizeof(char));
	    }
	}
}

void erase(Canvas* artist){
    artist->the_canvas[artist->row_start][artist->col_start] = '*';
}

void add(Canvas* artist){
    if(artist->row_or_col == 'c'){
        ++artist->col;
        for(int i = 0; i < artist->row; ++i){
            artist->the_canvas[i] = (char*)realloc(artist->the_canvas[i], artist->col * sizeof(char));
			artist->the_canvas[i][artist->col - 1] = '*';
        } // making space for the new col
        if(artist->position != artist->col - 1){ // make sure not the right most colume
            for(int j = (artist->col - 1); j > artist->position; --j){ // start from the right most col
                for(int k = 0; k < artist->row; ++k){
                    artist->the_canvas[k][j] = artist->the_canvas[k][j - 1]; // move one colume to the right
                }
            }
        }
        for(int i = 0; i < artist->row; ++i){ // insert the col
            artist->the_canvas[i][artist->position] = '*';
        }
    }else{
        ++artist->row;
        artist->the_canvas = (char**)realloc(artist->the_canvas, artist->row * sizeof(char*));
        artist->the_canvas[artist->row - 1] = (char*)calloc(artist->col, sizeof(char)); // making space for new row, only one row
        if(artist->position != artist->row - 1){ // make sure not the bottom most row
            for(int j = (artist->row - 1); j > artist->position; --j){ // start from the bottom row
                for(int k = 0; k < artist->col; ++k){
                    artist->the_canvas[j][k] = artist->the_canvas[j - 1][k]; // move one row down
                }
            }
        }
        for(int i = 0; i < artist->col; ++i){ // insert the row
            artist->the_canvas[artist->position][i] = '*';
        }
    }
}

void Delete(Canvas* artist){
    if(artist->row_or_col == 'c'){
        if(artist->position != artist->col - 1){ // make sure not the right most colume
            for(int j = artist->position; j < (artist->col - 1); ++j){ // start from the position
                for(int k = 0; k < artist->row; ++k){
                    artist->the_canvas[k][j] = artist->the_canvas[k][j + 1]; // move one colume to the left
                }
            }
        }
        --artist->col;
        for(int i = 0; i < artist->row; ++i){
            artist->the_canvas[i] = (char*)realloc(artist->the_canvas[i], artist->col * sizeof(char));
        } // Delete space for the new col
    }else{
        if(artist->position != artist->row - 1){ // make sure not the bottom most row
            for(int j = artist->position; j < (artist->row - 1); ++j){ // start from the position
                for(int k = 0; k < artist->col; ++k){
                    artist->the_canvas[j][k] = artist->the_canvas[j + 1][k]; // move one row up
                }
            }
        }
        --artist->row;
		free(artist->the_canvas[artist->row]);
        artist->the_canvas = (char**)realloc(artist->the_canvas, artist->row * sizeof(char*)); // Delete one row
    }
}
void save(Canvas* artist){
    fprintf(artist->the_file, "%d %d\n", artist->row, artist->col); // save the dimension of the matrix
    for(int i = 0; i < artist->row; ++i){
        for(int j = 0; j < artist->col; ++j){
            if(artist->the_canvas[i][j] != '*'){
                fprintf(artist->the_file, "%d %d %c\n", i, j, artist->the_canvas[i][j]); // mark the coordinates of the painted place
            }
        }
    }
    fclose(artist->the_file);
}

void load(Canvas* artist){
    clean_up(artist);
    fscanf(artist->the_file, "%d %d\n", &artist->row, &artist->col);
    create_canvas(artist);
    while(!feof(artist->the_file)){
        fscanf(artist->the_file, "%d %d %c\n", &artist->marked_row, &artist->marked_col, &artist->mark);
        artist->the_canvas[artist->marked_row][artist->marked_col] = artist->mark;
    }
    fclose(artist->the_file);
}

void quit(Canvas* artist){
    clean_up(artist);
    exit(0);
}
