#include "functions.h"

void user_cred(int* GP_or_Hosp) {
    //Takes input as to who is using the program, and what it is supposed to do at the moment
    int invalid_input;
    do {
        invalid_input = 0;
        printf("Please enter if GP (1) or Hospital (0):\n>");
        scanf(" %d", GP_or_Hosp);
        clear_buffer();
        if (*GP_or_Hosp != 0 && *GP_or_Hosp != 1) {
            printf("Please enter a valid input\n");
            invalid_input = 1;
        }

    } while (invalid_input == 1);
}

GP GP_user(){

    do {
        char id[DETAILS_LENGTH];

        printf("Please enter id:\n>");
        scanf(" %s", id);

        FILE *fp_gp = fopen("./database/GP_usernames.csv", "r");

        if (fp_gp == NULL) {
            printf("Error");
            exit(EXIT_FAILURE);
        }

        char *GP_info = search_first(id, fp_gp);
        fclose(fp_gp);

        if (strcmp(GP_info, "Value not found") == 0) {
            printf("\nError user not found.\n");
        } else {
            GP current_gp;
            sscanf(GP_info, "%[^,],%[^,],%[^,],%[^,],%[^\n]", current_gp.id, current_gp.name, current_gp.title,
                   current_gp.clinic, current_gp.phone_num);
            return current_gp;
        }
    } while (1);

}

hosp_person hosp_user (){

    do {

        char id[DETAILS_LENGTH];

        printf("Please enter id:\n>");
        scanf(" %s", id);

        FILE *fp_hosp = fopen("./database/hospital_usernames.csv", "r");

        if (fp_hosp == NULL) {
            printf("Error");
            exit(EXIT_FAILURE);
        }

        char *hosp_info = search_first(id, fp_hosp);
        fclose(fp_hosp);

        if (strcmp(hosp_info, "Value not found") == 0) {
            printf("\nError user not found.\n");
        } else {
            hosp_person current_hosp;
            sscanf(hosp_info, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]", current_hosp.id, current_hosp.name,
                   current_hosp.title, current_hosp.location, current_hosp.department, current_hosp.phone_num);
            return current_hosp;
        }

    } while (1);

}


