/**
 * @file board.cpp
 * @brief
 *
 * @author SimoX
 * @date 2023-08-14
 */

#include "board.h"

/**
 * @brief Transforms a board raw in an integer.
 *
 * @param l Letter that indicates the row of the Board.
 * @return the relative numerical index.
 */
int row_to_number(char l) {
    switch (l) {
        case 'A':
            return 0;
        case 'B':
            return 1;
        case 'C':
            return 2;
        case 'D':
            return 3;
        case 'E':
            return 4;
        case 'F':
            return 5;
        case 'G':
            return 6;
        case 'H':
            return 7;
        case 'I':
            return 8;
        case 'J':
            return 9;
        default:
            return -1;
    }
}
