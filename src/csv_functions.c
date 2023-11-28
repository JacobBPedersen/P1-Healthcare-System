#include <string.h>
#include "functions.h"

char *search_cpr(char *first_col, FILE *file) //Kald funktion search first
{
    char buffer[150];

    char return_buffer[150];
    char *token;

    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        strcpy(return_buffer, buffer);
        token = strtok(buffer, ",");

        if (strcmp(token, first_col) == 0)
        {

            fclose(file);
            return strdup(return_buffer);
        }

    }


    return "Value not found";
}
