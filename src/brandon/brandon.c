#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define DETAILS_LENGTH 40
#define PHONE_NUM 12
#define CPR_LENGTH 12

char *search_cpr(char *first_col, FILE *file) //Kald funktion search first
{
    char buffer[150];

    char return_buffer[150];
    char *token;

    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        strcpy(return_buffer, buffer);
        token = strtok(buffer, ",");

        if (strcmp(token, first_col) == 0)
        {

            fclose(file);
            return strdup(return_buffer);
        }

    }
    return NULL;
}


typedef struct address
{
    char zip_code[5];
    char city[DETAILS_LENGTH];
    char street_name[DETAILS_LENGTH];
    char house_number_etc[15];

} address;

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

int main(){
    FILE *fp = fopen("patient_register.csv","r");

    if (fp == NULL){
        printf("Error opening file");
        return 0;
    }

   patient patient = search_patient(fp);

    printf("%s\n",patient.CPR);
    printf("%s\n",patient.name);
    printf("%d\n",patient.age);
    printf("%s\n",patient.relative.email);


}
