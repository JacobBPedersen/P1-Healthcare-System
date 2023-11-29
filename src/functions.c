#include "functions.h"

#define DETAILS_LENGTH 40
#define PHONE_NUM 12
#define CPR_LENGTH 12

typedef struct address
{
    char zip_code[5];
    char city[DETAILS_LENGTH];
    char street_name[DETAILS_LENGTH];
    char house_number_etc[15];

} address;

typedef struct GP
{
    char name[DETAILS_LENGTH];
    char title[10];
    char clinic[10];
    char phone_num[PHONE_NUM];

} GP;

typedef struct relative
{
    char name[DETAILS_LENGTH];
    char phone_num[PHONE_NUM];
    char email[DETAILS_LENGTH];

} relative;

typedef struct patient
{ // Evt. hent info via cpr.
    char CPR[CPR_LENGTH];
    char name[DETAILS_LENGTH];
    // Date format
    int age;
    char sex;
    char phone_num[PHONE_NUM];
    address address;
    relative relative;

} patient;

typedef struct referral
{
    patient patient;
    int ref_dest;
    int diagnosis_cat;
    char diagnosis_desc[100];
    char short_anamnesis[1000];
    char results[500];
    char res_bact[100]; // Evt. bool.
    char handicap[100];
    char ref_purpose[200];
    int language_barrier;
    char language[DETAILS_LENGTH];
    GP GP;
    // char* preference; Evt. ikke anvendelig da de ikke selv skal prioritere.

} referral;

void user_cred()
{
    // Takes input as to who is using the program, and what it is supposed to do at the moment

    char username[DETAILS_LENGTH];
    // char password [50]; ??????

    printf("Please enter username:\n>");
    scanf(" %s", username);

    // printf("Please enter password:\n>");
    // scanf(" %s",password);

    // evt. return  GP?

    // skal hvis gp returne info om den praktiserende læge så den kan vedgå i henvisningen.
}

/**
 * @brief Validates a CPR
 * @param cpr A string representing a CPR number.
 * @return Returns 0 if valid, non-zero if invalid.
 */
int cprValidator(char cpr[CPR_LENGTH]){
    regex_t regex;
    regcomp(&regex, "^[0-9]{6}-[0-9]{4}$", REG_EXTENDED);
    return regexec(&regex, cpr, 0, NULL, 0);
}

patient search_patient(FILE *fp)
{
    char cpr[CPR_LENGTH];

    printf("Enter CPR of the patient.\n> ");

    // While loop for inserting and validating cpr number
    while(1){
        scanf("%s", cpr);

        int cpr_match = cprValidator(cpr);

        if (cpr_match == 0){
            break;
        };

        printf("Invalid format for CPR, try again.\n> ");

    }

    // Searches for a valid cpr number in the file register
    char *searched_patient = search_cpr(cpr, fp);

    // If patients doest exist, create on
    if (searched_patient == NULL)
    {

        char user_choice;

        printf("Patient not found, would you like to create patient? Y/n?\n> ");

        // While loop for creating patient, and validating user input.
        while (1){

            scanf(" %c",&user_choice);
            // clear_buffer();

            // If user want to create a patient
            if (user_choice == 'y' || user_choice == 'Y' ){

                // Create patient function here
                printf("CREATE PATIENT HERE");
                exit(1);
                //return create_patient();
            }else if(user_choice == 'n') {
                printf("EXIT PROGRAM");
                exit(1);
            }else{
                printf("Invalid input - Y/n\n> ");
            }
        }
    }

    // if patient does exit, define
    patient return_patient;

    // parsing string output from a found/existin
    sscanf(searched_patient, "%[^,],%[^,],%d,%c,%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,]"
            , return_patient.CPR, return_patient.name, &return_patient.age,
           &return_patient.sex, return_patient.phone_num, return_patient.address.zip_code, return_patient.address.city,
           return_patient.address.street_name, return_patient.address.house_number_etc,
           return_patient.relative.name, return_patient.relative.phone_num, return_patient.relative.email);

    return return_patient;
}

