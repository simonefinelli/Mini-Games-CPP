/**
 * @file curses_utils.h
 *
 * @author SimoX
 * @date 2023-09-09
 */

#include <ncurses.h>

#ifndef SPACEINVADERS_GUI_H
#define SPACEINVADERS_GUI_H

typedef enum InputMode {
    CANONICAL = 0,  // the terminal buffers input until a newline character ('\n') is received (when press enter)
    NON_CANONICAL  // (raw mode) the input is processed character by character, without buffering
} input_mode;

typedef struct ScreenXY {
    int x = 0;  // columns
    int y = 0;  // rows
} scr_xy;

namespace gui {
    // status
    void initialize_curses(bool show_user_input=false, input_mode mode=NON_CANONICAL, bool hide_cursor=true,
                           bool no_delay=true, bool enable_keypad=true);
    void shutdown_curses();

    // screen info
    scr_xy screen_size(WINDOW *win=stdscr);

    // screen manipulation
    void clear_screen();
    void refresh_screen();
    void draw_char(int x, int y, char c);
    void move_cursor(int x, int y);

    // user input
    int get_char();
}

#endif //SPACEINVADERS_GUI_H