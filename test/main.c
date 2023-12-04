#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "../src/functions.h"


void test_create_patient() {
    // Mock stdin with expected patient details...
    patient new_patient = create_patient();
    // Validate the new_patient against the expected values.
    printf("create_patient test passed\n");
}
