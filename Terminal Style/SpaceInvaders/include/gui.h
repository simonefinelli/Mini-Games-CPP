/**
 * @file gui.h
 * @brief Wrapper for Curses library.
 * @author SimoX
 * @date 2023-09-09
 */



#ifndef SPACEINVADERS_GUI_H
#define SPACEINVADERS_GUI_H

#include <array>
#include <ncurses.h>
#include "common.h"

#define HER0_MOVEMENT_OFFSET 1

typedef enum InputMode {
    CANONICAL = 0,  // the terminal buffers input until a newline character ('\n') is received (when press enter)
    NON_CANONICAL  // (raw mode) the input is processed character by character, without buffering
} input_mode;

typedef struct ScreenXY {
    int x = 0;  // columns
    int y = 0;  // rows
} scr_xy;

typedef enum GameKeys {
    LEFT = KEY_LEFT,
    RIGHT = KEY_RIGHT,
    SPACE = ' '
} key;

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
    /**
     * @brief Draws on the ncurses terminal a generic sprite.
     *
     * @param x X coordinate (columns).
     * @param y Y coordinate (rows).
     * @param s Sprite to draw.
     */
    template <typename T, size_t N>
    void draw_sprite(int x, int y, const std::array<T, N> &s) {
        int height_offset = 0;
        for (const auto &sprite_part : s) {
            mvprintw(y + height_offset, x, "%s", sprite_part.c_str());
            height_offset++;
        }
    }

    // user input
    int get_char();
}

#endif //SPACEINVADERS_GUI_H
