#include "header.h"

/* Convert 4 bytes of frame size into one integer value */
unsigned int get_frame_size(unsigned char *size)
{
    unsigned int value;
    /* Combine the 4 bytes to get the actual frame size */
    value = ((unsigned int)size[0] << 24) |
            ((unsigned int)size[1] << 16) |
            ((unsigned int)size[2] << 8)  |
            ((unsigned int)size[3]);
    return value;
}

/* Print the text stored inside a frame */
void print_text(unsigned char *data, unsigned int size)
{
    unsigned int i;
    /* Skip the frame if it contains only the encoding byte */
    if (size <= 1)
        return;

    /* Start from byte 1 because byte 0 contains encoding information */
    for (i = 1; i < size; i++)
    {
        /* Stop printing when the string ends */
        if (data[i] == '\0')
            break;

        /* Print only readable characters */
        if (data[i] >= 32 && data[i] <= 126)
            printf("%c", data[i]);
    }
    printf("\n");
}

/* Open the MP3 file and display its ID3v2.3 tag information */
int view_mp3(char *filename)
{
    FILE *fp;

    unsigned char header[10];
    unsigned char frame_header[10];

    unsigned int tag_size;
    unsigned int frame_size;

    unsigned char *frame_data;

    char frame_id[5];

    unsigned int total_read = 0;

    /* Open the MP3 file in binary read mode */
    fp = fopen(filename, "rb");
    /* Check whether the file was opened successfully */
    if (fp == NULL)
    {
        printf("\nERROR: Unable to open MP3 file\n");
        return FAILURE;
    }
    /* Read the first 10 bytes which contain the ID3 header */
    if (fread(header, 1, 10, fp) != 10)
    {
        printf("\nERROR: Unable to read ID3 header\n");
        fclose(fp);
        return FAILURE;
    }
    /* Check whether the file starts with ID3 */
    if (header[0] != 'I' ||
        header[1] != 'D' ||
        header[2] != '3')
    {
        printf("\nERROR: ID3 tag not found\n");
        fclose(fp);
        return FAILURE;
    }
    /* Check whether the MP3 contains ID3v2.3 */
    if (header[3] != 3)
    {
        printf("\nERROR: Only ID3v2.3 is supported\n");
        fclose(fp);
        return FAILURE;
    }
    printf("\n------------------------------------------------------------\n");
    printf("              MP3 TAG READER AND EDITOR\n");
    printf("------------------------------------------------------------\n");
    printf("\nID3 VERSION : 2.3.0\n");

    /* Get the total size of the ID3 tag from the header */
    tag_size = ((unsigned int)(header[6] & 0x7F) << 21) |
               ((unsigned int)(header[7] & 0x7F) << 14) |
               ((unsigned int)(header[8] & 0x7F) << 7)  |
               ((unsigned int)(header[9] & 0x7F));

    printf("TAG SIZE    : %u bytes\n", tag_size);
    printf("\n------------------------------------------------------------\n");
    printf("SELECTED VIEW DETAILS\n");
    printf("------------------------------------------------------------\n");

    /* Keep reading frames until the complete ID3 tag is processed */
    while (total_read + 10 <= tag_size)
    {
        /* Read the next 10 bytes which contain the frame header */
        if (fread(frame_header, 1, 10, fp) != 10)
            break;

        /* Stop reading when an empty frame is found */
        if (frame_header[0] == 0)
            break;

        /* Copy the 4-byte frame ID into a string */
        frame_id[0] = frame_header[0];
        frame_id[1] = frame_header[1];
        frame_id[2] = frame_header[2];
        frame_id[3] = frame_header[3];
        frame_id[4] = '\0';
        /* Get the size of the current frame */
        frame_size = get_frame_size(&frame_header[4]);
        /* Stop if the frame size is invalid */
        if (frame_size == 0 || frame_size > tag_size)
            break;

        /* Allocate memory to store the frame data */
        frame_data = malloc(frame_size);
        /* Stop if memory allocation fails */
        if (frame_data == NULL)
        {
            fclose(fp);
            return FAILURE;
        }
        /* Read the frame data from the MP3 file */
        if (fread(frame_data, 1, frame_size, fp) != frame_size)
        {
            free(frame_data);
            break;
        }
        /* Check whether the current frame is the title */
        if (strcmp(frame_id, "TIT2") == 0)
        {
            printf("TITLE   : ");
            print_text(frame_data, frame_size);
        }
        /* Check whether the current frame is the artist */
        else if (strcmp(frame_id, "TPE1") == 0)
        {
            printf("ARTIST  : ");
            print_text(frame_data, frame_size);
        }
        /* Check whether the current frame is the album */
        else if (strcmp(frame_id, "TALB") == 0)
        {
            printf("ALBUM   : ");
            print_text(frame_data, frame_size);
        }
        /* Check whether the current frame is the year */
        else if (strcmp(frame_id, "TYER") == 0)
        {
            printf("YEAR    : ");
            print_text(frame_data, frame_size);
        }
        /* Check whether the current frame is the music genre */
        else if (strcmp(frame_id, "TCON") == 0)
        {
            printf("MUSIC   : ");
            print_text(frame_data, frame_size);
        }
        /* Check whether the current frame is the comment */
        else if (strcmp(frame_id, "COMM") == 0)
        {
            printf("COMMENT : ");

            /* Skip the encoding and language bytes of the comment frame */
            if (frame_size > 4)
            {
                unsigned int i;

                /* Print the comment text */
                for (i = 4; i < frame_size; i++)
                {
                    /* Print only readable characters */
                    if (frame_data[i] >= 32 &&
                        frame_data[i] <= 126)
                    {
                        printf("%c", frame_data[i]);
                    }
                }
                printf("\n");
            }
        }
        /* Release the memory used by the current frame */
        free(frame_data);
        /* Move the count to the beginning of the next frame */
        total_read += 10 + frame_size;
    }
    printf("------------------------------------------------------------\n");
    /* Close the MP3 file after reading is complete */
    fclose(fp);
    return SUCCESS;
}