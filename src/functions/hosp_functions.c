#include "functions.h"


node* recommended_timeslot(nodelist list, int days) {
    reverse_list(&list);
    int recom_day = 0;
    int number_of_timeslot = list_counter(list.head);
    int day_count[days];


    //initializing the counter to zero
    for (int i = 0; i < days; ++i) {
        day_count[i] = 0;
    }
    //temporary note reading through list
    node *temp = list.head->next;
    //Counting time slots and storing number in day_count
    while (temp != NULL) {
        day_count[temp->day - 1]++;
        temp = temp->next;
    }

    //analysing one side to determine which side has most available time slots
    int lower_accumulator = 0;

    for (int i = 0; i < days / 2; ++i) {
        lower_accumulator += day_count[i];
    }
    //if lower accumulator is larger the first half of the days will be run through to find the first least occupied day
    if (lower_accumulator > number_of_timeslot / 2) {
        for (int i = 0; i < days / 2; ++i) {
            if (day_count[i] > day_count[recom_day]) {
                recom_day = i;
            }
        }
    } else {
        recom_day = days /2;
        for (int i = days / 2; i < days; ++i) {
            if (day_count[i] > day_count[recom_day]) {
                recom_day = i;
            }
        }
    }
    // the list is run through again until the first free time of the recommended day is found and returned
    temp = list.head->next;
    while (temp != NULL) {
        if (temp->day == recom_day+1) {
            return temp;
        }
        temp = temp->next;
    }
    //if no recommended slot is found a null is returned
    return NULL;
}


//recursively counting the nodes
int list_counter(node* current){
    if(current == NULL){
        //When the end is reached the last node is subtracted, as it starts from the head
        return -1;
    }else{
        return 1 + list_counter(current->next);
    }
}

void review_referral(referral ref) {

    printf("\nDo you wish to schedule a timeslot for the patient? (Yes: 1, No: 0)\n"); //access all referrals - sort either through prioritization or chronologically
    char choice = ' ';
    while (1) {
        scanf(" %c", &choice);
        if (choice == '1' || choice == '0') {
            break;
        } else {
            printf("Input '1' or '0'\n");
        }
    }

    if (choice == '1') {

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

void time_node_structure (int days, int ref_id) {
    // Accessing the timetable
    FILE *fp = fopen("./database/timetable.csv", "r");
    if (fp == NULL) {
        printf("File not accessed");
        exit(EXIT_FAILURE);
    }
    //creating an array of 15, which equals the potential free time slots in a day and stores the time in a string
    // and creating the variable day, which is used in reading the day and time slots with 'a' or 'o' in each line
    char time[15][6];
    int day;
    //creating the list and initializing to NULL
    nodelist free_timeslots = {NULL};
    char time_slot_avaliable;
    //fscans one day at a time storing the values in the array time.
    for (int i = 0; i < days; ++i) {
        fscanf(fp, "%d,%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],"
                   "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]", &day, time[0], time[1],
               time[2], time[3], time[4], time[5], time[6], time[7], time[8], time[9], time[10], time[11],
               time[12], time[13], time[14]);
        //the array time is read through for an 'a' - by skipping the first 4 numbers - and checked in an if statement.
        // If the condition holds a node is added to the node list.
        for (int j = 0; j < NUMBER_OF_TIMESLOTS; ++j) {
            sscanf(time[j], "%*4[0-9]%c", &time_slot_avaliable);
            if (time_slot_avaliable == 'a') {
                add_node_timeslot(&free_timeslots, day, time[j]);
            }
        }
    }
    if (free_timeslots.head == NULL) {
        printf("No free timeslots");
        exit(EXIT_FAILURE);
    }
    fclose(fp);
    //printing the free timeslots for user interface
    print_node(&free_timeslots);
    char choice;
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
            time_update(chosen_day, chosen_timeslot, ref_id, 1);
        } else {
            time_update(recomded_time_slot->day, recomded_time_slot->time, ref_id, 1);
        }

    }


}


