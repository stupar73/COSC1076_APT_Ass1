/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2014 Assignment #1 
 * Full Name        : Stuart Parker
 * Student Number   : s3390317
 * Course Code      : COSC1076 - Advanced Programming Techniques
 * Program Code     : BP094 - Bachelor of Computer Science
 * Start up code provided by Paul Miller and Virginia King
 **********************************************************************/

#include "scoreboard.h"

/* Req 2 - Initialises the scoreboard and sets all the strings to be 
 * empty*/
void init_scoreboard(struct result* scoreboard)
{
    int i;
    /* Blank out memory for result struct of size SCOREBOARDSIZE */
    for(i = 0; i < SCOREBOARDSIZE; ++i)
    {
        strcpy(scoreboard[i].won, "");
        strcpy(scoreboard[i].lost, "");
    }
}

/* Req 9 - Adds a result to the beginning of the scoreboard*/
void add_to_scoreboard(struct result* scoreboard, 
    struct result* latest_game)
{
    int i;
    
    /* Copy each entry in scoreboard down one position */
    for(i = SCOREBOARDSIZE - 1; i > 0; --i)
    {
        memcpy(&scoreboard[i], &scoreboard[i-1], sizeof(struct result));
    }
    /* Copy latest game to first position in scoreboard array */
    memcpy(&scoreboard[0], latest_game, sizeof(struct result));
}

/* Req 11 - Initialises the scoreboard and sets all the strings to be 
 * empty*/
void reset_scoreboard(struct result* scoreboard)
{
    /* reset_scoreboard is functionally equivalent to init_scoreboard */
    init_scoreboard(scoreboard);
}

/* Req 10 - Displays a formatted printout of the last 10 winners and 
 * losers*/
void display_scoreboard(struct result* scoreboard)
{
    int i;
    if(strlen(scoreboard[0].won) == 0)
    {
        printf("\nNo games have been played...\n");
        return;
    }
    printf("APT English Draughts Tournament - History of Games Played\n");
    print_multi('=', 57);
    printf("\n");
    printf("| %-*s", MAX_NAME_LEN, "Winner");
    printf("| %-*s|\n", MAX_NAME_LEN, "Loser");
    printf("| ");
    print_multi('-', 20);
    printf("| ");
    print_multi('-', 20);
    printf("|\n");
    
    /* Print each games winner and loser */
    for(i = 0; i < SCOREBOARDSIZE; ++i)
    {
        if(strlen(scoreboard[i].won) == 0)
        {
            break;
        }
        printf("| %-*s", MAX_NAME_LEN, scoreboard[i].won);
        printf("| %-*s|", MAX_NAME_LEN, scoreboard[i].lost);
        printf("\n");
    }
    printf("\n");
}

