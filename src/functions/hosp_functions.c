#include "functions.h"


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

        delete_from_inbox(ref.ref_id);

    }

}
//option to see current time schedule
//access specific referrals for review
//create time in an available time slot


void time_node_structure (int days, int ref_id) {

    char choice;

    FILE *fp = fopen("./database/timetable.csv", "r");
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





int time_update (int chosen_day, char chosen_time[], int ref_id) {
    FILE *srcFile = fopen("./database/timetable.csv", "r");
    FILE *destFile = fopen("./database/temp_timetable.csv", "w");
    if (!srcFile || !destFile) {
        perror("Error opening files");
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

        if (day == chosen_day) {
            sprintf(full_time, "%sa", chosen_time);
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
        remove("./database/temp_timetable.csv");
        return -1;
    } else {
        printf("\nAppointment made\n");
        remove("./database/timetable.csv");
        rename("./database/temp_timetable.csv", "./database/timetable.csv");
    }

    return 0;
}



referral referral_inbox(int* ref_returned) {

    char line[TEST];

    FILE* fp = fopen("./database/referrals_send.csv", "r");

    if (fp == NULL) {
        printf("Error");
        exit(EXIT_FAILURE);
    }

    int amount_ref = line_count_file(fp);

    // Dynamically allocate memory for referrals
    referral *array = (referral*)malloc(amount_ref * sizeof(referral));
    if (array == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    rewind(fp);

    //referral array[amount_ref+1];
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
        i++;
    }


    fclose(fp);


    *ref_returned = 0;

    while(1) {

        for (int j = 0; j < amount_ref; ++j) {
            printf("\nREFERRAL NO. %d", j+1);
            printf("\nREFERRAL ID: %d\tCPR: %s\tNAME: %s\tCATEGORY %d\tSEVERITY %d\n",
                   array[j].ref_id, array[j].patient.CPR, array[j].patient.name,
                   array[j].diagnosis_cat, array[j].diagnosis_sev);
        }

        int target_id;
        int sort_choice;
        int ref_mode;
        printf("\nDo you want to sort referrals?\n1 - Severity\t2 - Zip Code\t3 - CPR\t4 - Chronologically (ref ID)\t-1 - Exit"
               "\nDo you want to choose a referral? \nPress 5\n>");
        scanf("%d", &sort_choice);

        switch (sort_choice) {
            case 1:
                sort_ref(array, amount_ref, compare_sev);
                break;
            case 2:
                sort_ref(array, amount_ref, compare_zip);
                break;
            case 3:
                sort_ref(array, amount_ref, compare_cpr);
                break;
            case 4:
                sort_ref(array, amount_ref, compare_ref_id);
                break;
            case 5:
                printf("\nChoose by reference ID:\n>");
                scanf(" %d", &target_id);
                for (int j = 0; j < amount_ref; ++j) {
                    if (target_id == array[j].ref_id) {
                        print_referral(array[j]);
                        printf("\nAccept referral for selected patient (1)\n"
                               "Send back referral (2)\nForward referral (3)\nNo action (-1)\n>");
                        scanf("%d", &ref_mode);

                        referral selected_ref = array[j];

                        if (ref_mode == 1) {
                            free(array);
                            *ref_returned = 1;
                            return selected_ref;
                        }
                        else if (ref_mode == 2) {
                            free(array);
                            return_referral(selected_ref);
                            delete_from_inbox(selected_ref.ref_id);
                            return (referral){0};
                        }
                        else if (ref_mode == 3) {
                            free(array);
                            forward_referral(selected_ref);
                            delete_from_inbox(selected_ref.ref_id);
                            return (referral){0};
                        }
                        else {
                            printf("\nInvalid input\n");
                            continue;
                        }
                    }
                }
                printf("\nInvalid input: ID not found\n");
                break;
            case -1:
                free(array);
                return (referral){0};
            default:
                printf("\nInvalid input\n");
        }
    }

}




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


int compare_cpr (const void *x_ref, const void *y_ref) {

    referral* x = (referral*)x_ref;
    referral* y = (referral*)y_ref;

    // Comparing the cpr.
    if (x->patient.CPR != y->patient.CPR) {
        return strcmp(x->patient.CPR, y->patient.CPR); // Utilizing string compare to determine order of CPR.
    } else {
        return 0;
    }

}

int compare_ref_id (const void *x_ref, const void *y_ref) {

    referral* x = (referral*)x_ref;
    referral* y = (referral*)y_ref;

    // Comparing the ref id.
    if (x->ref_id != y->ref_id) {
        return (int)y->ref_id - (int)x->ref_id; // Type cast to int, to avoid clang-tidy and conversion errors
    } else {
        return 0;
    }

}



void sort_ref (referral* ref_list, int size_of_list, int(*sort_type)(const void *x_ref, const void *y_ref)) {

    qsort(ref_list, size_of_list, sizeof(referral), sort_type);

}



void delete_from_inbox (int target_id) {


    char line[TEST];
    int ref_id = 0;

    FILE* src_file = fopen("./database/referrals_send.csv", "r");
    FILE* dest_file = fopen("./database/referrals_send_temp.csv", "w");

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

    remove("./database/referrals_send.csv");
    rename("./database/referrals_send_temp.csv", "./database/referrals_send.csv");


}



void forward_referral (referral declined_ref) {

    return_ref detail;
    int destination;

    printf("Enter destination");
    scanf(" %d", &destination);
    clear_buffer();
    printf("What are the reason for the decline/return:\n>");
    scanf("%s", detail.reason);
    clear_buffer();
    printf("What recommended action to be carried out:\n>");
    scanf("%s", detail.action);
    clear_buffer();


    FILE* fp = fopen("./database/forwarded_referrals", "a+");

    if (fp == NULL) {
        printf("Error");
        exit(EXIT_FAILURE);
    }

    fprintf(fp, "%d,%s,%s,%s,%s,%d,%c,%s,%s,%s,%s,%s,%s,%s,%s,%d,%d,%d,%s,%s,%s,%s,%s,%s,%d,%s,%s,%s,%s,%s\n",
            //Critic
            destination, detail.reason, detail.action,
            //declined_ref.ref_id,
            //patient
            declined_ref.patient.CPR, declined_ref.patient.name, declined_ref.patient.age, declined_ref.patient.sex,
            declined_ref.patient.phone_num,
            //address
            declined_ref.patient.address.zip_code, declined_ref.patient.address.city,
            declined_ref.patient.address.street_name, declined_ref.patient.address.house_number_etc,
            //relative
            declined_ref.patient.relative.name, declined_ref.patient.relative.phone_num, declined_ref.patient.relative.email,
            //referral info
            declined_ref.ref_dest, declined_ref.diagnosis_cat, declined_ref.diagnosis_sev, declined_ref.diagnosis_desc,
            declined_ref.short_anamnesis, declined_ref.results, declined_ref.res_bact, declined_ref.handicap,
            declined_ref.ref_purpose, declined_ref.language_barrier, declined_ref.language, declined_ref.GP.name,
            declined_ref.GP.title, declined_ref.GP.clinic, declined_ref.GP.phone_num);


    fclose(fp);

}


void return_referral(referral declined_ref) {

    return_ref detail;

    printf("What are the reason for the decline/return:\n>");
    scanf("%s", detail.reason);
    clear_buffer();
    printf("What recommended action to be carried out:\n>");
    scanf("%s", detail.action);
    clear_buffer();


    FILE *fp = fopen("./database/returned_referrals", "a+");

    if (fp == NULL) {
        printf("Error");
        exit(EXIT_FAILURE);
    }

    fprintf(fp, "%s,%s,%s,%s,%d,%c,%s,%s,%s,%s,%s,%s,%s,%s,%d,%d,%d,%s,%s,%s,%s,%s,%s,%d,%s,%s,%s,%s,%s\n",
//Critic
            detail.reason, detail.action,
//declined_ref.ref_id,
//patient
            declined_ref.patient.CPR, declined_ref.patient.name, declined_ref.patient.age, declined_ref.patient.sex,
            declined_ref.patient.phone_num,
//address
            declined_ref.patient.address.zip_code, declined_ref.patient.address.city,
            declined_ref.patient.address.street_name, declined_ref.patient.address.house_number_etc,
//relative
            declined_ref.patient.relative.name, declined_ref.patient.relative.phone_num,
            declined_ref.patient.relative.email,
//referral info
            declined_ref.ref_dest, declined_ref.diagnosis_cat, declined_ref.diagnosis_sev, declined_ref.diagnosis_desc,
            declined_ref.short_anamnesis, declined_ref.results, declined_ref.res_bact, declined_ref.handicap,
            declined_ref.ref_purpose, declined_ref.language_barrier, declined_ref.language, declined_ref.GP.name,
            declined_ref.GP.title, declined_ref.GP.clinic, declined_ref.GP.phone_num);

    fclose(fp);

}


void handle_appointment () {

    referral found_ref;
    int cond = 1;
    while (cond == 1) {
        int mode;
        printf("Select mode\n1 - View referral of appointment\t2 - Reschedule or delete appointment\t-1 - Exit\n>");
        scanf("%d", &mode);

        switch (mode) {
            case 1:
                found_ref = search_ref();
                print_referral(found_ref);
                break;
            case 2:
                reschedule_appointment();
                break;
            default:
                cond = 0;
        }
    }

}

void reschedule_appointment () {

    int chosen_day;
    char chosen_time[6];

    referral chosen_ref;

    printf("Enter the day of the appointment to be rescheduled:\n>");
    scanf("%d", &chosen_day);
    printf("\nEnter the clock of the appointment to be rescheduled:\n>");
    scanf(" %s", chosen_time);
    chosen_ref = search_ref();

    time_delete (chosen_day, chosen_time, chosen_ref.ref_id);

    int res_choice;
    printf("\nContinue to reschedule?\n1 - Yes\t2 - No\n>");
    scanf("%d", &res_choice);

    if (res_choice == 1) {
        review_referral(chosen_ref);
    } else {
        printf("\nNo rescheduling chosen\n");
    }

}



referral search_ref () {


    FILE* fp = fopen("./database/referrals_send_doc.csv", "r");
    char target_id[5];
    if (fp == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }


    printf("Choose a referral ID");
    scanf("%s", target_id);

    char* ref_s = search_first(target_id, fp);

    referral ref;

    sscanf(ref_s, "%d,%[^,],%[^,],%d,%c,%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%d,%d,"
                 "%d,%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%d,%[^,],%[^,],%[^,],%[^,],%[^\n]",
           &ref.ref_id,
            //patient
           ref.patient.CPR, ref.patient.name,
           &ref.patient.age, &ref.patient.sex,
           ref.patient.phone_num,
            //address
           ref.patient.address.zip_code, ref.patient.address.city,
           ref.patient.address.street_name, ref.patient.address.house_number_etc,
            //relative
           ref.patient.relative.name, ref.patient.relative.phone_num, ref.patient.relative.email,
            //referral info
           &ref.ref_dest, &ref.diagnosis_cat, &ref.diagnosis_sev, ref.diagnosis_desc,
           ref.short_anamnesis, ref.results, ref.res_bact, ref.handicap,
           ref.ref_purpose, &ref.language_barrier, ref.language, ref.GP.name,
           ref.GP.title, ref.GP.clinic, ref.GP.phone_num);


    return ref;

}



int time_delete (int chosen_day, char chosen_time[], int ref_id) {
    FILE *srcFile = fopen("./database/timetable.csv", "r");
    FILE *destFile = fopen("./database/temp_timetable.csv", "w");
    if (!srcFile || !destFile) {
        perror("Error opening files");
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

        if (day == chosen_day) {
            sprintf(full_time, "%so%d", chosen_time, ref_id);
            for (int i = 0; i < NUM_TIMES; i++) {
                if (strcmp(times[i], full_time) == 0) {
                    sprintf(times[i], "%sa", chosen_time);
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
        printf("Day %d and time %s is not found, or not occupied.\n", chosen_day, chosen_time);
        remove("./database/temp_timetable.csv");
        return -1;
    } else {
        printf("\nAppointment deleted\n");
        remove("./database/timetable.csv");
        rename("./database/temp_timetable.csv", "./database/timetable.csv");
    }

    return 0;
}



//NOTE: Der mangler ordentlig udprint ved reschedule.