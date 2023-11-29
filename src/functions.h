#ifndef P1_HEALTHCARE_SYSTEM_FUNCTIONS_H
#define P1_HEALTHCARE_SYSTEM_FUNCTIONS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define DETAILS_LENGTH 40
#define PHONE_NUM 12
#define CPR_LENGTH 12

typedef struct address {
    char zip_code[5];
    char city[DETAILS_LENGTH];
    char street_name[DETAILS_LENGTH];
    char house_number_etc[15];
} address;

typedef struct GP {
    char id[DETAILS_LENGTH];
    char name [DETAILS_LENGTH];
    char title [10];
    char clinic [10];
    char phone_num [PHONE_NUM];
} GP;

typedef struct relative {
    char name[DETAILS_LENGTH];
    char phone_num[PHONE_NUM];
    char email [DETAILS_LENGTH];
} relative;

typedef struct patient { //Evt. hent info via cpr.
    char CPR[CPR_LENGTH];
    char name[DETAILS_LENGTH];
    // Date format
    int age;
    char sex;
    char phone_num[PHONE_NUM];
    address address;
    relative relative;
} patient;

typedef struct referral {
    patient patient;
    int ref_dest;
    int diagnosis_cat;
    char diagnosis_desc[100];
    char short_anamnesis[1000];
    char results[500];
    char res_bact[100]; //Evt. bool.
    char handicap[100];
    char ref_purpose[200];
    int language_barrier;
    char language[DETAILS_LENGTH];
    GP GP;
    // char* preference; Evt. ikke anvendelig da de ikke selv skal prioritere.
} referral;


//Prototypes of functions:

char *search_cpr(char *cpr, FILE *file);

GP user_cred();

patient search_patient(FILE *fp);

void create_referral(patient chosen_patient);

void print_referral(referral new_referral);

patient create_patient();

void review_referral();



#endif //P1_HEALTHCARE_SYSTEM_FUNCTIONS_H
