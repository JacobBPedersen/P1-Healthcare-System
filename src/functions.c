#include "functions.h"

void user_cred(int* GP_or_Hosp) {
    //Takes input as to who is using the program, and what it is supposed to do at the moment
    int invalid_input;
    do {
        invalid_input = 0;
        printf("Please enter if GP (1) or Hospital (0):\n>");
        scanf(" %d", GP_or_Hosp);
        clear_buffer();
        if (*GP_or_Hosp != 0 && *GP_or_Hosp != 1) {
            printf("Please enter a valid input\n");
            invalid_input = 1;
        }

    } while (invalid_input == 1);
}

GP GP_user(){

    do {
        char id[DETAILS_LENGTH];

        printf("Please enter id:\n>");
        scanf(" %s", id);

        FILE *fp_gp = fopen("GP_usernames.csv", "r");

        if (fp_gp == NULL) {
            printf("Error");
            exit(EXIT_FAILURE);
        }

        char *GP_info = search_first(id, fp_gp);
        fclose(fp_gp);

        if (strcmp(GP_info, "Value not found") == 0) {
            printf("\nError user not found.\n");
        } else {
            GP current_gp;
            sscanf(GP_info, "%[^,],%[^,],%[^,],%[^,],%[^\n]", current_gp.id, current_gp.name, current_gp.title,
                   current_gp.clinic, current_gp.phone_num);
            return current_gp;
        }
    } while (1);

}

hosp_person hosp_user (){

    do {

        char id[DETAILS_LENGTH];

        printf("Please enter id:\n>");
        scanf(" %s", id);

        FILE *fp_hosp = fopen("hospital_usernames.csv", "r");

        if (fp_hosp == NULL) {
            printf("Error");
            exit(EXIT_FAILURE);
        }

        char *hosp_info = search_first(id, fp_hosp);
        fclose(fp_hosp);

        if (strcmp(hosp_info, "Value not found") == 0) {
            printf("\nError user not found.\n");
        } else {
            hosp_person current_hosp;
            sscanf(hosp_info, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]", current_hosp.id, current_hosp.name,
                   current_hosp.title, current_hosp.location, current_hosp.department, current_hosp.phone_num);
            return current_hosp;
        }

    } while (1);

}


/**
 * @brief Validates a CPR, in the format of xxxxxx-xxxx.
 * @param cpr A string representing a CPR number.
 * @return Returns 0 if valid, non-zero if invalid.
 */

int cpr_validator(char cpr[CPR_LENGTH]){
    int digits1, digits2;

    if (sscanf(cpr, "%6d-%4d", &digits1, &digits2) == 2 && strlen(cpr) == CPR_LENGTH - 1) {
        return 0;
    }

    return 1;
}

patient search_patient() {

    FILE *fp = fopen("patient_register.csv", "r");

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



int ref_id_create() {

    char line[TEST];

    FILE *referrals_documentation = fopen("referrals_send_doc.csv", "r");
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


    FILE *referrals_documentation = fopen("referrals.csv", "a+");
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

    FILE *referrals_send = fopen("referrals_send.csv", "a+");
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
    FILE *referrals_send_doc = fopen("referrals_send_doc.csv", "a+");
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
            new_patient.address.house_number_etc, new_patient.relative.name, new_patient.relative.phone_num,
            new_patient.relative.email);


    //return patient hvis der skal oprettes en referral, ellers ikke
    return new_patient;
}

