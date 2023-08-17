/**
 * @file gui.cpp
 * @brief
 *
 * @author SimoX
 * @date 2023-08-17
 */

#include <iostream>
#include <vector>
#include "gui.h"

using std::vector;


void draw_board_line();
void draw_columns_title();
void draw_break_line();
void draw_ship_board_row(const vector<vector<ship_unit_area>> &ship_board, int r);
void draw_guess_board(const vector<vector<guess_unit_area>> &guess_board, int r);
void draw_space();

void draw_boards(const Player &p) {
    // draw_title();

    // Ship Board
    draw_columns_title();
    draw_space();
    // Guess Board
    draw_columns_title();
    draw_break_line();

    draw_board_line();
    draw_space();
    draw_board_line();
    draw_break_line();

    // draw playing field row by row
    for (int r = 0; r < FIELD_SIZE; r++) {
        // draw field's content
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
    std::cout << "  1   2   3   4   5   6   7   8   9  10  ";
}

void draw_board_line() {
    std::cout << "+---+---+---+---+---+---+---+---+---+---+";
//    std::cout << "| A | A | A | A                         |" << std::endl;
}

void draw_ship_board_row(const vector<vector<ship_unit_area>> &ship_board, int r) {
    std::string render_row = "|";

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
    std::string render_row = "|";

    if (r >= 0 && r < FIELD_SIZE) {
        const std::vector<guess_unit_area> &row = guess_board[r];
        for (auto u : row) {
            switch (u) {
                case UNEXPLORED:
                    render_row += "   ";
                    break;
                case MISSED:
                    render_row += " O ";
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

void draw_players_desk() {
    // TODO
}

void draw_space() {
    std::cout << "     ";
}