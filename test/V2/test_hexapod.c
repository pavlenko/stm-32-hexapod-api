#include <V2/hexapod.h>
#include <unity.h>
#include <stdio.h>

void test_HP_calculateRotationCenter1() {
    HP_Remote_t remote = {0, 0, 1};
    HP_Status_t status;

    HP_calculateRotationCenter(&remote, &status);

    TEST_ASSERT_EQUAL(0, status.rotateZBy.x);
    TEST_ASSERT_EQUAL(0, status.rotateZBy.y);
}

void test_HP_calculateRotationCenter2() {
    HP_Remote_t remote = {10, 0, 1};
    HP_Status_t status;

    HP_calculateRotationCenter(&remote, &status);

    TEST_ASSERT_EQUAL(0, status.rotateZBy.x);
    TEST_ASSERT_EQUAL(HP_BODY_RADIUS_X4, status.rotateZBy.y);
}

void test_HP_calculateRotationCenter3() {
    HP_Remote_t remote = {0, 10, 1};
    HP_Status_t status;

    HP_calculateRotationCenter(&remote, &status);

    TEST_ASSERT_EQUAL(HP_BODY_RADIUS_X4, status.rotateZBy.x);
    TEST_ASSERT_EQUAL(0, status.rotateZBy.y);
}

void test_HP_calculateRotationCenter4() {
    HP_Remote_t remote = {-5, 10, 1};
    HP_Status_t status;

    HP_calculateRotationCenter(&remote, &status);

    printf("%f; %f\n", status.rotateZBy.x, status.rotateZBy.y);
}


int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_HP_calculateRotationCenter1);
    RUN_TEST(test_HP_calculateRotationCenter2);
    RUN_TEST(test_HP_calculateRotationCenter3);
    RUN_TEST(test_HP_calculateRotationCenter4);
    return UNITY_END();
}