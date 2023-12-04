#include "functions.h"

int main()
{
    int GP_or_Hosp;
    GP current_gp;
    hosp_person current_hosp;
    patient current_patient;

    referral new_test = {"333333-3333","Knud Knudsen",25,'f',"+4577777777","9000","Aalborg","Lil knud","10 4.tv","farmand","+4566666666","farmand@gmail.com",2,3,"dawd","dwadwdaw","ffdfd","adsc","rfr","dsadrgr",0,"-","Niels Nielsen","Secretary","Nordlaege","+4500000000"};
    //review_referral(new_test);



    user_cred(&GP_or_Hosp);

    if (GP_or_Hosp == 1) {
        //Funktion til GP program
        current_gp = GP_user();
        print_test_personnel_gp(current_gp); // test
        int exit = 1;
        while (exit == 1) {
            int mode_choice_gp;
            printf("\nSelect mode:\n1 - Create Referral\t2 - Create Patient\t3 - Edit Patient\t-1 - Exit\n>");
            scanf("%d", &mode_choice_gp);
            switch (mode_choice_gp) {
                case 1:
                    current_patient = search_patient();
                    char choice_ref;
                    printf("Do you want to create a referral for a patient (y/n) Name:%s CPR:%s\n>", current_patient.name,
                           current_patient.CPR);
                    scanf(" %c", &choice_ref);
                    if (choice_ref != 'y') {
                        break;
                    }
                    create_referral(current_patient, current_gp);
                    printf("Do you want to continue (y/n):\n>");
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
    } else {
        current_hosp = hosp_user();
        print_test_personnel_hosp(current_hosp); // test
        review_referral(new_test);
    }





    //char *test = search_first("333333-3333", patients_file);

    //printf("%s", test);

    return 0;
}