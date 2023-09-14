/**
 * @file curses_gui.cpp
 *
 * @brief gui.cpp utilizes Curses library to draw objects and scenario on the
 * computer terminal.
 *
 * @author SimoX
 * @date 2023-08-14
 */

#include "gui.h"


/**
 * @brief Initializes the Curses library with optional configuration.
 *
 * Default inputs are useful when the game does not need to handle strings,
 * such as name entry or other text, but only needs to 'capture' inputs to
 * trigger events, like moving the player character.
 *
 * @param show_user_input Set to False to hide user input when typed - default is False.
 * @param mode Specify the input mode between CANONICAL and NON_CANONICAL - default is NON_CANONICAL.
 * @param hide_cursor Set to True to hide the cursor - default is True.
 * @param no_delay Set to True to periodically check for user input without blocking indefinitely - default is True.
 * @param enable_keypad Set to True to enable keypad behavior for special keys (like arrows) - default is True.
 */
void gui::initialize_curses(bool show_user_input, input_mode mode, bool hide_cursor, bool no_delay,
                            bool enable_keypad) {
    // initialize the terminal in Curses' mode
    initscr();
    // user input
    if (!show_user_input) noecho();
    // acquisition mode
    if (mode != CANONICAL) cbreak();
    // cursor behaviour
    curs_set(hide_cursor); // to hide the cursor
    // delay behaviour
    nodelay(stdscr, no_delay);
    // keypad behaviour
    keypad(stdscr, enable_keypad);
}

/**
 * @brief Closes safely and correctly the Curses library.
 *
 * This function must be called at the very end of the Game to close all properly.
 */
void gui::shutdown_curses() {
    endwin();
}

/**
 * @brief Retrieves the dimensions of the standard screen.
 *
 * In Curses library the screen is accessed be 'x' and 'y' coordinates, where\n
 * - initial point (0,0) is the top left corner of the screen;\n
 * - x coordinate is the width of the screen, i.e. columns;\n
 * - y coordinate is the height of the screen, i.e. lines.
 *
 *
 * @return a structure contains the Width (lines) and Height (cols) of the screen.
 */
scr_xy gui::screen_size(WINDOW *win) {
    int window_max_x;  // COLS
    int window_max_y;  // LINES
    getmaxyx(win, window_max_y, window_max_x);

    return {window_max_y, window_max_x};
}

/**
 * @brief Clears the standard screen.
 */
void gui::clear_screen() {
    clear();
}

/**
 * @brief Refreshes the standard screen.
 */
void gui::refresh_screen() {
    refresh();
}

/**
 * Draws a single character on standard screen in a specif position.
 *
 * @param x Column coordinate.
 * @param y Row coordinate.
 * @param c Single character.
 * @return True if the char can be draw, False otherwise (outside the margins).
 */
void gui::draw_char(int x, int y, char c) {
    mvaddch(y, x, c);
    return true;
}


void move_cursor(int x, int y) {
    move(y, x);
    return true;
}

/**
 * @brief Retrieves inputs from keyboard one character at a time and return
 * they as integers.
 *
 * @return single char user's input.
 */
int gui::get_char() {
    return getch();
}