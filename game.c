/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2014 Assignment #1 
 * Full Name        : Stuart Parker
 * Student Number   : s3390317
 * Course Code      : COSC1076 - Advanced Programming Techniques
 * Program Code     : BP094 - Bachelor of Computer Science
 * Start up code provided by Paul Miller and Virginia King
 **********************************************************************/
#include "game.h"

/* Requirement 4 - Controls the flow of play in the game */
void play_game(char* player_one, char* player_two, 
    struct result* outcome)
{
    enum cell_contents board[BOARDWIDTH][BOARDHEIGHT];
    struct player red_player;
    struct player white_player;
    enum str_result red_turn;
    enum str_result white_turn;
    BOOLEAN game_quit = FALSE;
    BOOLEAN game_won = FALSE;
    
    init_gameboard(board);
    
    red_player.col = P_RED;
    white_player.col = P_WHITE;
    randomly_assign_colours(&red_player, &white_player, player_one, player_two);
    
    printf("%s is red.\n", red_player.name);
    printf("%s is white.\n\n", white_player.name);
    
    while(!game_quit && !game_won)
    {
        display_gameboard(board);
        
        /* Check if the red player has any moves, if no the white player wins */
        if(!test_for_winner(&red_player, board))
        {
            game_won = TRUE;
            strcpy(outcome->won, white_player.name);
            strcpy(outcome->lost, red_player.name);
            break;
        }
        
        red_turn = player_turn(&red_player, board);
        if(red_turn == RTM)
        {
            game_quit = TRUE;
            break;
        }
        
        display_gameboard(board);
        
        /* Check if the white player has any moves, if no the red player wins */
        if(!test_for_winner(&white_player, board))
        {
            game_won = TRUE;
            strcpy(outcome->won, red_player.name);
            strcpy(outcome->lost, white_player.name);
            break;
        }
        
        white_turn = player_turn(&white_player, board);
        if(white_turn == RTM)
        {
            game_quit = TRUE;
            break;
        }
    }
}

/* Randomly assigns red or white to each player */
void randomly_assign_colours(struct player* white_player, 
    struct player* red_player, char* player_one, char* player_two)
{
    int random_num;
    
    random_num = rand()%100;
     
    if(random_num < 50)
    {
        strcpy(red_player->name, player_one);
        strcpy(white_player->name, player_two);
    }
    else
    {
        strcpy(red_player->name, player_two);
        strcpy(white_player->name, player_one);
    }
}

/* Requirement 5 - Handles the logic for the player's turn*/
enum str_result player_turn(struct player* current, 
    enum cell_contents board[][BOARDHEIGHT])
{
    enum str_result player_action = FAILURE;
    char input[MAX_INPUT_LEN];
    enum input_result turn_result;
    enum move_parse_result parse_result;
    struct move current_move;
    struct location attacking_piece;
    enum move_type current_move_type;
    enum input_result attack_again_result;
    BOOLEAN turn_finished = FALSE;
    BOOLEAN attack_again = FALSE;
    BOOLEAN attack_again_answered;
    
