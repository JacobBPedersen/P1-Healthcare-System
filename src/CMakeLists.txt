add_library(functions functions.c)

add_executable(P1_Healthcare_System main.c)

target_link_libraries(P1_Healthcare_System functions)