#include "functions.h"



void create_referral(patient chosen_patient, GP current_gp) {
    //checks if the patient is already registered.
    //if not, a patient is created from scratch with create_patient
    //otherwise only asks for variable data in update_patient
    //saves patient data in the database

    referral new_referral;

    new_referral.patient = chosen_patient;
    new_referral.GP = current_gp;

    //referral destination
    printf("Enter the destination of the referral:\n>");
    scanf(" %d", &new_referral.ref_dest);
    //Diagnosis category
    printf("Choose the diagnosis category of the referral:\n>");
    scanf(" %d", &new_referral.diagnosis_cat);
    //Diagnosis severity
    printf("Choose the diagnosis severity of the referral:\n>");
    scanf(" %d", &new_referral.diagnosis_sev);
    //Diagnosis description
    printf("Enter a description for the diagnosis of the referral:\n>");
    scanf(" %[^\n]", new_referral.diagnosis_desc);
    //Short anamnesis
    printf("Write a short anamnesis of the referral:\n>");
    scanf(" %[^\n]", new_referral.short_anamnesis);
    //Test results
    printf("Enter the test results for the referral:\n>");
    scanf(" %[^\n]", new_referral.results);
    //Resistant bacteria
    printf("Enter resistant bacteria for the referral:\n>");
    scanf(" %[^\n]", new_referral.res_bact);
    //Handicap
    printf("Enter handicap(s) of the patient for the referral:\n>");
    scanf(" %[^\n]", new_referral.handicap);
    //Information given
    printf("Enter the information of the patient for the referral:\n>");
    scanf(" %[^\n]", new_referral.ref_purpose);
    //Language

    // Der skal promptes med en bool før den kan gå videre
    printf("Acknowledge if there is a language barrier of the patient for the referral (yes: 1, no: 0):\n>");
    scanf(" %d", &new_referral.language_barrier);
    //Language
    if (new_referral.language_barrier == 0) {
        new_referral.language[0] = '-';
    } else {
        printf("Enter the spoken language of the patient for the referral:\n>");
        scanf(" %[^\n]", new_referral.language);
    }


    FILE *referrals_documentation = fopen("./database/referrals.csv", "a+");
    if (referrals_documentation == NULL) {
        printf("Error");
        exit(EXIT_FAILURE);
    }

    fprintf(referrals_documentation, "\n%s,%d,%d,%d,%s,%s,%s,%s,%s,%s,%d,%s,%s,%s,%s,%s",
            new_referral.patient.CPR, new_referral.ref_dest, new_referral.diagnosis_cat, new_referral.diagnosis_sev, new_referral.diagnosis_desc,
            new_referral.short_anamnesis, new_referral.results, new_referral.res_bact, new_referral.handicap,
            new_referral.ref_purpose, new_referral.language_barrier, new_referral.language, new_referral.GP.name,
            new_referral.GP.title, new_referral.GP.clinic, new_referral.GP.phone_num);

    fclose(referrals_documentation);


    new_referral.ref_id = ref_id_create()+1;
    printf("TESTLALA");

    FILE *referrals_send = fopen("./database/referrals_send.csv", "a+");
    if (referrals_send == NULL) {
        printf("Error");
        exit(EXIT_FAILURE);
    }

    fprintf(referrals_send, "\n%d,%s,%s,%d,%c,%s,%s,%s,%s,%s,%s,%s,%s,%d,%d,%d,%s,%s,%s,%s,%s,%s,%d,%s,%s,%s,%s,%s",
            new_referral.ref_id,
            //patient
            new_referral.patient.CPR, new_referral.patient.name, new_referral.patient.age, new_referral.patient.sex,
            new_referral.patient.phone_num,
            //address
            new_referral.patient.address.zip_code, new_referral.patient.address.city,
            new_referral.patient.address.street_name, new_referral.patient.address.house_number_etc,
            //relative
            new_referral.patient.relative.name, new_referral.patient.relative.phone_num, new_referral.patient.relative.email,
            //referral info
            new_referral.ref_dest, new_referral.diagnosis_cat, new_referral.diagnosis_sev, new_referral.diagnosis_desc,
            new_referral.short_anamnesis, new_referral.results, new_referral.res_bact, new_referral.handicap,
            new_referral.ref_purpose, new_referral.language_barrier, new_referral.language, new_referral.GP.name,
            new_referral.GP.title, new_referral.GP.clinic, new_referral.GP.phone_num);

    fclose(referrals_send);

    //Foelgende er en inboks for sendte refs. Tiltænkt som at være et lager for hospitalet.
    FILE *referrals_send_doc = fopen("./database/referrals_send_doc.csv", "a+");
    if (referrals_send_doc == NULL) {
        printf("Error");
        exit(EXIT_FAILURE);
    }

    fprintf(referrals_send_doc, "\n%d,%s,%s,%d,%c,%s,%s,%s,%s,%s,%s,%s,%s,%d,%d,%d,%s,%s,%s,%s,%s,%s,%d,%s,%s,%s,%s,%s",
            new_referral.ref_id,
            //patient
            new_referral.patient.CPR, new_referral.patient.name, new_referral.patient.age, new_referral.patient.sex,
            new_referral.patient.phone_num,
            //address
            new_referral.patient.address.zip_code, new_referral.patient.address.city,
            new_referral.patient.address.street_name, new_referral.patient.address.house_number_etc,
            //relative
            new_referral.patient.relative.name, new_referral.patient.relative.phone_num, new_referral.patient.relative.email,
            //referral info
            new_referral.ref_dest, new_referral.diagnosis_cat, new_referral.diagnosis_sev, new_referral.diagnosis_desc,
            new_referral.short_anamnesis, new_referral.results, new_referral.res_bact, new_referral.handicap,
            new_referral.ref_purpose, new_referral.language_barrier, new_referral.language, new_referral.GP.name,
            new_referral.GP.title, new_referral.GP.clinic, new_referral.GP.phone_num);

    fclose(referrals_send_doc);

}



