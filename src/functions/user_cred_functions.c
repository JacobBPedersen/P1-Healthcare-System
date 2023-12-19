#include "functions.h"

void user_cred(int* GP_or_Hosp) {

    printf("Please enter if GP (1) or Hospital (0):\n>");
    while (1) {
        if (scanf(" %d", GP_or_Hosp) == 1 && (*GP_or_Hosp == 1 || *GP_or_Hosp == 0)) {
            break;
        }
        printf("Invalid input. Try again:\n>");
        clear_buffer();
    }
}

GP GP_user(){

    do {
        char id[DETAILS_LENGTH];

        printf("Please enter id:\n>");
        scanf(" %s", id);

        FILE *fp_gp = fopen("./database/gp_users.csv", "r");

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

        FILE *fp_hosp = fopen("./database/hosp_users.csv", "r");

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


