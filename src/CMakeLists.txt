add_library(functions
        functions/user_cred_functions.c
        functions/utility_functions.c
        functions/main_workflow_functions.c
        functions/gp_functions.c
        functions/hosp_functions.c
)

add_executable(P1_Healthcare_System main.c
)

target_link_libraries(P1_Healthcare_System functions)

include_directories(../src/functions)