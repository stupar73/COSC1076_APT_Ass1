/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2014 Assignment #1 
 * Full Name        : Stuart Parker
 * Student Number   : s3390317
 * Course Code      : COSC1076 - Advanced Programming Techniques
 * Program Code     : BP094 - Bachelor of Computer Science
 * Start up code provided by Paul Miller and Virginia King
 **********************************************************************/
#include "gameboard.h"

/* Copies the master board to a local copy for each game */
void init_gameboard(enum cell_contents board[][BOARDHEIGHT])
{
    int x, y;
    
    /* Copy from master board constant to local board */
    for(y = 0; y < BOARDWIDTH; ++y)
    {
        for(x = 0; x < BOARDHEIGHT; ++x)
        {
            board[y][x] = master_board[y][x];
        }
    }
}

/* Prints the game board to the screen */
void display_gameboard(enum cell_contents board[][BOARDHEIGHT])
{
    int i;
    
    /* Print column headers */
    printf("     |");
    for(i = 0; i < BOARDWIDTH; ++i)
    {
        printf("  %d  |", i);
    }
    printf("\n");
    /* Print first separator */
    print_multi('-', 54);
    printf("\n");
    
    /* Print each row */
    for(i = 0; i < BOARDHEIGHT; ++i)
    {
        print_row(i, board);
        printf("\n");
        print_multi('-', 54);
        printf("\n");
    }
    printf("\n");
}

void print_row(int row, enum cell_contents board[][BOARDHEIGHT])
{
    int i;
    char piece[PIECE_LEN];
    
    printf("  %d  |", row);
    
    for(i = 0; i < BOARDWIDTH; ++i)
    {
        switch(board[row][i])
        {
            case EMPTY:
                strcpy(piece, " ");
                break;
            case RED:
                strcpy(piece, RED_DISPLAY);
                strcat(piece, WHITE_RESET);
                break;
            case WHITE:
                strcpy(piece, WHITE_DISPLAY);
                break;
            case K_RED:
                strcpy(piece, RED_KING_DISPLAY);
                strcat(piece, WHITE_RESET);
                break;
            case K_WHITE:
                strcpy(piece, WHITE_KING_DISPLAY);
                break;
        }
        printf("  %s  |", piece);
    }
}