enable_testing()

add_executable(test_main test_main.c)

target_link_libraries(test_main functions)
include_directories(../src/functions)

file(COPY ${CMAKE_SOURCE_DIR}/test/inputs/ DESTINATION ${CMAKE_BINARY_DIR}/test/inputs)
file(COPY ${CMAKE_SOURCE_DIR}/test/database/ DESTINATION ${CMAKE_BINARY_DIR}/test/database)

add_test(NAME TestCreatePatient COMMAND test_main test_create_patient)
add_test(NAME TestCprValidator COMMAND test_main test_cpr_validator)
add_test(NAME TestSearchFirst COMMAND test_main test_search_first)
add_test(NAME TestGPUSER COMMAND test_main test_GP_USER)
add_test(NAME TestHospUser COMMAND test_main test_hosp_user)
add_test(NAME TestSearchPatient COMMAND test_main test_search_patient)
add_test(NAME TestAddNodeTimeslot COMMAND test_main test_add_node_timeslot)
add_test(NAME TestPrintNode COMMAND test_main test_print_node)