void create_referral(patient chosen_patient)
{
    // checks if the patient is already registered.
    // if not, a patient is created from scratch with create_patient
    // otherwise only asks for variable data in update_patient
    // saves patient data in the database

    referral new_referral;

    new_referral.patient = chosen_patient;

    // referral destination
    printf("Enter the destination of the referral:\n>");
    scanf(" %d", &new_referral.ref_dest);
    // Diagnosis category
    printf("Choose the diagnosis category of the referral:\n>");
    scanf(" %d", &new_referral.diagnosis_cat);
    // Diagnosis description
    printf("Enter a description for the diagnosis of the referral:\n>");
    scanf(" %[^\n]", new_referral.diagnosis_desc);
    // Short anamnesis
    printf("Write a short anamnesis of the referral:\n>");
    scanf(" %[^\n]", new_referral.short_anamnesis);
    // Test results
    printf("Enter the test results for the referral:\n>");
    scanf(" %[^\n]", new_referral.results);
    // Resistant bacteria
    printf("Enter resistant bacteria for the referral:\n>");
    scanf(" %[^\n]", new_referral.res_bact);
    // Handicap
    printf("Enter handicap(s) of the patient for the referral:\n>");
    scanf(" %[^\n]", new_referral.handicap);
    // Information given
    printf("Enter the information of the patient for the referral:\n>");
    scanf(" %[^\n]", new_referral.ref_purpose);
    // Language

    // Der skal promptes med en bool før den kan gå videre
    printf("Acknowledge if there is a language barrier of the patient for the referral:\n>");
    scanf(" %d", &new_referral.language_barrier);
    // Language
    if (new_referral.language_barrier == 0)
    {
        new_referral.language[0] = '-';
    }
    else
    {
        printf("Enter the spoken language of the patient for the referral:\n>");
        scanf(" %[^\n]", new_referral.language);
    }
    // General practioner

    //  new_referral.GP = GP; Skal være lig med hvad man indtaster ved login

    FILE *referrals = fopen("referrals.csv", "a+");
    if (referrals == NULL)
    {
        printf("Error");
        exit(EXIT_FAILURE);
    }

    fprintf(referrals, "\n%s,%d,%d,%s,%s,%s,%s,%s,%s,%d,%s",
            new_referral.patient.CPR, new_referral.ref_dest, new_referral.diagnosis_cat, new_referral.diagnosis_desc,
            new_referral.short_anamnesis, new_referral.results, new_referral.res_bact, new_referral.handicap,
            new_referral.ref_purpose, new_referral.language_barrier, new_referral.language);
}

void print_referral(referral new_referral)
{
}

patient create_patient()
{
    // Henvist til denne funktion hvis patient ikke findes.

    patient new_patient;
    // CPR
    printf("Enter CPR of patient:\n>");
    scanf(" %[^\n]", new_patient.CPR);
    fflush(stdin);
    // Name
    printf("Enter name of patient:\n>");
    scanf(" %[^\n]", new_patient.name);
    fflush(stdin);
    // Age - Midlertidig
    printf("Enter age of patient:\n>");
    scanf("%d", &new_patient.age);
    fflush(stdin);
    // Sex
    printf("Enter sex of patient:\n>");
    scanf(" %c", &new_patient.sex);
    fflush(stdin);
    // Phone Number
    printf("Enter phone number of patient:\n>");
    scanf(" %s", new_patient.phone_num);
    fflush(stdin);
    // Address
    printf("Enter zip-code of patient:\n>");
    scanf(" %s", new_patient.address.zip_code);
    fflush(stdin);

    printf("Enter city of patient:\n>");
    scanf(" %[^\n]", new_patient.address.city);
    fflush(stdin);

    printf("Enter street name of patient:\n>");
    scanf(" %[^\n]", new_patient.address.street_name);
    fflush(stdin);

    printf("Enter house number etc. of patient:\n>");
    scanf(" %[^\n]", new_patient.address.house_number_etc);
    fflush(stdin);
    // Relatives
    printf("Enter name of one relative of the patient:\n>");
    scanf(" %[^\n]", new_patient.relative.name);
    fflush(stdin);
    // Relative phonenumber
    printf("Enter phone number of one relative of the patient:\n>");
    scanf(" %s", new_patient.relative.phone_num);
    fflush(stdin);
    // Relative email
    printf("Enter email of one relative of the patient:\n>");
    scanf(" %s", new_patient.relative.email);
    fflush(stdin);
    // Date
    // Date format

    FILE *pat_reg = fopen("patient_register.csv", "a+");
    if (pat_reg == NULL)
    {
        printf("Error");
        exit(EXIT_FAILURE);
    }
    fprintf(pat_reg, "\n%s,%s,%d,%c,%s,%s,%s,%s,%s,%s,%s,%s",
            new_patient.CPR, new_patient.name, new_patient.age, new_patient.sex, new_patient.phone_num,
            new_patient.address.zip_code, new_patient.address.city, new_patient.address.street_name,
            new_patient.address.house_number_etc, new_patient.relative.name, new_patient.relative.phone_num, new_patient.relative.email);

    // return patient hvis der skal oprettes en referral, ellers ikke
    return new_patient;
}

void review_referral()
{
    // access all referrals - sort either through prioritization or chronologically
    // option to see current time schedule
    // access specific referrals for review
    // create time in an available time slot
}