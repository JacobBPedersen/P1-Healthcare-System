#include <assert.h>
#include <functions.h>

void test_create_patient() {

    FILE *create_patient_file = freopen("./inputs/create_patient.txt", "r", stdin);

    assert(create_patient_file != NULL && "Failed to open file");

    char * test_cpr = "123456-1234";

    patient test_patient = create_patient(test_cpr);
    fclose(create_patient_file);

    assert(strcmp("Lars Andersen",test_patient.name) == 0);
    assert(45 == test_patient.age);
    assert(strcmp("Odense",test_patient.address.city) == 0);
    assert(strcmp("Sofie Andersen",test_patient.relative.name) == 0);
    assert(strcmp("sofie.andersen@mail.com",test_patient.relative.email) == 0);
}

void test_cpr_validator(){
    int test1 = cpr_validator("333333-3333");
    int test2 = cpr_validator("1234-123456");
    int test3 = cpr_validator("abc");
    int test4 = cpr_validator("909090-9090");
    int test5 = cpr_validator("999999999999");
    int test6 = cpr_validator("!#€%&/()=?`");
    int test7 = cpr_validator("123456.1234");
    int test8 = cpr_validator("012345-1234");

    assert(test1 == 0);
    assert(test2 == 1);
    assert(test3 == 1);
    assert(test4 == 0);
    assert(test5 == 1);
    assert(test6 == 1);
    assert(test7 == 1);
    assert(test8 == 0);

}

void test_binary_validation() {
    int test1 = binary_validation(1,"0");
    int test2 = binary_validation(1,"1");
    int test3 = binary_validation(1,"2");
    int test4 = binary_validation(1,"999");
    int test5 = binary_validation(0,"abc");
    int test6 = binary_validation(0,"æøå");
    int test7 = binary_validation(0,"0");
    int test8 = binary_validation(0,"1");
    int test9 = binary_validation(0,"y");
    int test10 = binary_validation(0,"n");
    int test11 = binary_validation(0,"Y");
    int test12 = binary_validation(2,"0");


    assert(test1 == 1);
    assert(test2 == 1);
    assert(test3 == 0);
    assert(test4 == 0);
    assert(test5 == 0);
    assert(test6 == 0);
    assert(test7 == 0);
    assert(test8 == 0);
    assert(test9 == 1);
    assert(test10 == 1);
    assert(test11 == 0);
    assert(test12 == -1);

}

void test_int_validation(){

    int test1 = int_validation("0");
    int test2 = int_validation("1");
    int test3 = int_validation("2");
    int test4 = int_validation("999");
    int test5 = int_validation("abc");
    int test6 = int_validation("æøå");

    assert(test1 == 1);
    assert(test2 == 1);
    assert(test3 == 1);
    assert(test4 == 1);
    assert(test5 == 0);
    assert(test6 == 0);
}

void test_email_validation(){
    int test1 = email_validation("example@example.com");
    int test2 = email_validation("example@example");
    int test3 = email_validation("exampleexample.com");
    int test4 = email_validation("exampleexamplecom");
    int test5 = email_validation("123");
    int test6 = email_validation("123@123.dk");
    int test7 = email_validation("email@mail.123");
    int test8 = email_validation("email@email.");
    int test9 = email_validation("email@@@mail@@.com");

    assert(test1 == 1);
    assert(test2 == 0);
    assert(test3 == 0);
    assert(test4 == 0);
    assert(test5 == 0);
    assert(test6 == 1);
    assert(test7 == 1);
    assert(test8 == 0);
    assert(test9 == 0);
}

void test_search_first(){
    FILE *gp_usernames = fopen("./database/gp_users.csv","r");

    assert(gp_usernames != NULL && "Failed to open file");

    char* test1 = search_first("1",gp_usernames);
    rewind(gp_usernames);

    char* test2 = search_first("2",gp_usernames);
    rewind(gp_usernames);

    char* test3 = search_first("3",gp_usernames);
    fclose(gp_usernames);

   assert(strcmp("1,Thor Thorsen,Doctor,Alles Laegehus,+4523232323\n",test1) == 0);
   assert(strcmp("2,Bjarne Bjarnsen,Nurse,Alles Laegehus,+4523432343\n",test2) == 0);
   assert(strcmp("3,Niels Nielsen,Secretary,Nordlaege,+4500000000",test3) == 0);

}

void test_GP_USER(){
    if (freopen("./inputs/gp_users.txt", "r", stdin) == NULL) {
        assert(0 && "Failed to open file for gp_users.txt");
    }

    GP test1 = GP_user(); // 1
    GP test2 = GP_user(); // 2
    GP test3 = GP_user(); // 3

    assert(strcmp(test1.name,"Thor Thorsen") == 0);
    assert(strcmp(test2.name,"Bjarne Bjarnsen") == 0);
    assert(strcmp(test3.name,"Niels Nielsen") == 0);
}

void test_hosp_user(){
    if (freopen("./inputs/hosp_user.txt", "r", stdin) == NULL) {
        assert(0 && "Failed to open file for hosp_user.txt");

    }

    hosp_person test1 = hosp_user(); // 1
    hosp_person test2 = hosp_user(); // 4
    hosp_person test3 = hosp_user(); // 6

    assert(strcmp(test1.name,"Lene Lensen") == 0);
    assert(strcmp(test2.name,"Klaus Kristensen") == 0);
    assert(strcmp(test3.name,"Jacob Jensen") == 0);

}

void test_print_node(){

    nodelist test_node_list;

    add_node_timeslot(&test_node_list,0,"1015");

    assert(test_node_list.head->day == 0);
    assert(strcmp(test_node_list.head->time,"1015") == 0);
}


int main(int argc, char **argv) {
    // Check if an argument is provided
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <test_name>\n", argv[0]);
        return 1;
    }

    // Check which test to run based on the command line argument
    if (strcmp(argv[1], "test_create_patient") == 0) {
        test_create_patient();
    } else if (strcmp(argv[1], "test_cpr_validator") == 0) {
        test_cpr_validator();
    } else if (strcmp(argv[1], "test_search_first") == 0) {
        test_search_first();
    } else if (strcmp(argv[1], "test_GP_USER") == 0) {
        test_GP_USER();
    } else if (strcmp(argv[1], "test_hosp_user") == 0) {
        test_hosp_user();
    } else if (strcmp(argv[1], "test_print_node") == 0) {
        test_print_node();
    } else if(strcmp(argv[1], "test_binary_validation") == 0) {
        test_binary_validation();
    } else if(strcmp(argv[1], "test_int_validation") == 0) {
        test_int_validation();
    } else if(strcmp(argv[1], "test_email_validation") == 0) {
        test_email_validation();
    } else {
        fprintf(stderr, "Test '%s' not found.\n", argv[1]);
        return 1;
    }

    return 0;
}
