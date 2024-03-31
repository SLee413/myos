/*
    Spencer Lee
*/

#ifndef MYOS_INCLUDE_CONSOLE_H

#define MYOS_INCLUDE_CONSOLE_H

    static const int VGA_WIDTH = 80;

    static const int VGA_HEIGHT = 25;

    static const int VGA_BYTES_PER_CHARACTER=2;

    void clear_terminal();

    void print_character(char c);

    void print_string(char* str);

    void print_line(char* str);

#endif