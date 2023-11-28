#include <string.h>
#include "functions.h"

char *search_cpr(char *first_col, FILE *file) //Kald funktion search first
{
    char *buffer = malloc(150 * sizeof(char));

    char *return_buffer = malloc(150 * sizeof(char));
    char *token;

    while (fgets(buffer, sizeof(char)*150, file) != NULL)
    {
        strcpy(return_buffer, buffer);
        token = strtok(buffer, ",");

        if (strcmp(token, first_col) == 0)
        {

            fclose(file);
            return return_buffer;
        }

    }

    return "value not found";
}
