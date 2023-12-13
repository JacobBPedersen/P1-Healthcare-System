#include <functions.h>

int main()
{
    int GP_or_Hosp;
    GP current_gp;
    hosp_person current_hosp;

    user_cred(&GP_or_Hosp);

    if (GP_or_Hosp == 1) {
        current_gp = GP_user();
        GP_main_flow(current_gp);
    } else {
        current_hosp = hosp_user();
        hosp_main_flow(current_hosp);
    }


    return 0;

}