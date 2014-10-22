/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2014 Assignment #1 
 * Full Name        : Stuart Parker
 * Student Number   : s3390317
 * Course Code      : COSC1076 - Advanced Programming Techniques
 * Program Code     : BP094 - Bachelor of Computer Science
 * Start up code provided by Paul Miller and Virginia King
 **********************************************************************/
#ifndef GAME_H
#define GAME_H

#include "gameboard.h"
#include "scoreboard.h"

#define MOVE_LEN 8

struct location
{
    unsigned x; /* Column */
    unsigned y; /* Row */
};

struct move
{
    struct location start;
    struct location end;
};

enum colour
{
    P_RED, P_WHITE
};

struct player
{
    char name[MAX_NAME_LEN+1];
    enum colour col;
};

enum move_type
{
    ATTACK, NORMAL, INVALID
};

enum str_result
{
    FAILURE, SUCCESS, RTM
};

enum move_parse_result
{
    PARSE_FAILURE, PARSE_SUCCESS
};

/* Requirement 4 - Controls the flow of play in the game*/
void play_game(char* player_one, char* player_two, 
    struct result* outcome);

void randomly_assign_colours(struct player* white_player, 
    struct player* red_player, char* player_one, char* player_two);

/* Requirement 5 - Handles the logic for the player's turn*/
enum str_result player_turn(struct player* current, 
    enum cell_contents board[][BOARDHEIGHT]);

enum move_parse_result parse_move(char* input, struct move* current_move);

void process_move(struct move validated_move,
    enum cell_contents board[][BOARDHEIGHT]);

/* Requirement 6 - Tests to see whether a move is valid or not*/
enum move_type is_valid_move(struct move curr_move, struct player* 
    current, enum cell_contents board[][BOARDHEIGHT]);

BOOLEAN is_valid_step(struct move next_move,
    enum cell_contents board[][BOARDHEIGHT]);

BOOLEAN is_valid_jump(struct move next_move, enum colour player_colour,
    enum cell_contents board[][BOARDHEIGHT], unsigned* x_jumped,
    unsigned* y_jumped);

BOOLEAN is_valid_king_jump(struct move next_move, unsigned* x_jumped,
    unsigned* y_jumped);

BOOLEAN is_jump(struct move validated_move, enum colour player_colour, 
    enum cell_contents board[][BOARDHEIGHT], unsigned* x_jumped,
    unsigned* y_jumped);

/* Requirement 7 - Tests whether the next player has any valid moves */
BOOLEAN test_for_winner(struct player* next_player, 
    enum cell_contents board[][BOARDHEIGHT]);

#endif