    while(!turn_finished)
    {
        printf("It is %s's turn. Please enter a move ", current->name);
        printf("[press enter or ctrl-D to quit the current game]: ");
        turn_result = get_input(input, MAX_INPUT_LEN);
        if(turn_result == INPUT_SUCCESS)
        {
            /* Allow player to change their mind after opting to attack again */
            if(attack_again && strcmp(input, "n") == 0)
            {
                player_action = SUCCESS;
                turn_finished = TRUE;
                break;
            }
            parse_result = parse_move(input, &current_move);
            if(parse_result == PARSE_SUCCESS)
            {
                current_move_type = is_valid_move(current_move, current, board);
                if(current_move_type == ATTACK)
                {
                    if((attack_again && 
                        current_move.start.x == attacking_piece.x &&
                        current_move.start.y == attacking_piece.y) ||
                       !attack_again)
                    {
                        process_move(current_move, board);
                        display_gameboard(board);
                        attack_again_answered = FALSE;
                        while(!attack_again_answered)
                        {
                            printf("You attacked! Would you like to attempt ");
                            printf("a further attack move with this token? ");
                            printf("[y for yes, n for no, or press enter or ");
                            printf("ctrl-D to quit the current game]: ");
                            attack_again_result = get_input(input, MAX_INPUT_LEN);
                            
                            if(attack_again_result == INPUT_SUCCESS)
                            {
                                if(strcmp(input, "y") == 0)
                                {
                                    attack_again = TRUE;
                                    attack_again_answered = TRUE;
                                    attacking_piece = current_move.end;
                                    printf("You chose to attack again! Please ");
                                    printf("note to change your mind simply ");
                                    printf("enter n instead of a move.\n\n");
                                }
                                else if(strcmp(input, "n") == 0)
                                {
                                    attack_again = FALSE;
                                    attack_again_answered = TRUE;
                                    player_action = SUCCESS;
                                    turn_finished = TRUE;
                                }
                                else
                                {
                                    printf("Invalid input, please enter y or ");
                                    printf("n.\n\n");
                                }
                            }
                            else if(attack_again_result == INPUT_EMPTY)
                            {
                                attack_again_answered = TRUE;
                                player_action = RTM;
                                turn_finished = TRUE;
                            }
                            else
                            {
                                printf("Invalid input, please try again.\n\n");
                            }
                        }
                    }
                    else
                    {
                        printf("Invalid move, please try again.\n\n");
                    }
                }
                else if(current_move_type == NORMAL && !attack_again)
                {
                    
                    process_move(current_move, board);
                    player_action = SUCCESS;
                    turn_finished = TRUE;
                }
                else
                {
                    printf("Invalid move, please try again.\n\n");
                }
            }
            else
            {
                printf("Invalid move format, please try again.\n\n");
            }
        }
        else if(turn_result == INPUT_EMPTY)
        {
            player_action = RTM;
            turn_finished = TRUE;
        }
        else
        {
            printf("Invalid input, please try again.\n\n");
        }
    }
    return player_action;
}

enum move_parse_result parse_move(char* input, struct move* current_move)
{
    unsigned x_start, y_start, x_end, y_end;
    
    /* Check that 4 unsigned ints were input by the user in the correct format */
    if(sscanf(input, "%u,%u-%u,%u", &x_start, &y_start, &x_end, &y_end) == 4)
    {
        current_move->start.x = x_start;
        current_move->start.y = y_start;
        current_move->end.x = x_end;
        current_move->end.y = y_end;
        return PARSE_SUCCESS;
    }
    else
    {
        return PARSE_FAILURE;
    }
}

void process_move(struct move validated_move,
    enum cell_contents board[][BOARDHEIGHT])
{
    unsigned x_start = validated_move.start.x;
    unsigned y_start = validated_move.start.y;
    unsigned x_end = validated_move.end.x;
    unsigned y_end = validated_move.end.y;
    unsigned x_jumped, y_jumped;
    enum colour player_colour;
    
    if(board[y_start][x_start] == RED || board[y_start][x_start] == K_RED)
    {
        player_colour = P_RED;
    }
    else
    {
        player_colour = P_WHITE;
    }
    
    if(is_jump(validated_move, player_colour, board, &x_jumped, &y_jumped))
    {
        /* Perform jump */
        board[y_jumped][x_jumped] = EMPTY;
    }
    
    /* Move piece */
    board[y_end][x_end] = board[y_start][x_start];
    board[y_start][x_start] = EMPTY;
    
    /* If a regular piece has reached the end of the board, turn into a king */
    if(board[y_end][x_end] == RED && y_end + 1 == BOARDHEIGHT)
    {
        board[y_end][x_end] = K_RED;
    }
    else if(board[y_end][x_end] == WHITE && y_end == 0)
    {
        board[y_end][x_end] = K_WHITE;
    }
}

/* Requirement 6 - Tests to see whether a move is valid or not*/
enum move_type is_valid_move(struct move next_move, 
    struct player* current, enum cell_contents board[][BOARDHEIGHT])
{
    unsigned x_start = next_move.start.x;
    unsigned y_start = next_move.start.y;
    unsigned x_end = next_move.end.x;
    unsigned y_end = next_move.end.y;
    unsigned x_jumped, y_jumped;
    enum colour player_colour = current->col;
    
    /* Beginning or end location out of bounds */
    if(x_start >= BOARDWIDTH ||
       y_start >= BOARDHEIGHT ||
       x_end >= BOARDWIDTH ||
       y_end >= BOARDHEIGHT ||
       x_start < 0 ||
       y_start < 0 ||
       x_end < 0 ||
       y_end < 0)
    {
        return INVALID;
    }
    
