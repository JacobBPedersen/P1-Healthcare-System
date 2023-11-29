#include "functions.h"


GP user_cred() {
    //Takes input as to who is using the program, and what it is supposed to do at the moment

    int GP_or_Hosp;
    printf("Please enter if GP");
    scanf(" %d", &GP_or_Hosp);

    char id[DETAILS_LENGTH];
    printf("Please enter id:\n>");
    scanf(" %s", id);


    if (GP_or_Hosp == 1) {
        FILE *fp_gp = fopen("GP_usernames.csv", "r");

        if (fp_gp == NULL) {
            printf("Error");
            exit(EXIT_FAILURE);
        }

        char* GP_info = search_cpr(id, fp_gp);

        if (strcmp(GP_info, "value not found") == 0) {
            exit(EXIT_FAILURE);
        } else {
            GP current_gp;
            sscanf(GP_info, "%s,%s,%s,%s,%s", current_gp.id, current_gp.name, current_gp.title,
                   current_gp.clinic, current_gp.phone_num);

            return current_gp;
        }


    }


    if (GP_or_Hosp == 0) {
        FILE *fp_hosp = fopen("hospital_usernames.csv", "r");

        if (fp_hosp == NULL) {
            printf("Error");
            exit(EXIT_FAILURE);
        }

        char* hosp_info = search_cpr(id, fp_hosp);

        if (strcmp(hosp_info, "value not found") == 0) {
            exit(EXIT_FAILURE);
        } else {
            GP current_gp;
            sscanf(hosp_info, "%s,%s,%s,%s,%s", current_gp.id, current_gp.name, current_gp.title,
                   current_gp.clinic, current_gp.phone_num);

            return current_gp;
        }



    }





    //printf("Please enter password:\n>");
    //scanf(" %s",password);

    // evt. return  GP?

    //skal hvis gp returne info om den praktiserende læge så den kan vedgå i henvisningen.
}

patient search_patient(FILE *fp) {
    //searches the register through CPR

    char cpr [CPR_LENGTH];
    printf("Enter CPR of the patient");
    scanf(" %s", cpr);

    //Use search function to find cpr, if not found call ask if patient is to be created.
    char *info = search_cpr(cpr, fp);

    if (strcmp(info, "value not found") == 0) {
        //create_patient();
        exit(EXIT_FAILURE);
    } else {
        patient f_patient;
        sscanf(info, "%s,%s,%d,%c,%s,%s,%s,%s,%s,%s,%s,%s", f_patient.CPR, f_patient.name, &f_patient.age,
               &f_patient.sex, f_patient.phone_num, f_patient.address.zip_code, f_patient.address.city,
               f_patient.address.street_name, f_patient.address.house_number_etc,
               f_patient.relative.name, f_patient.relative.phone_num, f_patient.relative.email);

        return f_patient;
    }


}



void create_referral(patient chosen_patient) {
    //checks if the patient is already registered.
    //if not, a patient is created from scratch with create_patient
    //otherwise only asks for variable data in update_patient
    //saves patient data in the database

    referral new_referral;

    new_referral.patient = chosen_patient;

    //referral destination
    printf("Enter the destination of the referral:\n>");
    scanf(" %d", &new_referral.ref_dest);
    //Diagnosis category
    printf("Choose the diagnosis category of the referral:\n>");
    scanf(" %d", &new_referral.diagnosis_cat);
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
    printf("Acknowledge if there is a language barrier of the patient for the referral:\n>");
    scanf(" %d", &new_referral.language_barrier);
    //Language
    if (new_referral.language_barrier == 0) {
        new_referral.language[0] = '-';
    } else {
        printf("Enter the spoken language of the patient for the referral:\n>");
        scanf(" %[^\n]", new_referral.language);
    }
    //General practioner

    //  new_referral.GP = GP; Skal være lig med hvad man indtaster ved login

    FILE *referrals = fopen("referrals.csv", "a+");
    if (referrals == NULL) {
        printf("Error");
        exit(EXIT_FAILURE);
    }

    fprintf(referrals, "\n%s,%d,%d,%s,%s,%s,%s,%s,%s,%d,%s",
            new_referral.patient.CPR, new_referral.ref_dest, new_referral.diagnosis_cat, new_referral.diagnosis_desc,
            new_referral.short_anamnesis, new_referral.results, new_referral.res_bact, new_referral.handicap,
            new_referral.ref_purpose, new_referral.language_barrier, new_referral.language);

}

void print_referral(referral new_referral){


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


    FILE *pat_reg = fopen("patient_register.csv", "a+");
    if (pat_reg == NULL) {
        printf("Error");
        exit(EXIT_FAILURE);
    }
    fprintf(pat_reg, "\n%s,%s,%d,%c,%s,%s,%s,%s,%s,%s,%s,%s",
            new_patient.CPR, new_patient.name, new_patient.age, new_patient.sex, new_patient.phone_num,
            new_patient.address.zip_code, new_patient.address.city, new_patient.address.street_name,
            new_patient.address.house_number_etc, new_patient.relative.name, new_patient.relative.phone_num, new_patient.relative.email);


    //return patient hvis der skal oprettes en referral, ellers ikke
    return new_patient;
}


void review_referral() {
    //access all referrals - sort either through prioritization or chronologically
    //option to see current time schedule
    //access specific referrals for review
    //create time in an available time slot
}