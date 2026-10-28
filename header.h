#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Return status */
#define SUCCESS 1
#define FAILURE 0

/* Structure for storing command line arguments */
typedef struct
{
    char *operation;      // -v or -e
    char *edit_option;    // -t, -a, -A, -y, -m, -c
    char *value;          // New value
    char *filename;       // MP3 file
} MP3;

/* Menu functions */
void print_usage(void);
void print_help(void);

/* View function */
int view_mp3(char *filename);

/* Six edit functions */
int edit_title(char *filename, char *new_value);
int edit_artist(char *filename, char *new_value);
int edit_album(char *filename, char *new_value);
int edit_year(char *filename, char *new_value);
int edit_content(char *filename, char *new_value);
int edit_comment(char *filename, char *new_value);

/* Common edit function */
int edit_tag(char *filename, char *tag, char *new_value);

#endif