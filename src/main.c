#include "functions.h"

int main()
{
    // create_referral()

    FILE *patients_file = fopen("./patient_register.csv", "r");

    char *test = search_cpr("333333-3333", patients_file);

    printf("%s", test);

    return 0;
}