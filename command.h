#ifndef COMMAND_H
#define COMMAND_H

void print_help();
void draw(Canvas* artist);
void resize(Canvas* artist);
void erase(Canvas* artist);
void add(Canvas* artist);
void Delete(Canvas* artist);
void save(Canvas* artist);
void load(Canvas* artist);
void command_directory(Canvas* artist);
void quit(Canvas* artist);

#endif