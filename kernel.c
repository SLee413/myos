/*
	Spencer Lee
*/

#include "console.h"

void main() {

     clear_terminal();

     print_string_with_color("hello", YELLOW, CYAN);

     print_line_with_color("World", MAGENTA, GREEN);

     print_string("Today");

     return;

}

