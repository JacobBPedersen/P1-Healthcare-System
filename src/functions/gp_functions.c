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
    while (1){
        if(scanf(" %d", &new_referral.ref_dest) == 1){
            break;
        };
        printf("Destination must be a number. Try again:\n>");
    }
        //Diagnosis category
        printf("Choose the diagnosis category of the referral:\n>");
    while (1){
        if(scanf(" %d", &new_referral.diagnosis_cat) == 1){
            break;
        };
        printf("Diagnosis category must be a number. Try again:\n>");
    }
        //Diagnosis severity
        printf("Choose the diagnosis severity of the referral:\n>");
    while (1){
        if(scanf(" %d", &new_referral.diagnosis_sev) == 1){
            break;
        };
        printf("Diagnosis severity must be a number. Try again:\n>");
    }

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
    printf("Enter the purpose for the referral:\n>");
    scanf(" %[^\n]", new_referral.ref_purpose);
    //Language

    // Der skal promptes med en bool før den kan gå videre
    printf("Acknowledge if there is a language barrier of the patient for the referral (yes: 1, no: 0):\n>");
    while(1){
        if(scanf(" %d", &new_referral.language_barrier) == 1 && (new_referral.language_barrier == 0 || new_referral.language_barrier == 1)){
            break;
        };
        printf("Invalid input. Try again:\n>");
    }

    if (new_referral.language_barrier == 0) {
        new_referral.language[0] = '-';
    } else {
        printf("Enter the spoken language of the patient for the referral:\n>");
        scanf(" %[^\n]", new_referral.language);
    }


    FILE *referrals_documentation = fopen("./database/gp_ref_doc.csv", "a+");
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

    FILE *referrals_send = fopen("./database/hosp_ref_inbox.csv", "a+");
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
    FILE *referrals_send_doc = fopen("./database/hosp_ref_inbox_doc.csv", "a+");
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

    FILE *fp = fopen("./database/gp_patient_register.csv", "r");

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

        printf("\nPatient not found, would you like to create patient? (yes: 1, no: 0)\n> ");

        // While loop for creating patient, and validating user input.
        while (1){

            scanf(" %c",&user_choice);
            clear_buffer();

            // If user want to create a patient
            if (user_choice == '1'){
                // Create patient function
                return create_patient(cpr);
            }else if(user_choice == '0') {
                printf("EXIT PROGRAM");
                exit(1);
            }else{
                printf("\nInvalid input - (yes: 1, no: 0)\n> ");
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



patient create_patient(char* cpr) {

    patient new_patient;
    //CPR
    strcpy(new_patient.CPR, cpr);
    fflush(stdin);
    //Name
    printf("\nEnter name of patient:\n>");
    scanf(" %[^\n]", new_patient.name);
    fflush(stdin);
    //Age
    printf("Enter age of patient:\n>");
    while(1){

        if(scanf("%d", &new_patient.age) == 1){
            break;
        };
        printf("Age must be a number. Try again:\n>");
        fflush(stdin);
    }

    fflush(stdin);
    //Sex
    printf("Enter sex of patient:\n>");
    while(1){
        if(scanf(" %c", &new_patient.sex) == 1 && new_patient.sex == 'f' || new_patient.sex == 'm'){
            break;
        }
        clear_buffer();
        printf("Invalid input, try again (f, m):\n>");
    }
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
    while(1){
        scanf(" %s", new_patient.relative.email);
        if (email_validation(new_patient.relative.email) == 1){
            break;
        }
        printf("Invalid email. Try again:\n>");
        fflush(stdin);
    }

    FILE *pat_reg = fopen("./database/gp_patient_register.csv", "a+");
    if (pat_reg == NULL) {
        printf("Error");
        exit(EXIT_FAILURE);
    }
    fprintf(pat_reg, "\n%s,%s,%d,%c,%s,%s,%s,%s,%s,%s,%s,%s",
            new_patient.CPR, new_patient.name, new_patient.age, new_patient.sex, new_patient.phone_num,
            new_patient.address.zip_code, new_patient.address.city, new_patient.address.street_name,
            new_patient.address.house_number_etc, new_patient.relative.name, new_patient.relative.phone_num,
            new_patient.relative.email);


    return new_patient;
}


int edit_patient_info() {

    char line[MAX_LINE_LENGTH];
    char cpr[13];
    int found = 0;



    patient return_patient = search_patient();

    char target_cpr[13];
    strcpy(target_cpr, return_patient.CPR);

    int cond = 1;
    while (cond == 1) {
        int choice;
        printf("\nWhat do you want to edit (1: Name, 2: Age, 3: Sex, 4: Phone number, 5: Zip-code,\n"
               "6: City, 7: Street name, 8: House number, 9: Relative name, 10: Relative phone number,\n"
               "11: Relative email\n"
               "\nTo exit editing mode, input '-1'\n>");
        while(1){
            if(scanf(" %d", &choice) == 1){
                break;
            };
            printf("Invalid input. Try again:\n>");
            clear_buffer();
        }

        switch (choice) {
            case 1:
                printf("\nEnter name:\n>");
                scanf(" %s", return_patient.name);
                break;
            case 2:
                printf("\nEnter age:\n>");
                while(1){

                    if(scanf("%d", &return_patient.age) == 1){
                        break;
                    };
                    printf("Age must be a number. Try again:\n>");
                    fflush(stdin);
                }
                break;
            case 3:
                printf("Enter sex:\n>");
                while(1){
                    scanf(" %c", &return_patient.sex);
                    if(return_patient.sex == 'f' || return_patient.sex == 'm'){
                        break;
                    }
                    printf("Invalid input, try again (f, m):\n>");
                }
                break;
            case 4:
                printf("\nEnter phone number:\n>");
                scanf(" %s", return_patient.phone_num);
                break;
            case 5:
                printf("\nEnter zip code:\n>");
                scanf(" %s", return_patient.address.zip_code);
                break;
            case 6:
                printf("\nEnter city:\n>");
                scanf(" %s", return_patient.address.city);
                break;
            case 7:
                printf("\nEnter street name:\n>");
                scanf(" %s", return_patient.address.street_name);
                break;
            case 8:
                printf("\nEnter house number etc:\n>");
                scanf(" %s", return_patient.address.house_number_etc);
                break;
            case 9:
                printf("\nEnter name of relative:\n>");
                scanf(" %s", return_patient.relative.name);
                break;
            case 10:
                printf("\nEnter phone number of relative:\n>");
                scanf(" %s", return_patient.relative.phone_num);
                break;
            case 11:
                printf("\nEnter email of relative:\n>");
                while(1){
                    scanf(" %s", return_patient.relative.email);
                    if (email_validation(return_patient.relative.email) == 1){
                        break;
                    }
                    printf("Invalid email. Try again:\n>");
                    fflush(stdin);
                }
                break;
            case -1:
                cond = 0;
                break;
            default:
                printf("\nInvalid input\n");
                break;
        }

    }


    FILE *srcFile = fopen("./database/gp_patient_register.csv", "r");
    FILE *destFile = fopen("./database/temp_patient_register.csv", "w");
    if (!srcFile || !destFile) {
        perror("\nError opening the files\n");
        return -1;
    }

    while (fgets(line, MAX_LINE_LENGTH, srcFile)) {
        chomp(line);
        sscanf(line, "%[^,]", cpr);
        if(strcmp(target_cpr, cpr) == 0) {
            sprintf(line, "%s,%s,%d,%c,%s,%s,%s,%s,%s,%s,%s,%s", return_patient.CPR, return_patient.name,
                    return_patient.age,
                    return_patient.sex, return_patient.phone_num, return_patient.address.zip_code,
                    return_patient.address.city,
                    return_patient.address.street_name, return_patient.address.house_number_etc,
                    return_patient.relative.name, return_patient.relative.phone_num, return_patient.relative.email);
            fprintf(destFile, "\n%s", line);
            found = 1;
        } else if (strcmp(cpr, "CPR") == 0) {
            fprintf(destFile, "%s", line);
        } else {
            fprintf(destFile, "\n%s", line);
        }
    }


    fclose(srcFile);
    fclose(destFile);

    if (!found) {
        printf("\nCPR %s not found\n", target_cpr);
        remove("./database/temp_patient_register.csv");
        return -1;
    } else {
        printf("\nEdit complete.\n");
        remove("./database/gp_patient_register.csv");
        rename("./database/temp_patient_register.csv", "./database/gp_patient_register.csv");
    }

    return 0;


}


int ref_id_create() {

    char line[TEST];

    FILE *referrals_documentation = fopen("./database/hosp_ref_inbox_doc.csv", "r");
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


    int ref_id;
    sscanf(line, "%d", &ref_id);


    return ref_id;


}
