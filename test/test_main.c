#include <assert.h>
#include "../src/functions.h"

void test_create_patient() {
    if (freopen("./inputs/create_patient.txt", "r", stdin) == NULL) {
        perror("Failed to open file");
        return;
    }

    patient test_patient = create_patient();

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

    assert(test1 == 0);
    assert(test2 == 1);
    assert(test3 == 1);
    assert(test4 == 0);
    assert(test5 == 1);
    assert(test6 == 1);

}

int main() {
    test_create_patient();
   test_cpr_validator();

    return 0;
}
