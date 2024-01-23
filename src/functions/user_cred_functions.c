#include "functions.h"

// Main function to determine if user is a GP or Hospital staff
void user_cred(int* GP_or_Hosp) {

    printf("Please enter if GP (1) or Hospital (0):\n>");
    while (1) {
        // Check if input is an integer and is either 1 or 0
        if (scanf(" %d", GP_or_Hosp) == 1 && (*GP_or_Hosp == 1 || *GP_or_Hosp == 0)) {
            break;
        }
        printf("Invalid input. Try again:\n>");
        clear_buffer();
    }
}

// Main GP user function
GP GP_user(){

    do {
        char id[DETAILS_LENGTH];

        printf("Please enter id:\n>");
        scanf(" %s", id);

        // Open GP user database
        FILE *fp_gp = fopen("./database/gp_users.csv", "r");

        if (fp_gp == NULL) {
            printf("Error");
            exit(EXIT_FAILURE);
        }

        // Search for user in database inputted by user
        char *GP_info = search_first(id, fp_gp);
        fclose(fp_gp);

        // If user not found, print error
        if (strcmp(GP_info, "Value not found") == 0) {
            printf("\nError user not found.\n");
        } else {
            // If user found, store user details in struct
            GP current_gp;
            sscanf(GP_info, "%[^,],%[^,],%[^,],%[^,],%[^\n]", current_gp.id, current_gp.name, current_gp.title,
                   current_gp.clinic, current_gp.phone_num);
            free(GP_info); // Added after submission
            return current_gp;
        }

    } while (1);

}

// Main hospital user function
hosp_person hosp_user (){

    do {

        char id[DETAILS_LENGTH];

        printf("Please enter id:\n>");
        scanf(" %s", id);

        // Open hospital user database
        FILE *fp_hosp = fopen("./database/hosp_users.csv", "r");

        if (fp_hosp == NULL) {
            printf("Error");
            exit(EXIT_FAILURE);
        }

        // Search for user in database inputted by user
        char *hosp_info = search_first(id, fp_hosp);
        fclose(fp_hosp);

        // If user not found, print error
        if (strcmp(hosp_info, "Value not found") == 0) {
            printf("\nError user not found.\n");
        } else {
            // If user found, store user details in struct
            hosp_person current_hosp;
            sscanf(hosp_info, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]", current_hosp.id, current_hosp.name,
                   current_hosp.title, current_hosp.location, current_hosp.department, current_hosp.phone_num);

            free(hosp_info); // Added after submission

            return current_hosp;
        }

    } while (1);

}


