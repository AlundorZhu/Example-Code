#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "canvas.h"
#include "input_validation.h"

void command_line_validation(int argc, char** argv, Canvas* artist){
    if(argc == 3){
        int rows_read = sscanf(argv[1], "%d", &artist->row);
        int cols_read = sscanf(argv[2], "%d", &artist->col);
        if(rows_read != 1){
            printf("The number of rows is not an integer.\n");
	        printf("Making default board of 10 X 10.\n");
	        artist->row = 10;
	        artist->col = 10;
        }else if(artist->row < 1){
            printf("The number of rows is less than 1.\n");
	        printf("Making default board of 10 X 10.\n");
	        artist->row = 10;
	        artist->col = 10;
        }else if(cols_read != 1){
            printf("The number of columns is not an integer.\n");
	        printf("Making default board of 10 X 10.\n");
	        artist->row = 10;
	        artist->col = 10;
        }else if(artist->col < 1){
            printf("The number of columns is less than 1.\n");
	        printf("Making default board of 10 X 10.\n");
	        artist->row = 10;
	        artist->col = 10;
        }
        create_canvas(artist);
    }else if(argc == 1){
      artist->row = 10;
      artist->col = 10;
      create_canvas(artist);
    }else{ //default scenraio
        printf("Wrong number of command line arguements entered.\n");
        printf("Usage: ./paint.out [num_rows num_cols]\n");
        printf("Making default board of 10 X 10.\n");
        artist->row = 10;
        artist->col = 10;
        create_canvas(artist);
    }
}

void print_error_message(int num){
    switch(num){
    case 1:
    printf("Improper draw command.\n");
    break;
    case 2:
    printf("Improper resize command.\n");
    break;
    case 3:
    printf("Improper erase command.\n");
    break;
    case 4:
    printf("Improper add command.\n");
    break;
    case 5:
    printf("Improper delete command.\n");
    break;
    case 6:
    printf("Improper save command or file could not be created.\n");
    break;
    case 7:
    printf("Improper load command or file could not be opened.\n");
	break;
    }
}

char* append_a_line(char* line, int* size_of_word, char a_character){
    (*size_of_word)++;
    line = (char*)realloc(line, *size_of_word * sizeof(char));
    line[*size_of_word - 1] = a_character;
    return line;
}

void read_and_create_space_for_a_line(char** output_line){
    char a_character;
    *output_line = NULL;
    int size_of_word = 0;
    do {
       scanf("%c", &a_character);
       *output_line = append_a_line(*output_line, &size_of_word, a_character);
    } while (!(a_character == '\n'));
    *output_line = append_a_line(*output_line, &size_of_word, '\0');
}

bool command_validation(Canvas* artist){
    int num_args_read = 0;
    char* input_line = NULL;
    char extra_arg;
    scanf("%c", &artist->command);
    read_and_create_space_for_a_line(&input_line);
    if(artist->command == 'w'){
        num_args_read = sscanf(input_line,"%d %d %d %d %c", &artist->row_start, &artist->col_start, &artist->row_end, &artist->col_end, &extra_arg);
        free(input_line);
        if(num_args_read != 4 || !command_boundary(*artist)){
            print_error_message(1);
            return false;
        }else if(!straight_line(*artist)){
            printf("Cannot draw the line as it is not straight.\n");
            return false;
        }
        return true;
    }else if(artist->command == 'e'){
        num_args_read = sscanf(input_line,"%d %d %c", &artist->row_start, &artist->col_start, &extra_arg);
        free(input_line);
        if(num_args_read != 2 || !command_boundary(*artist)){
            print_error_message(3);
            return false;
        }
        return true;
    }else if(artist->command == 'q' || artist->command == 'h'){
        num_args_read = strcmp(input_line, "\n");
        free(input_line);
        if(num_args_read != 0){
            printf("Unrecognized command. Type h for help.\n");
            return false;
        }
        return true;
    }else if(artist->command == 'r'){
        num_args_read = sscanf(input_line, "%d %d %c", &artist->new_size_row, &artist->new_size_col, &extra_arg);
        free(input_line);
        if(num_args_read != 2 || artist->new_size_row < 1 || artist->new_size_col < 1){
            print_error_message(2);
            return false;
        }
        return true;
    }else if(artist->command == 'a' || artist->command == 'd'){
        num_args_read = sscanf(input_line, " %c %d %c", &artist->row_or_col, &artist->position, &extra_arg);
        free(input_line);
        if(num_args_read != 2 || !command_boundary(*artist) || (artist->row_or_col != 'r' && artist->row_or_col != 'c')){
            if(artist->command == 'a'){
                print_error_message(4);
            }else{
                print_error_message(5);
            }
            return false;
        }
        return true;
    }else if(artist->command == 's' || artist->command == 'l'){
        if(strcmp(input_line, "\n") == 0){
            if(artist->command == 's'){
                print_error_message(6);
            }else{
                print_error_message(7);
            }
            return false;
        }else if(fail_to_open(artist, input_line)){
			printf("Failed to open file:%s", input_line);
			return false;
		}
        free(input_line);
        return true;
    }
    free(input_line);
    printf("Unrecognized command. Type h for help.\n");
    return false;
}

bool fail_to_open(Canvas* artist, char* file_name){
	if(artist->command == 's'){
		artist->the_file = fopen(file_name, "w");
		if(artist->the_file == NULL){
			return true;
		}
		return false;
	}
	artist->the_file = fopen(file_name, "r");
	if(artist->the_file == NULL){
		return true;
	}
	return false;
}

bool command_boundary(Canvas artist){
    if(artist.command == 'w'){
        if(artist.row_start >= artist.row || artist.col_start >= artist.col  || artist.row_end >= artist.row || artist.col_end >= artist.col || artist.row_start < 0 || artist.col_start < 0 || artist.row_end < 0 || artist.col_end < 0){
            return false;
        }
        return true;
    }else if(artist.command == 'e'){
        if(artist.row_start >= artist.row || artist.col_start >= artist.col || artist.row_end >= artist.row || artist.col_end >= artist.col || artist.row_start < 0 || artist.col_start < 0 || artist.row_end < 0 || artist.col_end < 0){
            return false;
        }
        return true;
    }else if(artist.command == 'a'){
        if((artist.row_or_col == 'r' && artist.position > artist.row) || (artist.row_or_col == 'c' && artist.position > artist.col) || artist.position < 0){
            return false;
        }
        return true;
    }else if(artist.command == 'd'){
        if((artist.row_or_col == 'r' && artist.position >= artist.row) || (artist.row_or_col == 'c' && artist.position >= artist.col) || artist.position < 0){
            return false;
        }
        return true;
    }
    return true;
}

bool straight_line(Canvas artist){
    if(artist.row_start == artist.row_end || artist.col_start == artist.col_end){
        return true;
    }else if(abs(artist.row_end - artist.row_start) / abs(artist.col_end - artist.col_start) == 1){
        return true;
    }
    return false;
}
