add_library(functions functions.c
        csv_functions.c)

add_executable(P1_Healthcare_System main.c
        csv_functions.c)

target_link_libraries(P1_Healthcare_System functions)