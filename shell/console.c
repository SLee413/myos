/*
    Spencer Lee
*/

#include "console.h"

static char* const VGA_BUFFER = (char*) 0xb8000;

/* Variables */

// Cursor position
int cursor_pos_x = 0;
int cursor_pos_y = 0;

/* Validates the cursor spot */
void validate_cursor() {
    // If the cursor would go offscreen, then move down a line
    if (cursor_pos_x >= VGA_WIDTH) {
        cursor_pos_x = (cursor_pos_x - VGA_WIDTH);  // For things of multple chars
        cursor_pos_y++;     // Eventually we'll validate this and move everything up
    }
}

/* Clears the terminal screen */
void clear_terminal() {
	// iterate through x
	for (int x=0; x < VGA_WIDTH; x++) {
		// iterate through y
		for (int y=0; y < VGA_HEIGHT; y++) {
			// Write null char, then default style
            int pos = (y * VGA_BYTES_PER_CHARACTER * VGA_WIDTH) + 
                (VGA_BYTES_PER_CHARACTER * x);
			VGA_BUFFER[pos] = 0x00;
			VGA_BUFFER[pos + 1] = 0x07;
		}
	}

    // Reset the cursor position
    cursor_pos_x = 0;
    cursor_pos_y = 0;
}

/* Print a character to the screen */
void print_character(char c) {

    // Character exceptions
    /* 
        While in a perfect world we don't print any of the functional
        characters, I feel it's disingenuous to not print something
        that is not rendering.

        Also, I'm not sure if you required this, but if so, can you
        just list which ones you want me to actually make work? I only
        use tab and newline, the others I don't tend to use, so I left them
        as is (so they render *something*)
    */
    switch (c) {
        // Newline - jump us to next line
        case '\n':
            cursor_pos_x = 0;
            cursor_pos_y++;
            validate_cursor();
            return;
        // Tab - we're just going to stick with 4 spaces, but
        //     tabs are usually smarter than that
        case '\t':
            cursor_pos_x += 4;
            validate_cursor();
            return;
    }

    // Calculate the byte position
    int byte_pos = (cursor_pos_y * VGA_BYTES_PER_CHARACTER * VGA_WIDTH) + 
        (VGA_BYTES_PER_CHARACTER * cursor_pos_x);
    
    // Write to the VGA buffer
    VGA_BUFFER[byte_pos] = c;
    VGA_BUFFER[byte_pos + 1] = 0x07;

    // Increment cursor
    cursor_pos_x++;
    validate_cursor();
}

/* Prints a string to the console */
void print_string(char* str) {
    // Iterate through the string until you find a null character
    for (int i=0; str[i] != '\0'; i++) {
		print_character(str[i]);
	}
}

/* Prints a string then a new line to the console */
void print_line(char* str) {
    // The quick n' ez way of doing things!
    print_string(str);
    print_character('\n');
}

