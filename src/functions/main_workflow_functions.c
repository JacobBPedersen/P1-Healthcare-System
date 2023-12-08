#include "functions.h"

void GP_main_flow (GP current_gp) {

    print_user_gp(current_gp);

    patient current_patient;

    int exit = 1;

    while (exit == 1) {
        int mode_choice_gp;
        printf("\nSelect mode:\n1 - Create Referral\t2 - Create Patient\t3 - Edit Patient\t-1 - Exit\n>");
        scanf("%d", &mode_choice_gp);
        switch (mode_choice_gp) {
            case 1:
                current_patient = search_patient();
                char choice_ref;
                printf("\nDo you want to create a referral for a patient (y/n) Name:%s CPR:%s\n>", current_patient.name,
                       current_patient.CPR);
                scanf(" %c", &choice_ref);
                if (choice_ref != 'y') {
                    break;
                }
                create_referral(current_patient, current_gp);
                printf("Referral created. Do you want to continue (y/n):\n>");
                scanf(" %c", &choice_ref);
                if (choice_ref != 'y') {
                    exit = 0;
                }
                break;
            case 2:
                create_patient();
                break;
            case 3:
                edit_patient_info();
                break;
            case -1:
                exit = 0; //Evt. i stedet for en exit condition for while, så blot return "log out".
                break;
            default:
                printf("Invalid input");
        }
    }


}


void hosp_main_flow (hosp_person current_hosp) {

    print_user_hosp(current_hosp);

    patient current_patient;

    referral current_ref;

    int exit = 1;
    int ref_returned;

    while (exit == 1) {
        int mode_choice_hosp;
        printf("\nSelect mode:\n1 - View Inbox\t2 - View Timetable\t3 - Forward Referral\t-1 - Exit\n>");
        scanf("%d", &mode_choice_hosp);
        clear_buffer();
        switch (mode_choice_hosp) {
            case 1:
                current_ref = referral_inbox(&ref_returned);
                if (ref_returned == 1) {
                    review_referral(current_ref);
                }
                break;
            case 2:
                printf("\n");
                time_node_structure(TREATMENT_TIME_FRAME, 0);
                printf("\n");
                break;
                //case 3: //
                //break;
            case -1:
                exit = 0; //Evt. i stedet for en exit condition for while, så blot return "log out".
                break;
            default:
                printf("Invalid input");
        }
    }


}
