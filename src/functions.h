#ifndef P1_HEALTHCARE_SYSTEM_FUNCTIONS_H
#define P1_HEALTHCARE_SYSTEM_FUNCTIONS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define DETAILS_LENGTH 40
#define PHONE_NUM 13
#define CPR_LENGTH 12
#define NUMBER_OF_TIMESLOTS 15
//Updating timetable
#define MAX_LINE_LENGTH 150
#define NUM_TIMES 15  // Antallet af tidspunkter i hver linje

typedef struct address {
    char zip_code[5];
    char city[DETAILS_LENGTH];
    char street_name[DETAILS_LENGTH];
    char house_number_etc[15];
} address;

typedef struct GP {
    char id[DETAILS_LENGTH];
    char name [DETAILS_LENGTH];
    char title [DETAILS_LENGTH];
    char clinic [DETAILS_LENGTH];
    char phone_num [PHONE_NUM];
} GP;

typedef struct hosp_person {
    char id[DETAILS_LENGTH];
    char name [DETAILS_LENGTH];
    char title [DETAILS_LENGTH];
    char location [DETAILS_LENGTH];
    char department [DETAILS_LENGTH];
    char phone_num [PHONE_NUM];
} hosp_person;

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
    int diagnosis_sev;
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

typedef struct node{
    int day;
    char time[5];
    struct node* next;
}node;

typedef struct nodelist{
    node* head;
}nodelist;

void add_node_timeslot(nodelist* list, int day, char* time);
void print_node(nodelist* list);






//Prototypes of functions:

char *search_first(char *cpr, FILE *file);

GP GP_user();

hosp_person hosp_user ();

void user_cred(int* GP_or_Hosp);

patient search_patient();

void create_referral(patient chosen_patient, GP current_gp);

void print_referral(referral new_referral);

patient create_patient();

void review_referral(referral ref);

void print_test_personnel_gp (GP user); // test

void print_test_personnel_hosp (hosp_person user);

void clear_buffer();

int time_update (int chosen_day, char chosen_time[]);

int edit_patient_info();

void chomp(char *s);

#endif //P1_HEALTHCARE_SYSTEM_FUNCTIONS_H