node* recommended_timeslot(nodelist list, int days){
    reverse_list(&list);
    int recom_day = 1;
    int number_of_timeslot = list_counter(list.head);
    node* timeslots = (node*) malloc(number_of_timeslot*sizeof(node));
    if(timeslots==NULL){
        printf("Memory allocation failed");
    }
    node* temp = list.head->next;
    //array af tiderne bygges
    for (int i = 0; i < number_of_timeslot; ++i) {
        timeslots[i].day = temp->day;
        strcpy(timeslots[i].time, temp->time);
        timeslots[i].next = NULL;
        temp = temp->next;
    }

    //spredning af tiderne
    if(days == CANCER_TREATMENT_TIME_FRAME){
        int day[CANCER_TREATMENT_TIME_FRAME] ={0};
        //loop der tæller antal tider på dagen
        for (int i = 0; i < number_of_timeslot; ++i) {
            for (int j = 0; j < CANCER_TREATMENT_TIME_FRAME; ++j) {
                if (timeslots[i].day == j + 1) {
                    day[j] += 1;
                }
            }
        }
        //akkumulere tider i to halvdele, hvor den vurdere om det skal være i første uge eller anden uge
        int lower_accumulator = 0, higher_accumulator = 0;
        for (int i = 0; i < CANCER_TREATMENT_TIME_FRAME /2; ++i) {
            lower_accumulator += day[i];
        }
        for (int i = CANCER_TREATMENT_TIME_FRAME/2; i < CANCER_TREATMENT_TIME_FRAME; ++i) {
            higher_accumulator += day[i];
        }
        //Den tager der hvor der er flest tider for at øge flow
        if(lower_accumulator>higher_accumulator){
            //loop der finder den dag, hvor der er flest tider, så der er constant spredning (dette kan ændres)
            for (int i = 0; i < CANCER_TREATMENT_TIME_FRAME/2; ++i) {
                if(day[i]>day[recom_day-1]){
                    recom_day = i+1;
                }
            }
            for (int i = 0; i < number_of_timeslot; ++i) {
                if(timeslots[i].day == recom_day){
                    return &timeslots[i];
                }
            }
        }else {
            //loop der finder den dag, hvor der er flest tider, så der er constant spredning (dette kan ændres)
            for (int i = CANCER_TREATMENT_TIME_FRAME/2; i < CANCER_TREATMENT_TIME_FRAME; ++i) {
                if (day[i] > day[recom_day - 1]) {
                    recom_day = i + 1;
                }
            }
            for (int i = 0; i < number_of_timeslot; ++i) {
                if (timeslots[i].day == recom_day) {
                    return &timeslots[i];
                }
            }
        }
    }else{
        int day[TREATMENT_TIME_FRAME] ={0};
        //loop der tæller antal tider på dagen
        for (int i = 0; i < number_of_timeslot; ++i) {
            for (int j = 0; j < TREATMENT_TIME_FRAME; ++j) {
                if (timeslots[i].day == j + 1) {
                    day[j] += 1;
                    }
                }
            }
            //akkumulere tider i to halvdele, hvor den vurdere om det skal være i første uge eller anden uge
            int lower_accumulator = 0, higher_accumulator = 0;
            for (int i = 0; i < TREATMENT_TIME_FRAME /2; ++i) {
                lower_accumulator += day[i];
            }
            for (int i = TREATMENT_TIME_FRAME/2; i < TREATMENT_TIME_FRAME; ++i) {
                higher_accumulator += day[i];
            }
            //Den tager der hvor der er flest tider for at øge flow
            if(lower_accumulator>higher_accumulator){
                //loop der finder den dag, hvor der er flest tider, så der er constant spredning (dette kan ændres)
                for (int i = 0; i < TREATMENT_TIME_FRAME; ++i) {
                    if(day[i]>day[recom_day-1]){
                        recom_day = i+1;
                    }
                }
                for (int i = 0; i < number_of_timeslot; ++i) {
                    if(timeslots[i].day == recom_day){
                        return &timeslots[i];
                    }
                }
            }else {
                //loop der finder den dag, hvor der er flest tider, så der er constant spredning (dette kan ændres)
                for (int i = TREATMENT_TIME_FRAME/2; i < TREATMENT_TIME_FRAME; ++i) {
                    if (day[i] > day[recom_day - 1]) {
                        recom_day = i + 1;
                    }
                }
                for (int i = 0; i < number_of_timeslot; ++i) {
                    if (timeslots[i].day == recom_day) {
                        return &timeslots[i];
                    }
                }
            }
    }
}


