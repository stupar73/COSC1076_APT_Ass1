/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2014 Assignment #1 
 * Full Name        : Stuart Parker
 * Student Number   : s3390317
 * Course Code      : COSC1076 - Advanced Programming Technique
 * Program Code     : BP094 - Bachelor of Computer Science
 * Start up code provided by Paul Miller and Virginia King
 **********************************************************************/

#ifndef UTILITY_H
#define UTILITY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NAME_LEN 20
#define MAX_INPUT_LEN 80

typedef enum
{
    FALSE, TRUE
} BOOLEAN;

enum input_result
{
    INPUT_TOOBIG, INPUT_EMPTY, INPUT_SUCCESS
};

enum int_result
{
    INT_INPUTTOOBIG, INT_INPUTEMPTY, INT_NOTINT, INT_OUTOFRANGE, INT_SUCCESS
};

void read_rest_of_line(void);
enum input_result get_input(char* s, unsigned size);
enum int_result get_int(int* n, unsigned size, int min, int max);
void print_multi(char c, int n);
unsigned abs_diff(unsigned x, unsigned y);

#endif
