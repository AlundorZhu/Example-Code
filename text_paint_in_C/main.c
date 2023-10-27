#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "canvas.h"
#include "command.h"
#include "input_validation.h"

int main(int argc, char** argv){
    Canvas artist;
    artist.command = '*';
    command_line_validation(argc, argv, &artist);

    do{
        print_matrix(artist);
        printf("Enter your command: ");
        if(command_validation(&artist)){
            command_directory(&artist);
        }else{
            continue;
        }
    }while(true);
    return -1;
}
