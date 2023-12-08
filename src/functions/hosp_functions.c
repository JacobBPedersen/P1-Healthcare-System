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
