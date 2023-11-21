#include "functions.h"


typedef struct address {
    char zip_code[4];
    char city[30];
    char street_name[34];
    char house_number_etc[15];

} address;

typedef struct GP {
    char name [40];
    char title [10];
    char clinic [10];
    char phone_num [12];

} GP;

typedef struct relative {
    char name[40];
    char phone_num[12];
    char email [40];

} relative;

typedef struct patient { //Evt. hent info via cpr.
    char CPR[11];
    char name[40];
    // Date format
    int age;
    int sex;
    char phone_num[12];
    address address;
    relative relative;

} patient;


typedef struct referral {
    patient patient;
    int ref_dest;
    int diagnosis_cat;
    char* diagnosis_desc;
    char* short_anamnesis;
    char* results;
    char* res_bact; //Evt. bool.
    char* handicap;
    char* info_given;
    int language_barrier;
    char* language;
    GP GP;
    // char* preference; Evt. ikke anvendelig da de ikke selv skal prioritere.


} referral;


void user_cred() {
    //Takes input as to who is using the program, and what it is supposed to do at the moment

    char username [50];
    //char password [50]; ??????

    printf("Please enter username:\n>");
    scanf(" %s",username);

    //printf("Please enter password:\n>");
    //scanf(" %s",password);


    // evt. return  GP?
}

void search_patient() {
    //searches the register through CPR

    char cpr [11];
    printf("Enter CPR of the patient");
    scanf(" %s", cpr);


}

referral create_referral() {
    //checks if the patient is already registered.
    //if not, a patient is created from scratch with create_patient
    //otherwise only asks for variable data in update_patient
    //saves patient data in the database


    referral new_referral;
    //referral destination
    printf("Enter the destination of the referral:\n>");
    scanf(" %d", &new_referral.ref_dest);
    //Diagnosis category
    printf("Choose the diagnosis category of the referral:\n>");
    scanf(" %d", &new_referral.diagnosis_cat);
    //Diagnosis description
    printf("Enter a description for the diagnosis of the referral:\n>");
    scanf(" %s", new_referral.diagnosis_desc);
    //Short anamnesis
    printf("Write a short anamnesis of the referral:\n>");
    scanf(" %s", new_referral.short_anamnesis);
    //Test results
    printf("Enter the test results for the referral:\n>");
    scanf(" %s", new_referral.results);
    //Resistant bacteria
    printf("Enter resistant bacteria for the referral:\n>");
    scanf(" %s", new_referral.res_bact);
    //Handicap
    printf("Enter handicap(s) of the patient for the referral:\n>");
    scanf(" %s", new_referral.handicap);
    //Information given
    printf("Enter the information of the patient for the referral:\n>");
    scanf(" %s", new_referral.info_given);
    //Language

    // Der skal promptes med en bool før den kan gå videre
    printf("Acknowledge if there is a language barrier of the patient for the referral:\n>");
    scanf(" %d", &new_referral.language_barrier);
    //Language
    printf("Enter the spoken language of the patient for the referral:\n>");
    scanf(" %s", new_referral.language);
    //General practioner

    //  new_referral.GP = GP; Skal være lig med hvad man indtaster ved login

    return new_referral;

}

void print_referral(referral new_referral){


}

patient create_patient() {
    //Henvist til denne funktion hvis patient ikke findes.

    patient new_patient;
    //CPR
    printf("Enter CPR of patient:\n>");
    scanf(" %s", new_patient.CPR);
    //Name
    printf("Enter name of patient:\n>");
    scanf(" %s", new_patient.name);
    //Age - Midlertidlig
    printf("Enter age of patient:\n>");
    scanf(" %d", &new_patient.age);
    //Sex
    printf("Enter sex of patient:\n>");
    scanf(" %d", &new_patient.sex);
    //Phone Number
    printf("Enter phone number of patient:\n>");
    scanf(" %s", new_patient.phone_num);
    //Address
    printf("Enter address of patient:\n>");
    scanf(" %s", new_patient.address);
    //Relatives
    printf("Enter name of one relative of the patient:\n>");
    scanf(" %s", new_patient.relative.name);
    //Relative phonenumber
    printf("Enter phone number of one relative of the patient:\n>");
    scanf(" %s", new_patient.relative.phone_num);
    //Relative email
    printf("Enter email of one relative of the patient:\n>");
    scanf(" %s", new_patient.relative.email);
    //Date
    //Date format

    return new_patient;
}



void review_referral() {
    //access all referrals - sort either through prioritization or chronologically
    //option to see current time schedule
    //access specific referrals for review
    //create time in an available time slot
}