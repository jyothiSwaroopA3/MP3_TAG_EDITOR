#include "header.h"

int main(int argc, char *argv[])
{
    MP3 mp3;

    /* STEP 1: Check command line arguments */

    if (argc < 2)
    {
        printf("\nERROR: Command line arguments not passed\n");
        print_usage();
        return FAILURE;
    }

    /* STEP 2: Check VIEW operation ./a.out -v sample.mp3 */

    if (strcmp(argv[1], "-v") == 0)
    {
        if (argc != 3)
        {
            printf("\nERROR: Invalid arguments for view\n");
            print_usage();
            return FAILURE;
        }

        mp3.operation = argv[1];
        mp3.filename = argv[2];

        if (view_mp3(mp3.filename))
        {
            printf("\nDETAILS DISPLAYED SUCCESSFULLY\n");
            return SUCCESS;
        }
        else
        {
            printf("\nVIEW OPERATION FAILED\n");
            return FAILURE;
        }
    }
    /*STEP 3: Check EDIT operation
       ./a.out -e -t new-title sample.mp3 */
    if (strcmp(argv[1], "-e") == 0)
    {
        if (argc != 5)
        {
            printf("\nERROR: Invalid arguments for edit\n");
            print_usage();
            return FAILURE;
        }

        mp3.operation = argv[1];
        mp3.edit_option = argv[2];
        mp3.value = argv[3];
        mp3.filename = argv[4];

        /*STEP 4: Check edit option */
        if (strcmp(mp3.edit_option, "-t") == 0)
        {
            if (edit_title(mp3.filename, mp3.value))
            {
                printf("\nTITLE CHANGED SUCCESSFULLY\n");
                return SUCCESS;
            }
        }
        else if (strcmp(mp3.edit_option, "-a") == 0)
        {
            if (edit_artist(mp3.filename, mp3.value))
            {
                printf("\nARTIST CHANGED SUCCESSFULLY\n");
                return SUCCESS;
            }
        }
        else if (strcmp(mp3.edit_option, "-A") == 0)
        {
            if (edit_album(mp3.filename, mp3.value))
            {
                printf("\nALBUM CHANGED SUCCESSFULLY\n");
                return SUCCESS;
            }
        }
        else if (strcmp(mp3.edit_option, "-y") == 0)
        {
            if (edit_year(mp3.filename, mp3.value))
            {
                printf("\nYEAR CHANGED SUCCESSFULLY\n");
                return SUCCESS;
            }
        }
        else if (strcmp(mp3.edit_option, "-m") == 0)
        {
            if (edit_content(mp3.filename, mp3.value))
            {
                printf("\nCONTENT CHANGED SUCCESSFULLY\n");
                return SUCCESS;
            }
        }
        else if (strcmp(mp3.edit_option, "-c") == 0)
        {
            if (edit_comment(mp3.filename, mp3.value))
            {
                printf("\nCOMMENT CHANGED SUCCESSFULLY\n");
                return SUCCESS;
            }
        }
        else
        {
            printf("\nERROR: Invalid edit option\n");
            print_help();
            return FAILURE;
        }

        printf("\nEDIT OPERATION FAILED\n");
        return FAILURE;
    }
    /*STEP 5: Invalid main operation */
    printf("\nERROR: Invalid command line arguments\n");
    print_usage();

    return FAILURE;
}