void add_node_timeslot(nodelist* list, int day, char* time){
    //allocating memory to the new node
    node* new_node = (node*) malloc(sizeof(node));
    if(new_node==NULL){
        printf("\nNo memory\n");
        exit(EXIT_FAILURE);
    }
    //new nodes node pointer is set to what the list is pointing at ensuring the path the list has stored
    new_node->next = list->head;
    //time_range is used to only take the specific time into the node, without the 'a'
    char time_range[5];
    sscanf(time, "%4s",time_range);
    //storing day and time info into the node
    strcpy(new_node->time, time_range);
    new_node->day = day;
    //the list head is updates to point the new node ensuring the integrety of the list
    list->head = new_node;
}

void reverse_list(nodelist* list) {
    node* prev = NULL;
    node* current = list->head;
    node* next = NULL;

    //while loop that reads through the nodes, temporarily storing the pointer and reversing the order.
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    //pointing the list head at the end
    list->head = prev;
}

//The following functions uses an output parameter (pointer array), to deliver one of two versions of a string.
//It is utilized for the time_update function, it is called twice within the function, but the "choice" parameter is either 1 or 0,
//depending on if the goal is to delete an appointment, or allocate an appointment
void time_string(char* full_time, char chosen_time[], int ref_id, int choice) {

    if (choice == 1){
        sprintf(full_time, "%sa", chosen_time);
    } else {
        sprintf(full_time, "%so%d", chosen_time,ref_id);
    }
}

// Function to update a timetable based on the given day and time.
// chosen_day: The day to update.
// chosen_time: The time to be updated.
// ref_id: Referral ID used in formatting the time.
// choice: To determine the formatting of the time string.
// Returns 0 on success, -1 on failure.
int time_update (int chosen_day, char chosen_time[], int ref_id, int choice) {
    FILE *srcFile = fopen("./database/timetable.csv", "r");
    FILE *destFile = fopen("./database/temp_timetable.csv", "w");
    if (!srcFile || !destFile) {
        perror("\nError opening files\n");
        return -1;
    }

    char line[BUFFER];
    int day;
    char times[NUM_TIMES][50];  // Array to hold time slots.
    int found = 0;
    char full_time[DETAILS_LENGTH];

    while (fgets(line, MAX_LINE_LENGTH, srcFile)) {
        // Remove newline characters from the line.
        chomp(line);
        // Parse the line into day and times.
        sscanf(line, "%d,%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,]",
               &day, times[0], times[1], times[2], times[3], times[4], times[5], times[6], times[7], times[8], times[9],
               times[10], times[11], times[12], times[13], times[14]);
        if (day == chosen_day) {
            // Format the time string.
            time_string(full_time, chosen_time, ref_id, choice);
            choice = (choice == 1) ? 0: 1;
            for (int i = 0; i < NUM_TIMES; i++) {
                if (strcmp(times[i], full_time) == 0) {
                    time_string(full_time, chosen_time, ref_id, choice);
                    // Update the time in the array, mark as found and reformat the line.
                    strcpy(times[i], full_time);
                    found = 1;
                    sprintf(line, "%d,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s", day, times[0], times[1], times[2],
                            times[3], times[4], times[5], times[6], times[7], times[8], times[9],
                            times[10], times[11], times[12], times[13], times[14]);
                    break;
                }
            }
        }
        // Printing the line to the destination file, both if altered or not.
        fprintf(destFile, "%s\n", line);
    }

    fclose(srcFile);
    fclose(destFile);

    // Handling the case where the time was not found or already altered.
    if (!found) {
        printf("Day %d and time %s is not found, or already altered.\n", chosen_day, chosen_time);
        remove("./database/temp_timetable.csv");
        return -1;
    } else {
        printf("\nProcedure done\n");
        // Replace the original file with the "temporary" (destination file).
        remove("./database/timetable.csv");
        rename("./database/temp_timetable.csv", "./database/timetable.csv");
    }

    return 0;
}


