/*
    Spencer Lee
*/

#include "console.h"
#include "portmap.h"

static char* const VGA_BUFFER = (char*) 0xb8000;


/** Variables **/

// Cursor position
static int vga_cursor_pos_x = 0;
static int vga_cursor_pos_y = 0;

// VGA Color
static VGA_Color terminal_font_color = LIGHT_GRAY; // Default font color will be light gray
static VGA_Color terminal_background_color = BLACK; // Default background color is black


/** Functions **/


/* Validates and updates the cursor spot */
void update_cursor() {
    // If the cursor would go offscreen, then move down a line
    if (vga_cursor_pos_x >= VGA_WIDTH) {
        vga_cursor_pos_x = (vga_cursor_pos_x - VGA_WIDTH);  // For things of multple chars
        vga_cursor_pos_y++;     // Eventually we'll validate this and move everything up
    }

    // Calculate the cursor position
    uint16_t cursor_position = (vga_cursor_pos_y * VGA_WIDTH) + vga_cursor_pos_x;

    // Send the cursor to the keyboard
    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t) (cursor_position));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t) (cursor_position >> 8));
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
    vga_cursor_pos_x = 0;
    vga_cursor_pos_y = 0;
    update_cursor();
}

/* Print a character to the screen with a given background/font color */
void print_character_with_color(char c, VGA_Color bg_color, VGA_Color font_color) {

    // Character exceptions
    switch (c) {
        // Newline - jump us to next line
        case '\n':
            vga_cursor_pos_x = 0;
            vga_cursor_pos_y++;
            update_cursor();
            return;
        // Tab - jump us to the next multiple of 4
        case '\t':
            vga_cursor_pos_x += 4;
            vga_cursor_pos_x -= (vga_cursor_pos_x % 4); // lock to nearest multiple of 4
            update_cursor();
            return;
    }

    // Calculate the byte position
    int byte_pos = (vga_cursor_pos_y * VGA_BYTES_PER_CHARACTER * VGA_WIDTH) + 
        (VGA_BYTES_PER_CHARACTER * vga_cursor_pos_x);
    
    // Write to the VGA buffer
    VGA_BUFFER[byte_pos] = c;
    VGA_BUFFER[byte_pos + 1] = (bg_color << 4) | font_color;

    // Increment cursor
    vga_cursor_pos_x++;
    update_cursor();
}

/* Prints a string to the console with a given bg/font color */
void print_string_with_color(char* str, VGA_Color bg_color, VGA_Color font_color) {
    // Iterate through the string until you find a null character
    for (int i=0; str[i] != '\0'; i++) {
		print_character_with_color(str[i], bg_color, font_color);
	}
}

/* Prints a string and then a new line with a given bg/font color */
void print_line_with_color(char* str, VGA_Color bg_color, VGA_Color font_color) {
      print_string_with_color(str, bg_color, font_color);
      print_character_with_color('\n', bg_color, font_color);

}

/* Prints a character to the console */
void print_character(char c) {
     print_character_with_color(c, terminal_background_color, terminal_font_color);
}

/* Prints a string to the console */
void print_string(char* str) {
     print_string_with_color(str, terminal_background_color, terminal_font_color);
}

/* Prints a string then a new line to the console */
void print_line(char* str) {
     print_line_with_color(str, terminal_background_color, terminal_font_color);
}

/* Sets the terminal font color */
void set_terminal_font_color(VGA_Color col) {
     terminal_font_color = col;
}

/* Sets the terminal background color */
void set_terminal_background_color(VGA_Color col) {
     terminal_background_color = col;
}