patient search_patient() {

    FILE *fp = fopen("./database/patient_register.csv", "r");

    if(fp == NULL){

        printf("Error");
    }

    char cpr[CPR_LENGTH];

    printf("\nEnter CPR of the patient.\n> ");

    // While loop for inserting and validating cpr number
    while(1){
        scanf("%s", cpr);
        clear_buffer();

        int cpr_match = cpr_validator(cpr);

        if (cpr_match == 0){
            break;
        }

        printf("\nInvalid format for CPR, try again.\n> ");

    }

    // Searches for a valid cpr number in the file register
    char *searched_patient = search_first(cpr, fp);

    fclose(fp);

    // If patients doest exist, create on
    if (strcmp(searched_patient, "Value not found") == 0)
    {

        char user_choice;

        printf("Patient not found, would you like to create patient? Y/n?\n> ");

        // While loop for creating patient, and validating user input.
        while (1){

            scanf(" %c",&user_choice);
            // clear_buffer();

            // If user want to create a patient
            if (user_choice == 'y' || user_choice == 'Y' ){

                // Create patient function
                return create_patient();
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

    // parsing string output from a found/existing
    sscanf(searched_patient, "%[^,],%[^,],%d,%c,%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]"
            , return_patient.CPR, return_patient.name, &return_patient.age,
           &return_patient.sex, return_patient.phone_num, return_patient.address.zip_code, return_patient.address.city,
           return_patient.address.street_name, return_patient.address.house_number_etc,
           return_patient.relative.name, return_patient.relative.phone_num, return_patient.relative.email);


    return return_patient;


}



patient create_patient() {
    //Henvist til denne funktion hvis patient ikke findes.
    patient new_patient;
    //CPR
    printf("Enter CPR of patient:\n>");
    scanf(" %[^\n]", new_patient.CPR);
    fflush(stdin);
    //Name
    printf("Enter name of patient:\n>");
    scanf(" %[^\n]", new_patient.name);
    fflush(stdin);
    //Age - Midlertidig
    printf("Enter age of patient:\n>");
    scanf("%d", &new_patient.age);
    fflush(stdin);
    //Sex
    printf("Enter sex of patient:\n>");
    scanf(" %c", &new_patient.sex);
    fflush(stdin);
    //Phone Number
    printf("Enter phone number of patient:\n>");
    scanf(" %s", new_patient.phone_num);
    fflush(stdin);
    //Address
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
    //Relatives
    printf("Enter name of one relative of the patient:\n>");
    scanf(" %[^\n]", new_patient.relative.name);
    fflush(stdin);
    //Relative phonenumber
    printf("Enter phone number of one relative of the patient:\n>");
    scanf(" %s", new_patient.relative.phone_num);
    fflush(stdin);
    //Relative email
    printf("Enter email of one relative of the patient:\n>");
    scanf(" %s", new_patient.relative.email);
    fflush(stdin);
    //Date
    //Date format


    FILE *pat_reg = fopen("./database/patient_register.csv", "a+");
    if (pat_reg == NULL) {
        printf("Error");
        exit(EXIT_FAILURE);
    }
    fprintf(pat_reg, "\n%s,%s,%d,%c,%s,%s,%s,%s,%s,%s,%s,%s",
            new_patient.CPR, new_patient.name, new_patient.age, new_patient.sex, new_patient.phone_num,
            new_patient.address.zip_code, new_patient.address.city, new_patient.address.street_name,
            new_patient.address.house_number_etc, new_patient.relative.name, new_patient.relative.phone_num,
            new_patient.relative.email);


    //return patient hvis der skal oprettes en referral, ellers ikke
    return new_patient;
}


int edit_patient_info() {

    char line[MAX_LINE_LENGTH];
    char cpr[13];
    int found = 0;

    //patient return_patient = {"333333-3333","Knud Knudsen",25,'f',"+4577777777","9000","Aalborg","Lil knud","10 4.tv","farmand","+4566666666","farmand@gmail.com"};


    patient return_patient = search_patient();

    char target_cpr[13];
    strcpy(target_cpr, return_patient.CPR);

    int cond = 1;
    while (cond == 1) {
        int choice;
        printf("What do you want to edit (1:name, 2:age, 3:sex, 4:phone_number, 5:zip-code,\n"
               "6:city, 7:street_name, 8:house_number, 9:rel_name, 10:rel_phone_number, 11:rel_email\n"
               "For complete edit, write '-1'\n>");
        scanf(" %d", &choice);

        switch (choice) {
            case 1:
                printf("enter name:\n>");
                scanf(" %s", return_patient.name);
                break;
            case 2:
                printf("enter age:\n>");
                scanf(" %d", &return_patient.age);
                break;
            case 3:
                printf("enter sex:\n>");
                scanf(" %c", &return_patient.sex);
                break;
            case 4:
                printf("enter phone number:\n>");
                scanf(" %s", return_patient.phone_num);
                break;
            case 5:
                printf("enter zip code:\n>");
                scanf(" %s", return_patient.address.zip_code);
                break;
            case 6:
                printf("enter city:\n>");
                scanf(" %s", return_patient.address.city);
                break;
            case 7:
                printf("enter street name:\n>");
                scanf(" %s", return_patient.address.street_name);
                break;
            case 8:
                printf("enter house number etc:\n>");
                scanf(" %s", return_patient.address.house_number_etc);
                break;
            case 9:
                printf("enter name of relative:\n>");
                scanf(" %s", return_patient.relative.name);
                break;
            case 10:
                printf("enter phone number of relative:\n>");
                scanf(" %s", return_patient.relative.phone_num);
                break;
            case 11:
                printf("enter email of relative:\n>");
                scanf(" %s", return_patient.relative.email);
                break;
            case -1:
                cond = 0;
                break;
            default:
                printf("\nInvalid input\n");
                break;
        }

    }


    FILE *srcFile = fopen("./database/patient_register.csv", "r");
    FILE *destFile = fopen("./database/temp_patient_register.csv", "w");
    if (!srcFile || !destFile) {
        perror("Fejl ved åbning af filer");
        return -1;
    }

    while (fgets(line, MAX_LINE_LENGTH, srcFile)) {
        chomp(line);
        sscanf(line, "%[^,]", cpr);
        //printf("\nTest cpr: %s", cpr);
        if(strcmp(target_cpr, cpr) == 0) {
            sprintf(line, "%s,%s,%d,%c,%s,%s,%s,%s,%s,%s,%s,%s", return_patient.CPR, return_patient.name,
                    return_patient.age,
                    return_patient.sex, return_patient.phone_num, return_patient.address.zip_code,
                    return_patient.address.city,
                    return_patient.address.street_name, return_patient.address.house_number_etc,
                    return_patient.relative.name, return_patient.relative.phone_num, return_patient.relative.email);
            //fseek(destFile, -strlen(line), SEEK_CUR);
            fprintf(destFile, "\n%s", line);
            found = 1;
        } else if (strcmp(cpr, "CPR") == 0) {
            fprintf(destFile, "%s", line);
        } else {
            fprintf(destFile, "\n%s", line);
        }
    }

    //SKAL TESTES SENERE

//    // Move to the end of the file
//    fseek(destFile, 0, SEEK_END);
//    int fileSize = ftell(destFile);
//    printf("TEST: %d", fileSize);
//
//    // Check and remove newline
//    fseek(destFile, -1, SEEK_END); // Go back one character
//    if (fgetc(destFile) == '\n') {
//        fseek(destFile, -1, SEEK_END);
//        ftruncate(fileno(destFile), fileSize - 1);
//    }



// Get the file descriptor
//    int fd = _fileno(destFile);
//
//    // Find the size of the file
//    fseek(destFile, 0, SEEK_END);
//    long fileSize = ftell(destFile);
//
//    // Check the last character
//    fseek(destFile, -1, SEEK_END);
//    int lastChar = fgetc(destFile);
//    if (lastChar == '\n') {
//        // Resize the file to remove the last character
//        if (_chsize(fd, fileSize - 1) != 0) {
//            perror("Error truncating file");
//            fclose(destFile);
//            return -1;
//        }
//    }



    fclose(srcFile);
    fclose(destFile);

    if (!found) {
        printf("CPR %s not found", target_cpr);
        remove("temp_patient_register.csv");
        return -1;
    } else {
        printf("\nEdit complete.\n");
        remove("patient_register.csv");
        rename("temp_patient_register.csv", "patient_register.csv");
    }

    return 0;


}


int ref_id_create() {

    char line[TEST];

    FILE *referrals_documentation = fopen("./database/referrals_send_doc.csv", "r");
    if (referrals_documentation == NULL) {
        printf("Error");
        exit(EXIT_FAILURE);
    }


    int i = 0;
    while (fseek(referrals_documentation, i, SEEK_END) == 0) {
        if (fgetc(referrals_documentation) == '\n') {
            break;
        }
        i--;
    }

    if (fgets(line, TEST, referrals_documentation) == NULL) {
        printf("Error");
        return 1;
    }

    fclose(referrals_documentation);

    printf("\nTEST: %s\n", line);

    int ref_id;
    sscanf(line, "%d", &ref_id);

    printf("\nTest: %d", ref_id);

    return ref_id;


}
