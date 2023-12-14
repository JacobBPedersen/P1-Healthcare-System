#include "functions.h"


/*********************************
 * String and input manipulation *
 *********************************/

void clear_buffer () {

    int ch;
    //This is a loop that continuously calls the getchar() function, which reads the next character from the input buffer.
    // The loop continues until it encounters a newline character '\n' or the end-of-file (EOF) indicator
    // (which would mean there's no more input to read).
    while ((ch = getchar()) != '\n' && ch != EOF);

}

void chomp(char *s) {
    while (*s && *s != '\n' && *s != '\r') s++;
    *s = 0;
}


/************************
 * VALIDATION FUNCTIONS *
 ************************/

int cpr_validator(char cpr[CPR_LENGTH]){
    int digits1, digits2;
    char str[11];

    int is_correct_cpr_length = strlen(cpr) == CPR_LENGTH-1;

    if (is_correct_cpr_length && sscanf(cpr, "%6d-%4d", &digits1, &digits2) == 2 ) {

        sprintf(str, "%d", digits1);
        int lengthOfDigits1 = strlen(str);

        sprintf(str, "%d", digits2);
        int lengthOfDigits2 = strlen(str);

        if (lengthOfDigits1 == 6 && lengthOfDigits2 == 4){
            return 0;
        }
    }

    return 1; // Ugyldig CPR
}


/********************
 * SEARCH FUNCTIONS *
 ********************/


char *search_first(char *cpr, FILE *file) //Kald funktion search first
{
    char buffer[TEST];

    char return_buffer[TEST];
    char *token;

    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        strcpy(return_buffer, buffer);
        token = strtok(buffer, ",");

        if (strcmp(token, cpr) == 0)
        {

            return strdup(return_buffer);
        }

    }

    return "Value not found";
}




int line_count_file(FILE* fp) {

    char line[TEST];
    int amount_ref=0;
    while(fgets(line, TEST, fp)) {
        amount_ref++;
    }

    return amount_ref;

}




/*******************
 * PRINT FUNCTIONS *
 *******************/


void print_timetable () {

    char line [TEST];

    FILE* fp = fopen("./database/timetable.csv", "r");

    if (fp == NULL) {
        perror("Error opening timetable");
        exit(EXIT_FAILURE);
    }

    while (fgets(line, TEST, fp)) {
        printf("%s\n", line);
    }

    fclose(fp);

}


void print_referral(referral new_referral){
    printf("\nReferral ID: %d\n", new_referral.ref_id);
    //CPR
    printf("CPR of patient: %s\n", new_referral.patient.CPR);
    //Name
    printf("Name of patient: %s\n", new_referral.patient.name);
    //Age - Midlertidig
    printf("Age of patient: %d\n", new_referral.patient.age);
    //Sex
    printf("Sex of patient: %c\n", new_referral.patient.sex);
    //Phone Number
    printf("Phone number of patient: %s\n", new_referral.patient.phone_num);
    //Address
    printf("Zip-code of patient: %s\n", new_referral.patient.address.zip_code);
    //Zip-code
    printf("City of patient: %s\n", new_referral.patient.address.city);
    //Street name
    printf("Street name of patient: %s\n", new_referral.patient.address.street_name);
    //House numer etc.
    printf("Enter house number etc. of patient: %s\n", new_referral.patient.address.house_number_etc);
    //Relatives
    printf("Enter name of one relative of the patient: %s\n", new_referral.patient.relative.name);
    //Relative phonenumber
    printf("Enter phone number of one relative of the patient: %s\n", new_referral.patient.relative.phone_num);
    //Relative email
    printf("Enter email of one relative of the patient: %s\n", new_referral.patient.relative.email);
    //referral destination
    printf("Destination of the referral: %d\n", new_referral.ref_dest);
    //Diagnosis category
    printf("Diagnosis category of the referral: %d \n", new_referral.diagnosis_cat);
    //Diagnosis severity
    printf("Diagnosis severity of the referral: %d \n", new_referral.diagnosis_sev);
    //Diagnosis description
    printf("Description for the diagnosis of the referral: %s\n", new_referral.diagnosis_desc);
    //Short anamnesis
    printf("Short anamnesis of the referral: %s\n", new_referral.short_anamnesis);
    //Test results
    printf("Test results for the referral: %s\n", new_referral.results);
    //Resistant bacteria
    printf("Resistant bacteria: %s\n", new_referral.res_bact);
    //Handicap
    printf("Handicap(s) of the patient: %s\n", new_referral.handicap);
    //Information given
    printf("Information of the patient for the referral: %s\n", new_referral.ref_purpose);
    //Language

    // Der skal promptes med en bool før den kan gå videre
    printf("There is a language barrier of the patient for the referral: %d\n", new_referral.language_barrier);
    //Language
    if (new_referral.language_barrier == 0) {
        new_referral.language[0] = '-';
    } else {
        printf("Spoken language of the patient for the referral: %s\n", new_referral.language);
    }
    //General practioner
    //  new_referral.GP = GP; Skal være lig med hvad man indtaster ved login

}


void print_node(nodelist* list) {
    reverse_list(list);

    node* current = list->head;
    int prevDay = -1;

    while (current != NULL) {
        if (current->day != prevDay) {
            printf("\n");
            printf("Day %d\nTime: %s  ", current->day, current->time);
        } else {
            printf("Time: %s  ", current->time);
        }

        prevDay = current->day;
        current = current->next;
    }
    reverse_list(list);
}


void print_user_gp (struct GP user) {

    printf("User ID: %s, Name: %s, Title: %s,\nClinic: %s, Phone number: %s\n", user.id, user.name, user.title, user.clinic, user.phone_num);

}


void print_user_hosp (struct hosp_person user) {

    printf("User ID: %s, Name: %s, Title: %s, Location: %s,\nDepartment: %s, Phone number: %s\n", user.id, user.name, user.title, user.location, user.department, user.phone_num);

}