// Function to "process" referrals in inbox and allow user interaction for managing them.
// ref_returned: Pointer to an integer for tracking if a referral was returned.
// current_hosp: Struct containing information about the current "hospital user".
// Returns a referral struct.
referral referral_inbox(int* ref_returned, hosp_person current_hosp) {

    char line[BUFFER];

    FILE* fp = fopen("./database/hosp_ref_inbox.csv", "r");

    if (fp == NULL) {
        printf("\nError opening file\n");
        exit(EXIT_FAILURE);
    }

    // Function which counts the number of lines (referrals) in the file.
    int amount_ref = line_count_file(fp);

    // Dynamically allocate memory for the array referrals
    referral *array = (referral*)malloc(amount_ref * sizeof(referral));
    if (array == NULL) {
        fprintf(stderr, "\nMemory allocation failed\n");
        fclose(fp);
        exit(EXIT_FAILURE);
    }
    // Rewinding file pointer to the beginning of the file.
    rewind(fp);


    int i = 0;

    // Attain each line via fgets and parse each line of the file into the array of structs (referral).
    while(fgets(line, BUFFER, fp)) {
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
        // Printing all the referrals. Only crucial information.
        for (int j = 0; j < amount_ref; ++j) {
            printf("\nREFERRAL NO. %d", j+1);
            printf("\nREFERRAL ID: %d\tCPR: %s\tNAME: %s\tCATEGORY %d\tSEVERITY %d\n",
                   array[j].ref_id, array[j].patient.CPR, array[j].patient.name,
                   array[j].diagnosis_cat, array[j].diagnosis_sev);
        }

        int target_id;
        int sort_choice;
        int ref_mode;
        printf("\nDo you want to sort referrals?\n1 - Severity\t2 - CPR\t3 - Chronologically (ref ID)\t-1 - Exit"
               "\nDo you want to choose a referral? \nPress 4\n>");
        scanf("%d", &sort_choice);

        switch (sort_choice) {
            case 1:
                sort_ref(array, amount_ref, compare_sev);
                break;
            case 2:
                sort_ref(array, amount_ref, compare_cpr);
                break;
            case 3:
                sort_ref(array, amount_ref, compare_ref_id);
                break;
            case 4:
                // User selecting referral by ID.
                printf("\nChoose by referral ID:\n>");
                scanf(" %d", &target_id);
                for (int j = 0; j < amount_ref; ++j) {
                    if (target_id == array[j].ref_id) {
                        // Printing selected referral and prompt for action.
                        print_referral(array[j]);
                        printf("\nAccept referral for selected patient (1)\n"
                               "Send back referral (2)\nForward referral (3)\nNo action (-1)\n>");
                        while (1) {
                            if (scanf(" %d", &ref_mode) == 1) {
                                break;
                            }
                            printf("Invalid input. Try again:\n>");
                            clear_buffer();
                        }


                        // Initialize referral struct to the selected referral. In order to be able to allocated heap free memory, and still retain specific referral.
                        referral selected_ref = array[j];

                        // Handling the chosen action/mode for the referral.
                        if (ref_mode == 1) {
                            free(array);
                            *ref_returned = 1;
                            return selected_ref;
                        }
                        else if (ref_mode == 2) {
                            free(array);
                            return_referral(selected_ref, current_hosp);
                            delete_from_inbox(selected_ref.ref_id);
                            return (referral){0};
                        }
                        else if (ref_mode == 3) {
                            free(array);
                            forward_referral(selected_ref, current_hosp);
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
                // Exit loop, also freeing memory, this is also done in other "exit" (return) cases.
                free(array);
                return (referral){0};
            default:
                printf("\nInvalid input\n");
        }
    }

}



// Function to compare two referral "objects" in structs based on diagnosis severity (category and correlated severity).
int compare_sev (const void *x_ref, const void *y_ref) {

    // Casting void pointers to referral type for comparison.
    referral* x = (referral*)x_ref;
    referral* y = (referral*)y_ref;

    // First, comparing the categories.
    if (x->diagnosis_cat != y->diagnosis_cat) {
        return (int)y->diagnosis_cat - (int)x->diagnosis_cat; // Type cast to int, to avoid clang-tidy and conversion errors
    }
    // If the categories were not 'not equal', compare the severity instead, since it then determines the order.
    return (int)y->diagnosis_sev - (int)x->diagnosis_sev; // Type cast to int, to avoid clang-tidy and conversion errors

}

// Function to compare two referral "objects" in structs based on patient CPR
int compare_cpr (const void *x_ref, const void *y_ref) {

    referral* x = (referral*)x_ref;
    referral* y = (referral*)y_ref;

//    // Comparing the CPR.
//    if (x->patient.CPR != y->patient.CPR) {
//        // Utilizing string compare to determine order of CPR according to the lexicographical order
//        return strcmp(x->patient.CPR, y->patient.CPR);
//    } else {
//        // Returns 0 if CPR values are identical.
//        return 0;
//    }

    return strcmp(x->patient.CPR, y->patient.CPR);

}

// Function to compare two referral "objects" in structs based on their referral ID.
int compare_ref_id (const void *x_ref, const void *y_ref) {

    referral* x = (referral*)x_ref;
    referral* y = (referral*)y_ref;

    // Comparing the ref id.
    if (x->ref_id != y->ref_id) {
        return (int)y->ref_id - (int)x->ref_id; // Type cast to int, to avoid clang-tidy and conversion errors
    } else {
        // Returns 0 if referral IDs are identical. (which shouldn't occur, since ref_id's are unique)
        return 0;
    }

}

// Function to sort an array of structs with datatype referral
// Utilizes a function pointer as parameter for flexibility.
void sort_ref (referral* ref_list, int size_of_list, int(*sort_type)(const void *x_ref, const void *y_ref)) {
    // Calls qsort with the referral list, size of the list, size of each element, and the comparison function.
    qsort(ref_list, size_of_list, sizeof(referral), sort_type);

}


// Function to delete a specific referral from the inbox file based on a target ID (referral ID).
void delete_from_inbox (int target_id) {

    char line[BUFFER];
    int ref_id = 0;

    FILE* src_file = fopen("./database/hosp_ref_inbox.csv", "r");
    FILE* dest_file = fopen("./database/referrals_send_temp.csv", "w");

    if (src_file == NULL || dest_file == NULL) {
        printf("\nError\n");
        exit(EXIT_FAILURE);
    }

    // Obtain each line from the source file via fgets.
    while(fgets(line, BUFFER, src_file)) {
        sscanf(line, "%d", &ref_id);
        // If the applicable line's ID is not the target ID, print the line to the destination file
        if (target_id != ref_id) {
            fprintf(dest_file, "%s", line);
        }
    }

    fclose(src_file);
    fclose(dest_file);

    // Delete the original inbox file (Source file).
    remove("./database/hosp_ref_inbox.csv");
    // Rename the temporary file (destination file), effectively updating the inbox, deleting the specific referral.
    rename("./database/referrals_send_temp.csv", "./database/hosp_ref_inbox.csv");

}


// Function to forward a "declined" referral to another destination (Hospital for instance).
void forward_referral (referral declined_ref, hosp_person current_hosp) {

    return_ref detail;
    int destination;

    printf("\nEnter destination:\n>");
    // Clearing input buffer
    clear_buffer();
    scanf(" %d", &destination);

    printf("\nWhat are the reason for the forwarding:\n>");
    clear_buffer();
    scanf("%[^\n]", detail.reason);

    printf("\nWhat do you expect from the recipient:\n>");
    clear_buffer();
    scanf("%[^\n]", detail.action);

    // Opening file in append mode to append the forwarded referral.
    FILE* fp = fopen("./database/ref_forwarded.csv", "a+");

    if (fp == NULL) {
        printf("\nError\n");
        exit(EXIT_FAILURE);
    }

    // Printing the referral and "forwarding details" to the file.
    fprintf(fp, "%d,%s,%s,%s,%s,%d,%c,%s,%s,%s,%s,%s,%s,%s,%s,%d,%d,%d,%s,%s,%s,%s,%s,%s,%d,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",
            //Feedback or critique information
            destination, detail.reason, detail.action,
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
            declined_ref.GP.title, declined_ref.GP.clinic, declined_ref.GP.phone_num,
            //Responsible hospital employee
            current_hosp.name, current_hosp.title, current_hosp.department, current_hosp.phone_num);


    fclose(fp);

}

// Function to return a "declined" referral "to the clinic/sender".
void return_referral(referral declined_ref, hosp_person current_hosp) {

    return_ref detail;

    printf("What are the reason for the decline/return:\n>");
    clear_buffer();
    scanf("%[^\n]", detail.reason);

    printf("What recommended action to be carried out:\n>");
    clear_buffer();
    scanf("%[^\n]", detail.action);

    // Opening a file in append mode to append the returned referral.
    FILE *fp = fopen("./database/ref_returned.csv", "a+");

    if (fp == NULL) {
        printf("Error");
        exit(EXIT_FAILURE);
    }

    // Printing the details of the returned referral to the file.
    fprintf(fp, "%s,%s,%s,%s,%d,%c,%s,%s,%s,%s,%s,%s,%s,%s,%d,%d,%d,%s,%s,%s,%s,%s,%s,%d,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",
            //Feedback or critique information
            detail.reason, detail.action,
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
            declined_ref.GP.title, declined_ref.GP.clinic, declined_ref.GP.phone_num,
            //Responsible hospital employee
            current_hosp.name, current_hosp.title, current_hosp.department, current_hosp.phone_num);

    fclose(fp);

}

// Function to handle appointment-related tasks. Seeing a referral, rescheduling an appointment or deleting it.
void handle_appointment () {

    referral found_ref;
    int cond = 1;
    // While loop allowing for ability to continuous handling of appointments.
    while (cond == 1) {
        int mode;
        printf("Select mode\n1 - View referral of appointment\t2 - Reschedule or delete appointment\t-1 - Exit\n>");
        scanf("%d", &mode);

        switch (mode) {
            // Mode 1: Search for and print a referral.
            case 1:
                found_ref = search_ref();
                print_referral(found_ref);
                break;
            case 2:
                // Mode 2: Delete and or reschedule appointment.
                reschedule_appointment();
                break;
            default:
                // Exit the loop, returning to prior mode select.
                cond = 0;
        }
    }

}

// Function to reschedule an appointment.
void reschedule_appointment () {

    int chosen_day;
    char chosen_time[6];

    referral chosen_ref;

    printf("Enter the day of the appointment to be rescheduled:\n>");
    scanf("%d", &chosen_day);
    printf("\nEnter the clock of the appointment to be rescheduled:\n>");
    scanf(" %s", chosen_time);
    // Call function search_ref to retrieve specific referral struct related to the appointment.
    chosen_ref = search_ref();

    // Changing the chosen occupied timeslot for the chosen referral to available.
    time_update (chosen_day, chosen_time, chosen_ref.ref_id, 0);

    int res_choice;
    // Prompt the user to confirm rescheduling and read the input. If no is chosen the appointment is simply left deleted and not rescheduled.
    printf("\nContinue to reschedule?\n1 - Yes\t2 - No\n>");
    scanf("%d", &res_choice);

    if (res_choice == 1) {
        // If reschedule is chosen, the review_referral function carries out the process of scheduling via recommendation or manual chosen timeslot.
        review_referral(chosen_ref);
    } else {
        printf("\nNo rescheduling chosen\n");
    }

}


// Function to search for a specific referral based on its referral ID
// (using search_first and then segmenting string into struct of referral type).
referral search_ref () {

    // Buffer to store the target referral ID.
    char target_id[10];

    FILE* fp = fopen("./database/hosp_ref_inbox_doc.csv", "r");

    if (fp == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    printf("Choose a referral ID:\n>");
    scanf("%s", target_id);

    // Calling search_first retrieving applicable referral as a string.
    char* ref_s = search_first(target_id, fp);

    fclose(fp);

    referral ref;

    // Parsing the found referral string into the referral struct.
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

    // Return the found referral
    return ref;

}