//recursiv optælling af listen
int list_counter(node* current){
    if(current == NULL){
        //hovedet trækkes fra
        return -1;
    }else{
        return 1 + list_counter(current->next);
    }
}

void review_referral(referral ref) {

    printf("\nDo you wish to schedule a timeslot for the patient? (y/n)\n"); //access all referrals - sort either through prioritization or chronologically
    char choice = ' ';
    while (1) {
        scanf(" %c", &choice);
        if (choice == 'y' || choice == 'n') {
            break;
        } else {
            printf("Input 'y' or 'n'\n");
        }
    }

    if (choice == 'y') {

        int days;
        if (ref.diagnosis_cat == cancer) {
            days = CANCER_TREATMENT_TIME_FRAME;
        } else {
            days = TREATMENT_TIME_FRAME;
        }


        time_node_structure(days, ref.ref_id);

//        int chosen_day;
//        char chosen_timeslot[5];
//
//        printf("\nChoose a day:\n>");
//        scanf("%d", &chosen_day);
//        printf("\nChoose a timeslot:\n>");
//        scanf("%4s", chosen_timeslot);
//
//        time_update(chosen_day, chosen_timeslot, ref.ref_id);

        delete_from_inbox(ref.ref_id);

    }

}
//option to see current time schedule
//access specific referrals for review
//create time in an available time slot


void time_node_structure (int days, int ref_id) {

    char choice;

    FILE *fp = fopen("timetable.csv", "r");
    if (fp == NULL) {
        printf("File not accessed");
        exit(EXIT_FAILURE);
    }
    char time[15][6];

    int day;
    nodelist free_timeslots = {NULL};
    char time_slot_avaliable;
    for (int i = 0; i < days; ++i) {
        fscanf(fp, "%d,%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],"
                   "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]", &day, time[0], time[1],
               time[2], time[3], time[4], time[5], time[6], time[7], time[8], time[9], time[10], time[11],
               time[12], time[13], time[14]);

        for (int j = 0; j < NUMBER_OF_TIMESLOTS; ++j) {
            sscanf(time[j], "%*4[0-9]%c", &time_slot_avaliable);
            if (time_slot_avaliable == 'a') {
                add_node_timeslot(&free_timeslots, day, time[j]);
            }
        }
    }
    fclose(fp);
    print_node(&free_timeslots);

    if (ref_id != 0) {
        node *recomded_time_slot = recommended_timeslot(free_timeslots, days);
        printf("\nRecommended timeslot is: Day %d - Time: %s\n", recomded_time_slot->day, recomded_time_slot->time);
        int chosen_day;
        char chosen_timeslot[5];
        printf("If you wish to manually schedule a timeslot press 1, else if you wish to schedule the recommended time press 2\n");
        while (1) {
            scanf(" %c", &choice);
            if (choice == '1' || choice == '2') {
                break;
            } else {
                printf("Input '1' or '2'");
            }
        }
        if (choice == '1') {
            printf("\nChoose a day:\n>");
            scanf("%d", &chosen_day);
            printf("\nChoose a timeslot:\n>");
            scanf("%4s", chosen_timeslot);
            time_update(chosen_day, chosen_timeslot, ref_id);
        } else {
            time_update(recomded_time_slot->day, recomded_time_slot->time, ref_id);
        }

    }


}


node* add_node_timeslot(nodelist* list, int day, char* time){
    node* new_node = (node*) malloc(sizeof(node));
    if(new_node==NULL){
        printf("No memory - goodbye\n");
        exit(EXIT_FAILURE);
    }
    new_node->next = list->head;
    char time_range[5];
    sscanf(time, "%4s",time_range);
    strcpy(new_node->time, time_range);
    new_node->day = day;
    list->head = new_node;
}

