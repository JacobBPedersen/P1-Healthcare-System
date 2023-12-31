#include "functions.h"

void GP_main_flow (GP current_gp) {
    //prints info of the user
    print_user_gp(current_gp);

    patient current_patient;

    char cpr[CPR_LENGTH];

    int exit = 1;
    //while loop to keep program running
    while (exit == 1) {
        int mode_choice_gp;
        printf("\nSelect mode:\n1 - Create Referral\t2 - Create Patient\t3 - Edit Patient\t-1 - Exit\n>");
        while (1) {
            if (scanf(" %d", &mode_choice_gp) == 1) {
                break;
            }
            printf("Invalid input. Try again:\n>");
            clear_buffer();
        }
        //allows the user to access different modes
        switch (mode_choice_gp) {
            //accessing "create referral" mode
            case 1:
                current_patient = search_patient();
                char choice_ref;
                printf("\nDo you want to create a referral for a patient (Yes: 1, No: 0) Name:%s CPR:%s\n>", current_patient.name,
                       current_patient.CPR);
                scanf(" %c", &choice_ref);
                if (choice_ref != '1') {
                    break;
                }
                create_referral(current_patient, current_gp);
                printf("\nReferral created. Do you want to continue (Yes: 1, No: 0):\n>");
                scanf(" %c", &choice_ref);
                if (choice_ref != '1') {
                    exit = 0;
                }
                break;
            //accessing "create patient" mode
            case 2:
                printf("Enter CPR of patient:\n>");
                scanf(" %[^\n]", cpr);
                while(1) {
                    if (cpr_validator(cpr) == 0) {
                        break;
                    }
                    printf("Invalid CPR. Try again:\n>");
                    scanf(" %[^\n]", cpr);
                }
                create_patient(cpr);
                break;
            //accessing "edit patient info" mode
            case 3:
                edit_patient_info();
                break;
            //exits the program
            case -1:
                exit = 0;
                break;
            default:
                printf("\nInvalid input\n");
        }
    }
}

void hosp_main_flow (hosp_person current_hosp) {
    //prints info of the user
    print_user_hosp(current_hosp);

    referral current_ref;

    int exit = 1;
    int ref_returned;
    //while loop to keep program running
    while (exit == 1) {
        int mode_choice_hosp;
        printf("\nSelect mode:\n1 - View Inbox\t2 - View Timetable\t-1 - Exit\n>");
        while (1) {
            if (scanf(" %d", &mode_choice_hosp) == 1) {
                break;
            }
            printf("Invalid input. Try again:\n>");
            clear_buffer();
        }
        //allows the user to access different modes
        switch (mode_choice_hosp) {
            //accessing "view inbox" mode
            case 1:
                current_ref = referral_inbox(&ref_returned, current_hosp);
                if (ref_returned == 1) {
                    review_referral(current_ref);
                }
                break;
            //accessing "view timetable" mode
            case 2:
                printf("\n");
                print_timetable();
                printf("\n");
                int choice;
                printf("Do you want to view/reschedule appointment?\n1 - Yes\t0 - No\n>");
                scanf("%d", &choice);
                if(choice == 1) {
                    handle_appointment();
                } else {
                    break;
                }
            //exits the program
            case -1:
                exit = 0;
                break;
            default:
                printf("Invalid input");
        }
    }
}