#ifndef P1_HEALTHCARE_SYSTEM_FUNCTIONS_H
#define P1_HEALTHCARE_SYSTEM_FUNCTIONS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define CANCER_TREATMENT_TIME_FRAME 14
#define TREATMENT_TIME_FRAME 60
#define DETAILS_LENGTH 40
#define PHONE_NUM 13
#define CPR_LENGTH 12
#define NUMBER_OF_TIMESLOTS 15
#define MAX_LINE_LENGTH 150
#define NUM_TIMES 15
#define BUFFER 400




enum Hospital_nordjyl {Hjoerring = 1, Aalborg, Aalborg_super};
enum Hospital_midtjyl {Aarhus = 4, Horsens, Hammel, Silkeborg, Viborg, Herning, Holstebro, Lemvig, Randers};
enum Hospital_syddan {Broerup = 13, Esbjerg, Grindsted, Aabenraa, Soenderborg, Toender, Kolding,
        Middelfart, Vejle, Odense, Svendborg, Nyborg, Aeroe};
enum Hospital_sjael {Holbaek = 26, Nykoebing_Falster, Naestved, Ringsted, Koege, Roskilde, Slagelse};
enum Hospital_hoved {Amager = 33, Bispenbjerg, Bornholm, Frederiksberg, Gentofte, Herlev, Hvidovre,
        Frederikssund, Hilleroed, Helsingoer, Glostrup};


enum diagnosis{rhino_virus, cough, flue, acute_child_bronchitis, asthma, COPD, pulmonary_clot, cancer};


/***********************
 * STRUCTS FOR PROGRAM *
 ***********************/

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

typedef struct patient {
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
    int ref_id;
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
} referral;

typedef struct return_ref {
    char reason[BUFFER];
    char action[BUFFER];
} return_ref;


/// Struct for linked lists:
typedef struct node{
    int day;
    char time[5];
    struct node* next;
}node;

typedef struct nodelist{
    node* head;
}nodelist;




/****************************
 * PROTOTYPES FOR FUNCTIONS *
 ****************************/


/// Main workflow function prototypes:
void GP_main_flow (GP current_gp);
void hosp_main_flow (hosp_person current_hosp);

/// User credential function prototypes:
void user_cred(int* GP_or_Hosp);
GP GP_user();
hosp_person hosp_user ();

/// Utility function prototypes:
    // Search functions:
char *search_first(char *cpr, FILE *file);
int line_count_file(FILE* fp);
referral search_ref ();
void print_timetable ();
    // String and input manipulation:
void clear_buffer();
void chomp(char *s);
    // Print functions:
void print_referral(referral new_referral);
void print_user_gp (GP user);
void print_user_hosp (hosp_person user);
void print_node(nodelist* list);
    // Input validation / validation function prototypes:
int cpr_validator(char cpr[CPR_LENGTH]);
int int_validation(char *input);
int binary_validation(int is_num_validation, char * input);
int email_validation(char *input);

/// GP function prototypes:
void create_referral(patient chosen_patient, GP current_gp);
patient search_patient();
patient create_patient(char* cpr);
int edit_patient_info();
int ref_id_create();

/// Hospital function prototypes:
void time_node_structure (int days, int ref_id);
void delete_from_inbox (int ref_id);
void reverse_list(nodelist* list);
void add_node_timeslot(nodelist* list, int day, char* time);
node* recommended_timeslot(nodelist list, int days);
int list_counter(node* current);
void review_referral(referral ref);
void time_string(char* full_time, char chosen_time[], int ref_id, int choice);
int time_update (int chosen_day, char chosen_time[], int ref_id, int mode);
referral referral_inbox (int* ref_returned, hosp_person current_hosp);
void return_referral(referral declined_ref, hosp_person current_hosp);
void forward_referral (referral declined_ref, hosp_person current_hosp);
void handle_appointment();
void reschedule_appointment();
    // Sorting function prototypes, utilized by referral_inbox:
void sort_ref (referral* ref_list, int size_of_list, int(*sort_type)(const void *x_ref, const void *y_ref));
int compare_sev (const void *x_ref, const void *y_ref);
int compare_cpr (const void *x_ref, const void *y_ref);
int compare_ref_id (const void *x_ref, const void *y_ref);


#endif //P1_HEALTHCARE_SYSTEM_FUNCTIONS_H
