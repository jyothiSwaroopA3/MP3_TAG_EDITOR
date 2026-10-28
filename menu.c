#include "header.h"

/*  Displays correct command line syntax.*/

void print_usage(void)
{
    printf("\n");
    printf("------------------------------------------------------------\n");
    printf("ERROR: INVALID ARGUMENTS\n");
    printf("------------------------------------------------------------\n");

    printf("\nUSAGE:\n");

    printf("\nTo view MP3 file:\n");
    printf("./a.out -v sample.mp3\n");

    printf("\nTo edit MP3 file:\n");
    printf("./a.out -e -t new_title sample.mp3\n");

    printf("\nTo get help:\n");
    printf("./a.out --help\n");

    printf("\n------------------------------------------------------------\n");
}

/*Displays complete help menu.*/

void print_help(void)
{
    printf("\n");
    printf("------------------------------------------------------------\n");
    printf("                    HELP MENU\n");
    printf("------------------------------------------------------------\n");

    printf("\n1. VIEW MP3 FILE\n");
    printf("   -v  -> View MP3 file contents\n");

    printf("\n2. EDIT MP3 FILE\n");

    printf("   -t  -> Edit Title\n");
    printf("   -a  -> Edit Artist\n");
    printf("   -A  -> Edit Album\n");
    printf("   -y  -> Edit Year\n");
    printf("   -m  -> Edit Content / Genre\n");
    printf("   -c  -> Edit Comment\n");

    printf("\nEXAMPLES:\n");

    printf("./a.out -v sample.mp3\n");

    printf("./a.out -e -t new_title sample.mp3\n");
    printf("./a.out -e -a new_artist sample.mp3\n");
    printf("./a.out -e -A new_album sample.mp3\n");
    printf("./a.out -e -y 2022 sample.mp3\n");
    printf("./a.out -e -m rock sample.mp3\n");
    printf("./a.out -e -c my_comment sample.mp3\n");

    printf("\n------------------------------------------------------------\n");
}