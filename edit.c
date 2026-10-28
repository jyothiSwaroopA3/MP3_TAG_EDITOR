#include "header.h"

/* Convert the frame size into 4 bytes */
void put_frame_size(unsigned char *size, unsigned int value)
{
    /* Store the highest byte first */
    size[0] = (value >> 24) & 0xFF;

    /* Store the next byte */
    size[1] = (value >> 16) & 0xFF;

    /* Store the next byte */
    size[2] = (value >> 8) & 0xFF;

    /* Store the lowest byte */
    size[3] = value & 0xFF;
}
/* Find the required tag and replace its value */
int edit_tag(char *filename, char *tag, char *new_value)
{
    FILE *fp;

    unsigned char header[10];
    unsigned char frame_header[10];

    unsigned int tag_size;
    unsigned int frame_size;

    unsigned char *data;

    char frame_id[5];

    unsigned int total_read = 0;

    long data_position;

    /* Open the MP3 file for reading and writing */
    fp = fopen(filename, "r+b");

    /* Check whether the file opened successfully */
    if (fp == NULL)
    {
        printf("\nERROR: Unable to open MP3 file\n");
        return FAILURE;
    }
    /* Read the first 10 bytes of the MP3 file */
    if (fread(header, 1, 10, fp) != 10)
    {
        fclose(fp);
        return FAILURE;
    }
    /* Check whether the file contains an ID3 tag */
    if (header[0] != 'I' ||
        header[1] != 'D' ||
        header[2] != '3')
    {
        printf("\nERROR: ID3 tag not found\n");
        fclose(fp);
        return FAILURE;
    }

    /* Check whether the file uses ID3v2.3 */
    if (header[3] != 3)
    {
        printf("\nERROR: Only ID3v2.3 is supported\n");
        fclose(fp);
        return FAILURE;
    }
    /* Get the total size of the ID3 tag */
    tag_size = ((unsigned int)(header[6] & 0x7F) << 21) |
               ((unsigned int)(header[7] & 0x7F) << 14) |
               ((unsigned int)(header[8] & 0x7F) << 7)  |
               ((unsigned int)(header[9] & 0x7F));

    /* Read each frame until the required tag is found */
    while (total_read + 10 <= tag_size)
    {
        /* Read the next frame header */
        if (fread(frame_header, 1, 10, fp) != 10)
            break;

        /* Stop if an empty frame is found */
        if (frame_header[0] == 0)
            break;

        /* Copy the frame ID into a string */
        frame_id[0] = frame_header[0];
        frame_id[1] = frame_header[1];
        frame_id[2] = frame_header[2];
        frame_id[3] = frame_header[3];
        frame_id[4] = '\0';

        /* Get the size of the current frame */
        frame_size = ((unsigned int)frame_header[4] << 24) |
                     ((unsigned int)frame_header[5] << 16) |
                     ((unsigned int)frame_header[6] << 8)  |
                     ((unsigned int)frame_header[7]);

        /* Save the position where the frame data starts */
        data_position = ftell(fp);

        /* Check whether this is the tag we want to edit */
        if (strcmp(frame_id, tag) == 0)
        {
            unsigned int required_size;

            /* Calculate the space needed for the new text */
            required_size = 1 + strlen(new_value);

            /* Check whether the new text fits in the old frame */
            if (required_size > frame_size)
            {
                printf("\nERROR: New value is too long\n");
                printf("Existing frame size : %u\n", frame_size);
                printf("Required size       : %u\n", required_size);

                fclose(fp);
                return FAILURE;
            }

            /* Allocate memory for the new frame data */
            data = calloc(1, frame_size);

            /* Check whether memory was allocated */
            if (data == NULL)
            {
                fclose(fp);
                return FAILURE;
            }
            /* Set encoding to ISO-8859-1 */
            data[0] = 0;

            /* Copy the new value into the frame */
            strcpy((char *)&data[1], new_value);

            /* Move the file pointer to the frame data */
            fseek(fp, data_position, SEEK_SET);

            /* Write the new value into the MP3 file */
            if (fwrite(data, 1, frame_size, fp) != frame_size)
            {
                free(data);
                fclose(fp);
                return FAILURE;
            }
            /* Make sure the changes are written to the file */
            fflush(fp);

            /* Release the allocated memory */
            free(data);

            /* Close the MP3 file */
            fclose(fp);
            return SUCCESS;
        }
        /* Skip the current frame and move to the next frame */
        fseek(fp, frame_size, SEEK_CUR);

        /* Add the current frame size to the total bytes read */
        total_read += 10 + frame_size;
    }
    /* Display an error when the requested tag is not found */
    printf("\nERROR: Tag %s not found\n", tag);

    /* Close the MP3 file */
    fclose(fp);

    return FAILURE;
}
/* Edit the title using the TIT2 frame */
int edit_title(char *filename, char *new_value)
{
    printf("\n------------------------------------------------------------\n");
    printf("SELECTED EDIT DETAILS\n");
    printf("------------------------------------------------------------\n");
    printf("CHANGE THE TITLE\n");
    printf("TITLE : %s\n", new_value);

    /* Send TIT2 tag to the common editing function */
    return edit_tag(filename, "TIT2", new_value);
}
/* Edit the artist using the TPE1 frame */
int edit_artist(char *filename, char *new_value)
{
    printf("\n------------------------------------------------------------\n");
    printf("SELECTED EDIT DETAILS\n");
    printf("------------------------------------------------------------\n");
    printf("CHANGE THE ARTIST\n");
    printf("ARTIST : %s\n", new_value);

    /* Send TPE1 tag to the common editing function */
    return edit_tag(filename, "TPE1", new_value);
}
/* Edit the album using the TALB frame */
int edit_album(char *filename, char *new_value)
{
    printf("\n------------------------------------------------------------\n");
    printf("SELECTED EDIT DETAILS\n");
    printf("------------------------------------------------------------\n");
    printf("CHANGE THE ALBUM\n");
    printf("ALBUM : %s\n", new_value);

    /* Send TALB tag to the common editing function */
    return edit_tag(filename, "TALB", new_value);
}
/* Edit the year using the TYER frame */
int edit_year(char *filename, char *new_value)
{
    printf("\n------------------------------------------------------------\n");
    printf("SELECTED EDIT DETAILS\n");
    printf("------------------------------------------------------------\n");
    printf("CHANGE THE YEAR\n");
    printf("YEAR : %s\n", new_value);

    /* Send TYER tag to the common editing function */
    return edit_tag(filename, "TYER", new_value);
}
/* Edit the content or genre using the TCON frame */
int edit_content(char *filename, char *new_value)
{
    printf("\n------------------------------------------------------------\n");
    printf("SELECTED EDIT DETAILS\n");
    printf("------------------------------------------------------------\n");
    printf("CHANGE THE CONTENT\n");
    printf("CONTENT : %s\n", new_value);

    /* Send TCON tag to the common editing function */
    return edit_tag(filename, "TCON", new_value);
}
/* Edit the comment using the COMM frame */
int edit_comment(char *filename, char *new_value)
{
    FILE *fp;

    unsigned char header[10];
    unsigned char frame_header[10];

    unsigned int tag_size;
    unsigned int frame_size;

    unsigned int total_read = 0;

    char frame_id[5];

    /* Open the MP3 file for reading and writing */
    fp = fopen(filename, "r+b");

    /* Check whether the file opened successfully */
    if (fp == NULL)
    {
        printf("\nERROR: Unable to open MP3 file\n");
        return FAILURE;
    }
    /* Read the first 10 bytes of the MP3 file */
    if (fread(header, 1, 10, fp) != 10)
    {
        fclose(fp);
        return FAILURE;
    }
    /* Check whether the file contains an ID3 tag */
    if (header[0] != 'I' ||
        header[1] != 'D' ||
        header[2] != '3')
    {
        printf("\nERROR: ID3 tag not found\n");
        fclose(fp);
        return FAILURE;
    }
    /* Check whether the file uses ID3v2.3 */
    if (header[3] != 3)
    {
        printf("\nERROR: Only ID3v2.3 is supported\n");
        fclose(fp);
        return FAILURE;
    }
    /* Get the total size of the ID3 tag */
    tag_size = ((unsigned int)(header[6] & 0x7F) << 21) |
               ((unsigned int)(header[7] & 0x7F) << 14) |
               ((unsigned int)(header[8] & 0x7F) << 7)  |
               ((unsigned int)(header[9] & 0x7F));

    /* Search each frame until the COMM frame is found */
    while (total_read + 10 <= tag_size)
    {
        long position;

        /* Read the next frame header */
        if (fread(frame_header, 1, 10, fp) != 10)
            break;

        /* Stop if an empty frame is found */
        if (frame_header[0] == 0)
            break;

        /* Copy the frame ID into a string */
        frame_id[0] = frame_header[0];
        frame_id[1] = frame_header[1];
        frame_id[2] = frame_header[2];
        frame_id[3] = frame_header[3];
        frame_id[4] = '\0';

        /* Get the size of the current frame */
        frame_size = ((unsigned int)frame_header[4] << 24) |
                     ((unsigned int)frame_header[5] << 16) |
                     ((unsigned int)frame_header[6] << 8)  |
                     ((unsigned int)frame_header[7]);

        /* Save the position where the frame data starts */
        position = ftell(fp);

        /* Check whether the current frame is COMM */
        if (strcmp(frame_id, "COMM") == 0)
        {
            unsigned char *data;
            unsigned int required_size;

            /* Calculate the space needed for the new comment */
            required_size = 5 + strlen(new_value);

            /* Check whether the new comment fits in the old frame */
            if (required_size > frame_size)
            {
                printf("\nERROR: New comment is too long\n");
                fclose(fp);
                return FAILURE;
            }
            /* Allocate memory for the comment */
            data = calloc(1, frame_size);

            /* Check whether memory was allocated */
            if (data == NULL)
            {
                fclose(fp);
                return FAILURE;
            }

            /* Set encoding to ISO-8859-1 */
            data[0] = 0;

            /* Set the language to English */
            data[1] = 'e';
            data[2] = 'n';
            data[3] = 'g';

            /* Keep the short description empty */
            data[4] = 0;

            /* Copy the new comment */
            strcpy((char *)&data[5], new_value);

            /* Move the file pointer to the comment data */
            fseek(fp, position, SEEK_SET);

            /* Write the new comment into the MP3 file */
            if (fwrite(data, 1, frame_size, fp) != frame_size)
            {
                free(data);
                fclose(fp);
                return FAILURE;
            }
            /* Make sure the changes are written to the file */
            fflush(fp);

            /* Release the allocated memory */
            free(data);

            /* Close the MP3 file */
            fclose(fp);
            return SUCCESS;
        }
        /* Skip the current frame and move to the next frame */
        fseek(fp, frame_size, SEEK_CUR);

        /* Add the current frame size to the total bytes read */
        total_read += 10 + frame_size;
    }
    /* Display an error when the COMM frame is not found */
    printf("\nERROR: COMM tag not found\n");
    /* Close the MP3 file */
    fclose(fp);
    return FAILURE;
}