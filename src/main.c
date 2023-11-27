#include "functions.h"

int main()
{
    // create_referral()

    FILE *patients_file = fopen("patient_register.csv", "r");

    if(patients_file == NULL){

        printf("Error");
    }

    char *test = search_cpr("333333-3333", patients_file);


    printf("%s", test);

    return 0;
}