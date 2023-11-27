#include <string.h>
#include "functions.h"

char *search_cpr(char *cpr, FILE *file)
{
    char *buffer = malloc(150 * sizeof(char));

    char *return_buffer = malloc(150 * sizeof(char));
    char *token;

    int found = 0;

    while (fgets(buffer, sizeof(char)*150, file) != NULL)
    {
        strcpy(return_buffer, buffer);
        token = strtok(buffer, ",");

        if (strcmp(token, cpr) == 0)
        {
            found = 1;
        }

        if (found)
        {
            fclose(file);
            return return_buffer;
        }
    }
    return "value not found";
}
