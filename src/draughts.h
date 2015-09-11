/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2014 Assignment #1 
 * Full Name        : Stuart Parker
 * Student Number   : s3390317
 * Course Code      : COSC1076 - Advanced Programming Techniques
 * Program Code     : BP094 - Bachelor of Computer Science
 * Start up code provided by Paul Miller and Virginia King
 **********************************************************************/
#ifndef DRAUGHTS_H
#define DRAUGHTS_H

#include "game.h"

#define NUM_MENU_OPTS  4

void display_menu(char* options[], int num_options);
int get_valid_selection(char* options[]);
void prepare_game(char* player_one, char* player_two);

#endif
