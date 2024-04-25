/*
    Spencer Lee
*/

#ifndef MYOS_INCLUDE_KEYBOARD_H

#define MYOS_INCLUDE_KEYBOARD_H

#include "portmap.h"

static const char charmap[256] = {0,   0x1B, '1',  '2',  '3',  '4',  '5',  '6',
    '7',  '8',  '9',  '0',  '-',  '=',  '\b', '\t',
    'q',  'w',  'e',  'r',  't',  'y',  'u',  'i',
    'o',  'p',  '[',  ']',  '\n', 0,   'a',  's',
    'd',  'f',  'g',  'h',  'j',  'k',  'l',  ';',
    '\'', '`',  0,   '\\', 'z',  'x',  'c',  'v',
    'b',  'n',  'm',  ',',  '.',  '/',  0,   '*', 
    0,   ' ',  0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   '7',
    '8',  '9',  '-',  '4',  '5',  '6',  '+',  '1',
    '2',  '3',  '0',  '.',  0,   0,   0,   0
};

uint8_t scan(void);

#endif