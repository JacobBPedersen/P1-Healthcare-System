#include "functions.h"

int main()
{
    int GP_or_Hosp;
    GP current_gp;
    hosp_person current_hosp;

    referral new_test = {"333333-3333","Knud Knudsen",25,'f',"+4577777777","9000","Aalborg","Lil knud","10 4.tv","farmand","+4566666666","farmand@gmail.com",2,3,2,"dawd","dwadwdaw","ffdfd","adsc","rfr","dsadrgr",0,"-","Niels Nielsen","Secretary","Nordlaege","+4500000000"};
    //review_referral(new_test);


    //ref_id_create();


    user_cred(&GP_or_Hosp);

    if (GP_or_Hosp == 1) {
        //Funktion til GP program
        current_gp = GP_user();
        GP_main_flow(current_gp);
    } else {
        current_hosp = hosp_user();
        hosp_main_flow(current_hosp);
    }



    //char *test = search_first("333333-3333", patients_file);

    //printf("%s", test);

    return 0;
}