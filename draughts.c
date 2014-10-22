/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2014 Assignment #1
 * Full Name        : Stuart Parker
 * Student Number   : s3390317
 * Course Code      : COSC1076 - Advanced Programming Techniques
 * Program Code     : BP094 - Bachelor of Computer Science
 * Start up code provided by Paul Miller and Virginia King
 **********************************************************************/
#include "draughts.h"

int main(int argc, char* argv[])
{
    struct result scoreboard[SCOREBOARDSIZE];
    char* options[] = {"Play Game", "Display Winners", "Reset Scoreboard",
        "Quit"};
    int selection;
    struct result outcome;
    char player_one[MAX_NAME_LEN];
    char player_two[MAX_NAME_LEN];
    
    srand(time(NULL));
    
    init_scoreboard(scoreboard);
    
    do
    {
        display_menu(options, NUM_MENU_OPTS);
        selection = get_valid_selection(options);
        switch(selection)
        {
            case 1: /* Play Game */
                /* Blank outcome struct before beginning game to ensure strlen()
                 * check can be used to determine if the game was exited early */
                strcpy(outcome.won, "");
                strcpy(outcome.lost, "");
                
                prepare_game(player_one, player_two);
                play_game(player_one, player_two, &outcome);
                
                /* Only add game to scoreboard if the game ended with a winner */
                if(strlen(outcome.won) > 0 && strlen(outcome.lost) > 0)
                {
                    printf("\n%s has won!\n", outcome.won);
                    printf("Adding result to scoreboard...\n");
                    add_to_scoreboard(scoreboard, &outcome);
                }
                break;
            case 2: /* Display Winners */
                display_scoreboard(scoreboard);
                break;
            case 3: /* Reset Scoreboard */
                reset_scoreboard(scoreboard);
                printf("\nScoreboard reset...\n");
                break;
            case 4: /* Quit */
                printf("\nSystem exiting...\n");
                break;
        }
    } while(selection != 4);
    
    return EXIT_SUCCESS;
}

void display_menu(char* options[], int num_options)
{
    int i;
    
    print_multi('-', 28);
    printf("\nEnglish Draughts - Main Menu\n");
    print_multi('-', 28);
    printf("\n");
    /* Print menu options */
    for(i = 0; i < num_options; ++i)
    {
        printf("%d) %s\n", i+1, options[i]);
    }
}

int get_valid_selection(char* options[])
{
    int selection;
    enum int_result selection_result;
    BOOLEAN valid_option_selected = FALSE;
    
    while(!valid_option_selected)
    {
        printf("\nEnter selection: ");
        selection_result = get_int(&selection, MAX_INPUT_LEN, 1, NUM_MENU_OPTS);
        
        /* Test if input was a valid selection */
        if(selection_result == INT_SUCCESS)
        {
            valid_option_selected = TRUE;
        }
        else
        {
            printf("\nInvalid input\n\n");
            display_menu(options, NUM_MENU_OPTS);
        }
    }
    return selection;
}

/* Get the names for the players */
void prepare_game(char* player_one, char* player_two)
{
    char input[MAX_INPUT_LEN];
    enum input_result name_result;
    BOOLEAN player_one_name_valid = FALSE;
    BOOLEAN player_two_name_valid = FALSE;
    
    /* Get player ones name from user */
    while(!player_one_name_valid)
    {
        printf("\nEnter player ones name: ");
        name_result = get_input(input, MAX_NAME_LEN);
        if(name_result != INPUT_SUCCESS)
        {
            printf("Error reading name, please enter a name of at most ");
            printf("20 characters.\n");
        }
        else
        {
            strcpy(player_one, input);
            player_one_name_valid = TRUE;
        }
    }
    /* Get player twos name from user */
    while(!player_two_name_valid)
    {
        printf("Enter player twos name: ");
        name_result = get_input(input, MAX_NAME_LEN);
        if(name_result != INPUT_SUCCESS)
        {
            printf("Error reading name, please enter a name of at most ");
            printf("20 characters.\n");
        }
        else
        {
            strcpy(player_two, input);
            player_two_name_valid = TRUE;
        }
    }
    printf("\n");
}