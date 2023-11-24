#include <string.h>
#include "functions.h"

char *search_cpr(char *cpr, FILE *file)
{
    char buffer[50];

    char *return_buffer = malloc(50 * sizeof(char));
    char *token;

    int found = 0;
    int column = 0;

    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        strcpy(return_buffer, buffer);

        buffer[strcspn(buffer, "\n")] = 0;
        token = strtok(buffer, ",");

        if (token == NULL)
        {
            printf("Value not found");
            return 0;
        }

        if (strcmp(token, cpr) == 0)
        {

            found = 1;
            break;
        }

        token = strtok(NULL, ",");

        if (found)
        {
            fclose(file);
            return return_buffer;
        }
    }
    return return_buffer;
}
