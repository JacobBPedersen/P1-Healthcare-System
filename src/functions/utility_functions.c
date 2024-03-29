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

//chomp removes newlines
void chomp(char *s) {
    while (*s && *s != '\n' && *s != '\r') {
        s++; // Edited layout after submission
    }
    *s = 0;
}


/************************
 * VALIDATION FUNCTIONS *
 ************************/

/**
 * Validates a CPR number
 * @param cpr The CPR number to be validated
 * @return 0 if the CPR number is valid, 1 if the CPR number is invalid
 */
int cpr_validator(char cpr[CPR_LENGTH]){
    char digits1[6];
    char digits2[4];

    // Check if CPR is correct length
    int is_correct_cpr_length = strlen(cpr) == CPR_LENGTH-1;

    // Check if CPR is correct format and assigned to variables
    if (is_correct_cpr_length && sscanf(cpr, "%6c-%4c", digits1, digits2) == 2 ) {

        // Check if the first 6 digits are digits
        for (int i = 0; i <= 5; ++i) {
            if (!isdigit(digits1[i])) {
                return 1; // Ugyldig CPR
            }
        }

        // Check if the last 4 digits are digits
        for (int i = 0; i <=3; ++i) {
            if (!isdigit(digits2[i])) {
                return 1; // Invalid CPR
            }
        }

        return 0; // Valid CPR
    }

    return 1; // Invalid CPR
}

/**
 * Validates a binary input
 * @param is_num_validation Binary value, 1 if the input is a number, 0 if the input is not a number
 * @param input The input to be validated
 * @return 1 if the input is valid, 0 if the input is invalid
 */
int binary_validation(int is_num_validation, char * input){

    // is_num_validation = 1, if the input is a number
    if (is_num_validation == 1){

        // Check if the input is 0 or 1
        if (strcmp(input,"0") == 0 || strcmp(input,"1") == 0){
            return 1;
        }
        return 0;

    // is_num_validation = 0, if the input is not a number
    }else if (is_num_validation == 0){

        // Check if the input is y or n
        if (strcmp(input,"y") == 0 || strcmp(input,"n") == 0){
            return 1;
        }
        return 0;
    }

return -1;
}

/***
 * Validates an integer
 * @param input The input to be validated
 * @return 1 if the input is valid, 0 if the input is invalid
 */
int int_validation(char *input) {
    // Get the length of the input
    unsigned long char_len = strlen(input);

    // Check every character in the input to see if it is a digit
    for (int i = 0; i < char_len; ++i) {
        if (!isdigit(input[i])) {
            return 0;
        }
    }

    return 1;
}

/**
 * Validates an email
 * @param email The email to be validated
 * @return 1 if the email is valid, 0 if the email is invalid
 */
int email_validation(char *email) {

    int atSymbol = -1, dot = -1;
    int amountOfAtSymbols = 0;
    int len = strlen(email);

    // Count when the @ and . symbols are found
    for (int i = 0; i < len; ++i) {
        if (email[i] == '@') {
            atSymbol = i;
            amountOfAtSymbols++;
        }

        if (email[i] == '.') {
            dot = i;
        }
    }
    // Check if the email is valid based on the position of the @ and . symbols and the amount of @ symbols
    if (atSymbol == -1 || dot == -1 || atSymbol > dot || dot == len - 1 || amountOfAtSymbols > 1) {
        return 0;
    }

    return 1;
}


/********************
 * SEARCH FUNCTIONS *
 ********************/

/**
 * Function to search for the first value in a line in a CSV file.
 * @param first_value
 * @param file
 * @return
 */
char *search_first(char *first_value, FILE *file)
{
    char buffer[BUFFER];

    char return_buffer[BUFFER];
    
    char *token;

    //Loops through each line in the file and stores the current line
    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        strcpy(return_buffer, buffer);
        //Tokenizes the line, separating each value by commas
        token = strtok(buffer, ",");

        //if the first value matches
        if (strcmp(token, first_value) == 0)
        {
            //Returns a duplicate of the found first value
            return strdup(return_buffer);
        }

    }

    return "Value not found";
}

int line_count_file(FILE* fp) {

    char line[BUFFER];
    int amount_ref=0;
    while(fgets(line, BUFFER, fp)) {
        amount_ref++;
    }

    return amount_ref;

}


/*******************
 * PRINT FUNCTIONS *
 *******************/

void print_timetable () {

    char line [BUFFER];

    FILE* fp = fopen("./database/timetable.csv", "r");

    if (fp == NULL) {
        perror("Error opening timetable");
        exit(EXIT_FAILURE);
    }

    while (fgets(line, BUFFER, fp)) {
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
    //Age
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
    //House number etc.
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
    //Referral purpose
    printf("Information of the patient for the referral: %s\n", new_referral.ref_purpose);
    //Language
    printf("There is a language barrier of the patient for the referral: %d\n", new_referral.language_barrier);
    //Language
    if (new_referral.language_barrier == 0) {
        new_referral.language[0] = '-';
    } else {
        printf("Spoken language of the patient for the referral: %s\n", new_referral.language);
    }
}

void print_node(nodelist* list) {
    //reversing the list
    reverse_list(list);
    //Current is used to read through the list
    node* current = list->head;
    // prevday is set to -1 to meet the first if statement, in the first iteration of the while loop
    int prevDay = -1;

    while (current != NULL) {
        //prints the day the first time it is encountered in the list
        if (current->day != prevDay) {
            printf("\n");
            printf("Day %d\nTime: %s  ", current->day, current->time);
        } else {
            // will only print time if the day is the same
            printf("Time: %s  ", current->time);
        }
        //moving the prevday to the current->day and moving the current node one forward
        // until the while loop condition fails with null
        prevDay = current->day;
        current = current->next;
    }
    //restoring the node structure to the initial form
    reverse_list(list);
}


void free_nodelist(nodelist* list) { //Added after submission
    node* temp = list->head;
    while (temp != NULL){
        node* next = temp->next;
        free(temp);
        temp = next;
    }

    list->head = NULL;
}





void print_user_gp (struct GP user) {

    printf("User ID: %s, Name: %s, Title: %s,\nClinic: %s, Phone number: %s\n", user.id, user.name, user.title, user.clinic, user.phone_num);
}

void print_user_hosp (struct hosp_person user) {

    printf("User ID: %s, Name: %s, Title: %s, Location: %s,\nDepartment: %s, Phone number: %s\n", user.id, user.name, user.title, user.location, user.department, user.phone_num);
}