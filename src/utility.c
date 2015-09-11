/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2014 Assignment #1 
 * Full Name        : Stuart Parker
 * Student Number   : s3390317
 * Course Code      : COSC1076 - Advanced Programming Techniques
 * Program Code     : BP094 - Bachelor of Computer Science
 * Start up code provided by Paul Miller and Virginia King
 **********************************************************************/
#include "utility.h"

/* Tidy up residual data in stdin when encountering an error. You will 
 * need to use this when there is a possibility that there will be 
 * leftover characters in the input buffer. */
void read_rest_of_line(void)
{
    int ch;
    /* remove all characters from the buffer */
    while(ch = getc(stdin), ch!='\n' && ch!=EOF);
    
    /* clear the error status of the input pointer */
    clearerr(stdin);
}

/* Reads user input from stdin and stores in 's'. Returns INPUT_EMPTY if no
 * input was read, returns INPUT_TOOBIG if input was greater than 'size',
 * returns INPUT_SUCCESS if input was successfully read and was no bigger
 * than 'size'. */
enum input_result get_input(char* s, unsigned size)
{
    unsigned len;
    
    fgets(s, MAX_INPUT_LEN, stdin);
    
    len = strlen(s);
    
    if(len == 1)
    {
        return INPUT_EMPTY;
    }
    else if(s[len-1] == '\n')
    {
        s[len-1] = '\0';
    }
    else
    {
        read_rest_of_line();
        return INPUT_TOOBIG;
    }
    
    return INPUT_SUCCESS;
}
/* Reads integer from user input using get_input(). Returns INT_INPUTTOOBIG
 * if user input exceeded 'size' , returns INT_INPUTEMPTY if no input was read,
 * returns INT_NOTINT if the user entered something that was not an integer,
 * returns INT_OUTOFRANGE if the integer entered was greater than 'max' or less
 * than 'min', returns INT_SUCCESS if input was successfully read and converted
 * to an integer (which is then stored in the int pointer passed into function
 */
enum int_result get_int(int* n, unsigned size, int min, int max)
{
    char temp_str[MAX_INPUT_LEN];
    int temp_int = 0;
    char* end_ptr;
    enum input_result input_res;
    
    input_res = get_input(temp_str, size);
    
    if(input_res == INPUT_TOOBIG)
    {
        return INT_INPUTTOOBIG;
    }
    else if(input_res == INPUT_EMPTY)
    {
        return INT_INPUTEMPTY;
    }
    else /* String successfully read */
    {
        temp_int = (int)strtol(temp_str, &end_ptr, 10);
        
        if(strcmp(end_ptr, "") != 0)
        {
            return INT_NOTINT;
        }
        else if(temp_int < min || temp_int > max)
        {
            return INT_OUTOFRANGE;
        }
        else
        {
            *n = temp_int;
            return INT_SUCCESS;
        }
    }
}

/* Prints character 'c' 'n' times */
void print_multi(char c, int n)
{
    int i;
    for(i = 0; i < n; ++i)
    {
        putchar(c);
    }
}

/* Returns the absoulute value of the difference between input variables */
unsigned abs_diff(unsigned x, unsigned y)
{
    if(x > y)
    {
        return x - y;
    }
    else
    {
        return y - x;
    }
}