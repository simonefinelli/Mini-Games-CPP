#include "config.h"

#ifndef NUMBER_GUESSER_GUI_H
#define NUMBER_GUESSER_GUI_H

namespace gui {
    void show_title();

    void show_subtitle(int range_min = RANGE_MIN, int range_max = RANGE_MAX);

    void show_welcome();

    void show_greetings();

    void show_continue_game_message();

    void show_end_game_message(int secret_number);

    void show_feedback(int player_guess, int secret_number);

    void show_leave_message();

    void show_ongoing_bar(int guess_counter, int attempts);

    void show_insert_message();

    void show_warning_message();

    void draw_blank_line();

    void clear_board();
}

#endif //NUMBER_GUESSER_GUI_H