    /* Start location does not contain a piece of the players colour */
    if(player_colour == P_RED)
    {
        if((board[y_start][x_start] != RED) &&
           (board[y_start][x_start] != K_RED))
        {
            return INVALID;
        }
    }
    if(player_colour == P_WHITE)
    {
        if((board[y_start][x_start] != WHITE) &&
           (board[y_start][x_start] != K_WHITE))
        {
            return INVALID;
        }
    }
    
    /* End location not empty */
    if(board[y_end][x_end] != EMPTY)
    {
        return INVALID;
    }
    /* Move is a legal jump or legal step */
    if(is_valid_step(next_move, board))
    {
        return NORMAL;
    }
    else if(is_valid_jump(next_move, player_colour, board, &x_jumped, &y_jumped))
    {
        return ATTACK;
    }
    else
    {
        return INVALID;
    }
}

BOOLEAN is_valid_step(struct move next_move,
    enum cell_contents board[][BOARDHEIGHT])
{
    unsigned x_start = next_move.start.x;
    unsigned y_start = next_move.start.y;
    unsigned x_end = next_move.end.x;
    unsigned y_end = next_move.end.y;
    
    /* Know that: - end location is empty and within bounds
                  - piece being moved is the players piece */
    
    /* Regular piece not being moved one square diagonally forward */
    if(board[y_start][x_start] == RED)
    {
        if((abs_diff(x_start, x_end) != 1) ||
           (y_end - y_start != 1))
        {
            return FALSE;
        }
    }
    if(board[y_start][x_start] == WHITE)
    {
        if((abs_diff(x_start, x_end) != 1) ||
           (y_start - y_end != 1))
        {
            return FALSE;
        }
    }
    
    /* King piece not being moved diagonally forward or backward */
    if(board[y_start][x_start] == K_WHITE ||
       board[y_start][x_start] == K_RED)
    {
        if(!(((x_end == x_start - 1) && (y_end == y_start + 1)) ||
             ((x_end == x_start - 1) && (y_end == y_start - 1)) ||
             ((x_end == x_start + 1) && (y_end == y_start + 1)) ||
             ((x_end == x_start + 1) && (y_end == y_start - 1))))
        {
            return FALSE;
        }
    }
    
    return TRUE;
}

BOOLEAN is_valid_jump(struct move next_move, enum colour player_colour,
    enum cell_contents board[][BOARDHEIGHT], unsigned* x_jumped,
    unsigned* y_jumped)
{
    unsigned x_start = next_move.start.x;
    unsigned y_start = next_move.start.y;
    unsigned x_end = next_move.end.x;
    unsigned y_end = next_move.end.y;
    
    /* Know that: - end location is empty and within bounds
                  - piece being moved is the players piece */
    if(player_colour == P_RED)
    {
        if(board[y_start][x_start] == RED)
        {
            if((abs_diff(x_start, x_end) != 2) ||
               (y_end - y_start != 2))
            {
                return FALSE;
            }
            *y_jumped = y_start + 1;
            if(x_end < x_start)
            {
                /* Piece being jumped is to the left */
                *x_jumped = x_start - 1;
            }
            else
            {
                /* Piece being jumped is to the right */
                *x_jumped = x_start + 1;
            }
        }
        if(board[y_start][x_start] == K_RED)
        {
            if(!is_valid_king_jump(next_move, x_jumped, y_jumped))
            {
                return FALSE;
            }
        }
        /* Cannot jump your own piece (or empty piece) */
        if(board[*y_jumped][*x_jumped] == RED ||
           board[*y_jumped][*x_jumped] == K_RED ||
           board[*y_jumped][*x_jumped] == EMPTY)
        {
            return FALSE;
        }
    }
    
    if(player_colour == P_WHITE)
    {
        if(board[y_start][x_start] == WHITE)
        {
            if((abs_diff(x_start, x_end) != 2) ||
               (y_start - y_end != 2))
            {
                return FALSE;
            }
            *y_jumped = y_start - 1;
            if(x_end < x_start)
            {
                /* Piece being jumped is to the left */
                *x_jumped = x_start - 1;
            }
            else
            {
                /* Piece being jumped is to the right */
                *x_jumped = x_start + 1;
            }
        }
        if(board[y_start][x_start] == K_WHITE)
        {
            if(!is_valid_king_jump(next_move, x_jumped, y_jumped))
            {
                return FALSE;
            }
        }
        /* Cannot jump your own piece */
        if(board[*y_jumped][*x_jumped] == WHITE ||
           board[*y_jumped][*x_jumped] == K_WHITE ||
           board[*y_jumped][*x_jumped] == EMPTY)
        {
            return FALSE;
        }
    }
    
    return TRUE;
}

