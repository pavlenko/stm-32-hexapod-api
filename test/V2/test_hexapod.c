#include "../../src/V2/hexapod.h"
#include <unity.h>

//TODO move hardware independent logic to lib dir

void test_function() {
    HP_Remote_t remote = {0, 0, 0};
    HP_Status_t status = {0, {0, 0}};

    HP_calculateRotationCenter(&remote, &status);

    TEST_ASSERT_EQUAL(32, 25+7);
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_function);
    UNITY_END();

    return 0;
}