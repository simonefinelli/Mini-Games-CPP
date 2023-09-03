/**
 * @file gui.cpp
 * @brief
 *
 * @author SimoX
 * @date 2023-08-17
 */

#include <iostream>
#include <vector>
#include <thread>
#include "gui.h"
#include "player.h"
#include "ship.h"

using std::vector;

#define DESK_LENGTH 92
#define PLAYER_SPACE 39


void draw_title();
void draw_boards(const Player &p);
void draw_info_desk(const Player &p1, const Player &p2, player_turn turn);
void draw_board_line();
void draw_columns_title();
void draw_break_line();
void draw_ship_board_row(const vector<vector<ship_unit_area>> &ship_board, int r);
void draw_guess_board(const vector<vector<guess_unit_area>> &guess_board, int r);
void draw_space();
std::string get_column_title(int offset);
void draw_desk_line();
void draw_names(const std::string &p1_name, const std::string &p2_name,
                player_turn);
void draw_ships_status(const std::vector<Ship> &p1_ships,
                       const std::vector<Ship> &p2_ships);
void clear_board();


const std::string TITLE = R"(
                            ╔══╗       ╔╗  ╔╗ ╔╗         ╔╗
                            ║╔╗║      ╔╝╚╗╔╝╚╗║║         ║║
                            ║╚╝╚╗╔══╗ ╚╗╔╝╚╗╔╝║║ ╔══╗╔══╗║╚═╗╔╗╔══╗
                            ║╔═╗║╚ ╗║  ║║  ║║ ║║ ║╔╗║║══╣║╔╗║╠╣║╔╗║
                            ║╚═╝║║╚╝╚╗ ║╚╗ ║╚╗║╚╗║║═╣╠══║║║║║║║║╚╝║
                            ╚═══╝╚═══╝ ╚═╝ ╚═╝╚═╝╚══╝╚══╝╚╝╚╝╚╝║╔═╝
                                                               ║║
                                                               ╚╝
)";


void gui::draw_playing_field(const GameData &gd, player_turn t) {
    // clear the terminal
    clear_board();

    draw_title();

    // draw boards
    draw_boards(gd.player1);
    // draw_boards(gd.player2); // DEBUG

    // draw Players' info
    draw_info_desk(gd.player1, gd.player2, t);
}

void draw_title() {
    std::cout << TITLE << std::endl;
}

void draw_boards(const Player &p) {
    // draw fields' content
    draw_columns_title();
    draw_space();
    draw_columns_title();
    draw_break_line();
    draw_board_line();
    draw_space();
    draw_board_line();
    draw_break_line();
    for (int r = 0; r < FIELD_SIZE; r++) {
        draw_ship_board_row(p.ship_board, r);
        draw_space();
        draw_guess_board(p.guess_board, r);
        draw_break_line();
        draw_board_line();
        draw_space();
        draw_board_line();
        std::cout << std::endl;
    }
}

void draw_break_line() {
    std::cout << std::endl;
}

void draw_columns_title() {
    std::cout << "     1   2   3   4   5   6   7   8   9  10  ";
}

void draw_board_line() {
    std::cout << "   +---+---+---+---+---+---+---+---+---+---+";
}

void draw_ship_board_row(const vector<vector<ship_unit_area>> &ship_board, int r) {


    std::string render_row = get_column_title(r) + " |";

    if (r >= 0 && r < FIELD_SIZE) {
        const std::vector<ship_unit_area> &row = ship_board[r];
        for (auto u : row) {
            if (u.is_hit) {
                render_row += " X ";
                render_row += "|";
                continue;
            }
            switch (u.type) {
                case NO_TYPE:
                    render_row += "   ";
                    break;
                case AIRCRAFT_CARRIER:
                    render_row += " A ";
                    break;
                case BATTLESHIP:
                    render_row += " B ";
                    break;
                case CRUISER:
                    render_row += " C ";
                    break;
                case SUBMARINE:
                    render_row += " S ";
                    break;
                case DESTROYER:
                    render_row += " D ";
                    break;
            }
            render_row += "|";
        }
        std::cout << render_row;
    } else {
        throw std::runtime_error("Invalid row index!");
    }
}

void draw_guess_board(const vector<vector<guess_unit_area>> &guess_board, int r) {
    std::string render_row = get_column_title(r) + " |";

    if (r >= 0 && r < FIELD_SIZE) {
        const std::vector<guess_unit_area> &row = guess_board[r];
        for (auto u : row) {
            switch (u) {
                case UNEXPLORED:
                    render_row += "   ";
                    break;
                case MISSED:
                    render_row += " ~ ";
                    break;
                case HIT:
                    render_row += " X ";
                    break;
            }
            render_row += "|";
        }
        std::cout << render_row;
    } else {
        throw std::runtime_error("Invalid row index!");
    }
}

