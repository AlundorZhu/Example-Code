#ifndef INPUT_VALIDATION_H
#define INPUT_VALIDATION_H
#include <stdbool.h>

char* append_a_line (char* line, int* size_of_word, char a_character);
void read_and_create_space_for_a_line(char** output_line);
void command_line_validation(int argc, char** argv, Canvas* artist);
void print_error_message(int num);
bool command_validation(Canvas* artist);
bool command_boundary(Canvas artist);
bool straight_line(Canvas artist);
bool fail_to_open(Canvas* artist, char* file_name);

#endif
