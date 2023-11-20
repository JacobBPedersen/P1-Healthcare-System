#include "functions.h"


typedef struct address {
    char zip_code[4];
    char city[30];
    char street_name[34];
    char house_number_etc[15];

} address;

typedef struct patient { //Evt. hent info via cpr.
    char CPR[11];
    char name[40];
    // Date format
    int age;
    int sex;
    char phone_num[12];
    address address; // Evt. struct

} patient;


typedef struct referral {
    patient patient;

    int ref_dest;
    int diagnosis_cat;
    char* diagnosis_desc;
    char* short_anamnesis;
    char* results;
    char* res_bact; //Evt. bool.
    //struct til FMK, evt. hent via cpr.
    char* handicap;
    char* info_given;
    //Struct til pårørende;
    int language_barrier;
    char* language;
    //Struct læge, evt. dan via cred.
    // char* preference; Evt. ikke anvendelig da de ikke selv skal prioritere.


} referral;


void user_cred() {
    //Takes input as to who is using the program, and what it is supposed to do at the moment

}

void search_patient() {
    //searches the register through some ID


}

void create_referral() {
    //checks if the patient is already registered.
    //if not, a patient is created from scratch with create_patient
    //otherwise only asks for variable data in update_patient
    //saves patient data in the database


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