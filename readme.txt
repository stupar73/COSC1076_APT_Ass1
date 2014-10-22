/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2014 Assignment #1 
 * Full Name        : Stuart Parker
 * Student Number   : s3390317
 * Course Code      : COSC1076 - Advanced Programming Techniques
 * Program Code     : BP094 - Bachelor of Computer Science
 * Start up code provided by Paul Miller and Virginia King
 **********************************************************************/

 /* This file is for you to provide any extra information that your 
 markers may find useful. For example. Bugs, inconsistencies, incomplete
 functionality, reasoning for design choices etc. */

utility.c:29 - Inspiration for get_input() taken from function examples provided
    on blackboard.
utility.c:60 - Inspiration for get_int() taken from function examples provided
    on blackboard.
game.c:17 - red_player and white_player used instead of playerone and playertwo
    for player structs to allow for easier managing of which colours turn it is
    (rather than multiple if statements)
game.c:229 - sscanf() safe to use here, since user input has already been safely
    read and if the user enters anything other than 4 unsigned ints in the
    correct format it will not act on those values entered.
game.c:529 - When checking moves it is assumed that the piece could be a king
    without checking. This reduces the size of the loop but has no effect
    on the outcome since if the piece is not a king is_valid_move() will
    return FALSE.
    Player colour is ignored when checking moves in this function, since
    is_valid_move() will return INVALID if the piece attempting to be moved is
    not the player's piece.