BOOLEAN is_valid_king_jump(struct move next_move, unsigned* x_jumped,
    unsigned* y_jumped)
{
    unsigned x_start = next_move.start.x;
    unsigned y_start = next_move.start.y;
    unsigned x_end = next_move.end.x;
    unsigned y_end = next_move.end.y;
    
    /* Know that: - end location is empty and within bounds
                  - piece being moved is the players piece */
    
    /* Jumping left and down */
    if((x_end == x_start - 2) && (y_end == y_start + 2))
    {
        *x_jumped = x_start - 1;
        *y_jumped = y_start + 1;
    }
    /* Jumping left and up */
    else if((x_end == x_start - 2) && (y_end == y_start - 2))
    {
        *x_jumped = x_start - 1;
        *y_jumped = y_start - 1;
    }
    /* Jumping right and down */
    else if((x_end == x_start + 2) && (y_end == y_start + 2))
    {
        *x_jumped = x_start + 1;
        *y_jumped = y_start + 1;
    }
    /* Jumping right and up */
    else if((x_end == x_start + 2) && (y_end == y_start - 2))
    {
        *x_jumped = x_start + 1;
        *y_jumped = y_start - 1;
    }
    else
    {
        return FALSE;
    }
    
    return TRUE;
}

BOOLEAN is_jump(struct move validated_move, enum colour player_colour, 
    enum cell_contents board[][BOARDHEIGHT], unsigned* x_jumped,
    unsigned* y_jumped)
{
    if(is_valid_jump(validated_move, player_colour, board, x_jumped, y_jumped))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/* Requirement 7 - Tests whether the next player has any valid moves
 * Returns true if player has moves available */
BOOLEAN test_for_winner(struct player* next_player, 
    enum cell_contents board[][BOARDHEIGHT])
{
    struct move test_move;
    int x,y;
    
    for(y = 0; y < BOARDHEIGHT; ++y)
    {
        for(x = 0; x < BOARDWIDTH; ++x)
        {
            test_move.start.x = x;
            test_move.start.y = y;
            /* Test stepping up left */
            if(y - 1 >= 0 && x - 1 >= 0)
            {
                test_move.end.x = x - 1;
                test_move.end.y = y - 1;
                if(is_valid_move(test_move, next_player, board) != INVALID)
                {
                    return TRUE;
                }
            }
            /* Test stepping up right */
            if(y - 1 >= 0)
            {
                test_move.end.x = x + 1;
                test_move.end.y = y - 1;
                if(is_valid_move(test_move, next_player, board) != INVALID)
                {
                    return TRUE;
                }
            }
            /* Test stepping down left */
            if(x - 1 >= 0)
            {
                test_move.end.x = x - 1;
                test_move.end.y = y + 1;
                if(is_valid_move(test_move, next_player, board) != INVALID)
                {
                    return TRUE;
                }
            }
            /* Test stepping down right */
            test_move.end.x = x + 1;
            test_move.end.y = y + 1;
            if(is_valid_move(test_move, next_player, board) != INVALID)
            {
                return TRUE;
            }
            
            /* Test jumping up left */
            if(y - 2 >= 0 && x - 2 >= 0)
            {
                test_move.end.x = x - 2;
                test_move.end.y = y - 2;
                if(is_valid_move(test_move, next_player, board) != INVALID)
                {
                    return TRUE;
                }
            }
            /* Test jumping up right */
            if(y - 2 >= 0)
            {
                test_move.end.x = x + 2;
                test_move.end.y = y - 2;
                if(is_valid_move(test_move, next_player, board) != INVALID)
                {
                    return TRUE;
                }
            }
            /* Test jumping down left */
            if(x - 2 >= 0)
            {
                test_move.end.x = x - 2;
                test_move.end.y = y + 2;
                if(is_valid_move(test_move, next_player, board) != INVALID)
                {
                    return TRUE;
                }
            }
            /* Test jumping down right */
            test_move.end.x = x + 2;
            test_move.end.y = y + 2;
            if(is_valid_move(test_move, next_player, board) != INVALID)
            {
                return TRUE;
            }
        }
    }
    
    return FALSE;
}
