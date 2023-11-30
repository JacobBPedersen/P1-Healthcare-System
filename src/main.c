#include "functions.h"

int main()
{
    int GP_or_Hosp;
    GP current_gp;
    hosp_person current_hosp;
    patient current_patient;



    FILE *patients_file = fopen("patient_register.csv", "r");

    if(patients_file == NULL){

        printf("Error");
    }


    user_cred(&GP_or_Hosp);

    if (GP_or_Hosp == 1) {
        current_gp = GP_user();
        print_test_personnel_gp(current_gp);
        current_patient = search_patient(patients_file);
        create_referral(current_patient, current_gp);

    } else {
        current_hosp = hosp_user();
        print_test_personnel_hosp(current_hosp);
    }





    //char *test = search_cpr("333333-3333", patients_file);

    //printf("%s", test);

    return 0;
}