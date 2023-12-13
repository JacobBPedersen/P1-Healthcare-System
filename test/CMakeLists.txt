# Enable testing with CTest
enable_testing()

# Create an executable for your tests
add_executable(test_main test_main.c
)

include_directories(../src/functions/)

# Link the functions library with your test executable
target_link_libraries(test_main functions)

# Add the test executable to CTest
add_test(NAME TestMain COMMAND test_main)