void reverse_list(nodelist* list) {
    node* prev = NULL;
    node* current = list->head;
    node* next = NULL;

    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    list->head = prev;
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




void print_test_personnel_gp (struct GP user) {

    printf("%s, %s, %s, %s, %s", user.id, user.name, user.title, user.clinic, user.phone_num);

}

void print_test_personnel_hosp (struct hosp_person user) {

    printf("%s, %s, %s, %s, %s, %s", user.id, user.name, user.title, user.location, user.department, user.phone_num);

}


void chomp(char *s) {
    while (*s && *s != '\n' && *s != '\r') s++;
    *s = 0;
}

int time_update (int chosen_day, char chosen_time[], int ref_id) {
    FILE *srcFile = fopen("timetable.csv", "r");
    FILE *destFile = fopen("temp_timetable.csv", "w");
    if (!srcFile || !destFile) {
        perror("Fejl ved åbning af filer");
        return -1;
    }

    char line[TEST];
    int day;
    char times[NUM_TIMES][50];  // Array til at holde tidspunkterne
    int found = 0;


    while (fgets(line, MAX_LINE_LENGTH, srcFile)) {
        chomp(line);
        sscanf(line, "%d,%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,]", //Forsøg at fjerne denne if.
                   &day, times[0], times[1], times[2], times[3], times[4], times[5], times[6], times[7], times[8], times[9],
                   times[10], times[11], times[12], times[13], times[14]);
        char full_time[7];
        sprintf(full_time, "%sa", chosen_time);

        if (day == chosen_day) {
            for (int i = 0; i < NUM_TIMES; i++) {
                if (strcmp(times[i], full_time) == 0) {
                    sprintf(times[i], "%so%d", chosen_time, ref_id);
                    found = 1;
                    sprintf(line, "%d,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s", day, times[0], times[1], times[2],
                            times[3], times[4], times[5], times[6], times[7], times[8], times[9],
                            times[10], times[11], times[12], times[13], times[14]); // Opdaterer linjen
                    break; // Stopper ved første match.
                }
            }
        }

        fprintf(destFile, "%s\n", line);
    }

    fclose(srcFile);
    fclose(destFile);

    if (!found) {
        printf("Day %d and time %s is not found, or already occupied.\n", chosen_day, chosen_time);
        remove("temp_timetable.csv");
        return -1;
    } else {
        printf("\nAppointment made\n");
        remove("timetable.csv");
        rename("temp_timetable.csv", "timetable.csv");
    }

    return 0;
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


    FILE *srcFile = fopen("patient_register.csv", "r");
    FILE *destFile = fopen("temp_patient_register.csv", "w");
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


referral referral_inbox(int* ref_returned) {

    char line[TEST];

    FILE* fp = fopen("referrals_send.csv", "r");

    if (fp == NULL) {
        printf("Error");
        exit(EXIT_FAILURE);
    }

    int amount_ref=0;
    while(fgets(line, TEST, fp)) {
        amount_ref++;
    }

    rewind(fp);

    referral array[amount_ref+1];
    int i = 0;


    while(fgets(line, TEST, fp)) {
        sscanf(line, "%d,%[^,],%[^,],%d,%c,%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%d,%d,"
                     "%d,%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%d,%[^,],%[^,],%[^,],%[^,],%[^\n]",
           &array[i].ref_id,
           //patient
           array[i].patient.CPR, array[i].patient.name,
           &array[i].patient.age, &array[i].patient.sex,
           array[i].patient.phone_num,
           //address
           array[i].patient.address.zip_code, array[i].patient.address.city,
           array[i].patient.address.street_name, array[i].patient.address.house_number_etc,
           //relative
           array[i].patient.relative.name, array[i].patient.relative.phone_num, array[i].patient.relative.email,
           //referral info
           &array[i].ref_dest, &array[i].diagnosis_cat, &array[i].diagnosis_sev, array[i].diagnosis_desc,
           array[i].short_anamnesis, array[i].results, array[i].res_bact, array[i].handicap,
           array[i].ref_purpose, &array[i].language_barrier, array[i].language, array[i].GP.name,
           array[i].GP.title, array[i].GP.clinic, array[i].GP.phone_num);
        //printf("\nTEST: %d\n", array[i].ref_id);
        i++;
    }

    fclose(fp);

//    for (int j = 0; j < amount_ref; ++j) {
//        printf("\nREFERRAL NO. %d", j+1);
//        printf("\nCPR: %s\tNAME: %s\tCATEGORY %d\tSEVERITY %d\n",
//               array[j].patient.CPR, array[j].patient.name, array[j].diagnosis_cat, array[j].diagnosis_sev);
//        //print_referral(array[j]);
//
//    }


    int cond = 1;
    while(cond) {

        for (int j = 0; j < amount_ref; ++j) {
            printf("\nREFERRAL NO. %d", j+1);
            printf("\nREFERRAL ID: %d\tCPR: %s\tNAME: %s\tCATEGORY %d\tSEVERITY %d\n",
                   array[j].ref_id, array[j].patient.CPR, array[j].patient.name,
                   array[j].diagnosis_cat, array[j].diagnosis_sev);
            //print_referral(array[j]);

        }

        int target_id;
        int sort_choice;
        int create_ref;
        printf("\nDo you want to sort referrals?\n1 - Severity\t2 - Zip Code\t-1 - Exit"
               "\nDo you want to choose a referral? Press 3\n>");
        scanf("%d", &sort_choice);

        switch (sort_choice) {
            case 1:
                sort_ref(array, amount_ref, compare_sev);
                break;
            case 2:
                sort_ref(array, amount_ref, compare_zip);
                break;
            case 3:
                printf("\nChoose by reference ID:\n>");
                scanf(" %d", &target_id);
                for (int j = 0; j < amount_ref; ++j) {
                    if (target_id == array[j].ref_id) {
                        print_referral(array[j]);
                        printf("\nAccept referral for selected patient (1)\n"
                               "Send back referral (2)\nForward referral (3)\nNo action (-1)\n>");
                        scanf("%d", &create_ref);
                        if (create_ref == 1) {
                            *ref_returned = 1;
                            return array[j];
                        }/* else if (create_ref == 2) {
                            send_back_ref ();
                            break;
                        } else if (create_ref == 3) {
                            forward_ref (); */
                        else {
                            printf("\nInvalid input\n");
                            continue;
                        }
                    }

                }
                printf("\nInvalid input: ID not found\n");
                break;
            case -1:
                //cond = 0;
                return array[0]; //Evt overvej et alternativ
            default:
                printf("\nInvalid input\n");
        }
    }

}

//IKKE SLETTE
//    while(fgets(line, TEST, fp)){
//        printf("\nTEST: %s\n", line);
//    }

//    int amount;
//    printf("\nEnter amount of referrals to be printed\n");
//    scanf("%d", &amount);
//
//
//    for (int i = 0; i < amount; ++i) {
//        fgets(line, TEST, fp);
//        printf("\nTEST: %s\n", line);
//    }


int compare_sev (const void *x_ref, const void *y_ref) {

    referral* x = (referral*)x_ref;
    referral* y = (referral*)y_ref;

    // First, comparing the categories.
    if (x->diagnosis_cat != y->diagnosis_cat) {
        return (int)y->diagnosis_cat - (int)x->diagnosis_cat; // Type cast to int, to avoid clang-tidy and conversion errors
    }
    // If the categories were not 'not equal', compare the severity instead, since it then determines the order.
    return (int)y->diagnosis_sev - (int)x->diagnosis_sev; // Type cast to int, to avoid clang-tidy and conversion errors

}

int compare_zip (const void *x_ref, const void *y_ref) {

    referral* x = (referral*)x_ref;
    referral* y = (referral*)y_ref;

    // Comparing the zip codes.
    if (x->patient.address.zip_code != y->patient.address.zip_code) {
        return strcmp(x->patient.address.zip_code, y->patient.address.zip_code); // Utilizing string compare to determine order of zip codes.
    } else {
       return 0;
    }

}

void sort_ref (referral* ref_list, int size_of_list, int(*sort_type)(const void *x_ref, const void *y_ref)) {

    qsort(ref_list, size_of_list, sizeof(referral), sort_type);

}



void clear_buffer () {

    int ch;
    //This is a loop that continuously calls the getchar() function, which reads the next character from the input buffer.
    // The loop continues until it encounters a newline character '\n' or the end-of-file (EOF) indicator
    // (which would mean there's no more input to read).
    while ((ch = getchar()) != '\n' && ch != EOF);

}



void GP_main_flow (GP current_gp) {

    print_test_personnel_gp(current_gp); // test

    patient current_patient;

    int exit = 1;

    while (exit == 1) {
        int mode_choice_gp;
        printf("\nSelect mode:\n1 - Create Referral\t2 - Create Patient\t3 - Edit Patient\t-1 - Exit\n>");
        scanf("%d", &mode_choice_gp);
        switch (mode_choice_gp) {
            case 1:
                current_patient = search_patient();
                char choice_ref;
                printf("\nDo you want to create a referral for a patient (y/n) Name:%s CPR:%s\n>", current_patient.name,
                       current_patient.CPR);
                scanf(" %c", &choice_ref);
                if (choice_ref != 'y') {
                    break;
                }
                create_referral(current_patient, current_gp);
                printf("Referral created. Do you want to continue (y/n):\n>");
                scanf(" %c", &choice_ref);
                if (choice_ref != 'y') {
                    exit = 0;
                }
                break;
            case 2:
                create_patient();
                break;
            case 3:
                edit_patient_info();
                break;
            case -1:
                exit = 0; //Evt. i stedet for en exit condition for while, så blot return "log out".
                break;
            default:
                printf("Invalid input");
        }
    }


}


void delete_from_inbox (int target_id) {


    char line[TEST];
    int ref_id = 0;

    FILE* src_file = fopen("referrals_send.csv", "r");
    FILE* dest_file = fopen("referrals_send_temp.csv", "w");

    if (src_file == NULL || dest_file == NULL) {
        printf("Error");
        exit(EXIT_FAILURE);
    }

    while(fgets(line, TEST, src_file)) {
        sscanf(line, "%d", &ref_id);
        if (target_id != ref_id) {
            fprintf(dest_file, "%s", line);
        }
    }

    //Overvej fejlkontrol

    fclose(src_file);
    fclose(dest_file);

    remove("referrals_send.csv");
    rename("referrals_send_temp.csv", "referrals_send.csv");


}



void hosp_main_flow (hosp_person current_hosp) {

    print_test_personnel_hosp(current_hosp); // test

    patient current_patient;

    referral current_ref;

    int exit = 1;
    int ref_returned;

    while (exit == 1) {
        int mode_choice_hosp;
        printf("\nSelect mode:\n1 - View Inbox\t2 - View Timetable\t3 - Forward Referral\t-1 - Exit\n>");
        scanf("%d", &mode_choice_hosp);
        clear_buffer();
        switch (mode_choice_hosp) {
            case 1:
                current_ref = referral_inbox(&ref_returned);
                if (ref_returned == 1) {
                    review_referral(current_ref);
                }
                //Når man er i inbox kan man vælge en patient, som fører videre til review referral.
                // (Evt. i forbindelse med print af ref, kunne man printe bare de kritiske elemenenter, når alle printes.
                // EVT. ikke print navn ud til at starte med. Der kan printes alder og sygdom mm. men ikke navn eller
                // andre ting som kan give bias.)
                break;
            case 2:
                printf("\n");
                time_node_structure(TREATMENT_TIME_FRAME, 0);
                printf("\n");
                break;
            //case 3:
                //break;
            case -1:
                exit = 0; //Evt. i stedet for en exit condition for while, så blot return "log out".
                break;
            default:
                printf("Invalid input");
        }
    }


}



//Kirk's Noter
//Forward referral
//Send back