void draw_space() {
    std::cout << "     ";
}

std::string get_column_title(int offset) {
    int name = static_cast<int>('A') + offset;

    return " " + std::string{static_cast<char>(name)};
}

void draw_info_desk(const Player &p1, const Player &p2, player_turn turn) {
    draw_break_line();
    draw_names(p1.name, p2.name, turn);
    draw_ships_status(p1.ships, p2.ships);
    draw_desk_line();
    draw_break_line();
    std::cout << " -- " << ((turn == PLAYER_1) ? p1.name : p2.name)
              << " Turn -- \n\n";
}

void draw_desk_line() {
    int repeat = DESK_LENGTH;
    char c = '*';
    std::string line (repeat, c);
    std::cout << " " << line << std::endl;
}

void draw_names(const std::string &p1_name, const std::string &p2_name,
                player_turn turn) {
    // turn choice
    std::string p1_turn {};
    std::string p2_turn {};
    if (turn == PLAYER_1) {
        p1_turn = "[ * ]";
        p2_turn = "[   ]";
    } else {
        p1_turn = "[   ]";
        p2_turn = "[ * ]";
    }

    draw_desk_line();

    std::cout << " | ";

    // player 1
    int repeat = PLAYER_SPACE - static_cast<int>(p1_name.length()) -
            static_cast<int>(p1_turn.length()) - 1;
    char c = ' ';
    std::string space1 (repeat, c);
    std::cout << p1_name << " " << p1_turn << space1 << " |";

    // space
    std::cout << "      ";

    std::cout << "| ";
    // player 2
    repeat = PLAYER_SPACE - static_cast<int>(p2_name.length()) -
            static_cast<int>(p2_turn.length()) - 1;
    std::string space2 (repeat, c);
    std::cout << p2_name << " " << p2_turn << space2 << " |" << std::endl;

    draw_desk_line();
}

void draw_ships_status(const std::vector<Ship> &p1_ships,
                       const std::vector<Ship> &p2_ships) {

    for (int i = 0; i < SHIPS_NUMBER; i++) {
        std::string status_msg {};

        std::cout << " | ";
        // player 1
        std::string p1_ship_name = get_ship_name_length(p1_ships.at(i).type);
        if (p1_ships.at(i).status == ALIVE) {
            status_msg = "Alive";
        } else {
            status_msg = "Sunk";
        }
        int repeat = PLAYER_SPACE - static_cast<int>(status_msg.length()) -
                     static_cast<int>(p1_ship_name.length()) - 2;
        char c = ' ';
        std::string space1 (repeat, c);
        std::cout << p1_ship_name << ": " << status_msg << space1 << " |";

        // space
        std::cout << "      ";
        std::cout << "| ";

        // player 2
        std::string p2_ship_name = get_ship_name_length(p1_ships.at(i).type);
        if (p2_ships.at(i).status == ALIVE) {
            status_msg = "Alive";
        } else {
            status_msg = "Sunk";
        }
        repeat = PLAYER_SPACE - static_cast<int>(status_msg.length()) -
                     static_cast<int>(p2_ship_name.length()) - 2;
        c = ' ';
        std::string space2 (repeat, c);
        std::cout << p2_ship_name << ": " << status_msg << space2 << " |";

        draw_break_line();
    }
}

void gui::display_results(const GameData &gd, player_turn t) {
    std::string p_name = (t == PLAYER_1) ? gd.player1.name : gd.player2.name;

    std::cout << " > Congratulations " << p_name << ", you win!" << std::endl;
}

void gui::display_ai_message() {
    std::cout << " > I'm thinking ... " << std::flush;
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

void gui::display_enter_coords_message(ship_type type) {
    std::cout << " > Enter the coordinates for the " << get_ship_name(type)
              << ": ";
}

void gui::display_hit_message() {
    std::cout << " > Where do you want to hit? ";
}

void gui::display_checked_coords_message() {
    std::cout << " > Coordinates already checked!" << std::endl;
}

void gui::display_enter_orient_message(ship_type type) {
    std::cout << " > Enter the orientation for the " << get_ship_name(type)
              << ": ";
}

void gui::display_coords_not_valid_message() {
    std::cout << " > Coordinates not valid!" << std::endl;
}

void gui::display_orient_not_valid_message() {
    std::cout << " > Orientation not valid!" << std::endl;
}

void gui::display_invalid_placement_message(const std::string &msg) {
    std::cout << " > " << msg << std::endl;
}


/**
 * @brief Clears the terminal screen based on the Operating System.
 */
void clear_board() {
#ifdef _WIN32 // Windows
    system("cls");
#else // Unix-like systems (Linux, macOS, etc.)
    system("clear");
#endif
}
