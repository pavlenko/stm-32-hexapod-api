#include <V2/hexapod.h>
#include <unity.h>
#include <stdio.h>

void test_HP_calculateLinearNoMove() {
    HP_Remote_t remote = {0, 0};
    HP_Status_t status;

    HP_calculateLinear(&remote, &status);

    TEST_ASSERT_EQUAL(0, status.moveByX);
    TEST_ASSERT_EQUAL(0, status.moveByY);
}

void test_HP_calculateLinearMoveX() {
    HP_Remote_t remote;
    HP_Status_t status;

    remote = (HP_Remote_t) {10, 0};
    HP_calculateLinear(&remote, &status);

    TEST_ASSERT_EQUAL(1, status.moveByX);
    TEST_ASSERT_EQUAL(0, status.moveByY);

    remote = (HP_Remote_t) {-10, 0};
    HP_calculateLinear(&remote, &status);

    TEST_ASSERT_EQUAL(-1, status.moveByX);
    TEST_ASSERT_EQUAL(0, status.moveByY);
}

void test_HP_calculateLinearMoveY() {
    HP_Remote_t remote;
    HP_Status_t status;

    remote = (HP_Remote_t) {0, 10};
    HP_calculateLinear(&remote, &status);

    TEST_ASSERT_EQUAL(0, status.moveByX);
    TEST_ASSERT_EQUAL(1, status.moveByY);

    remote = (HP_Remote_t) {0, -10};
    HP_calculateLinear(&remote, &status);

    TEST_ASSERT_EQUAL(0, status.moveByX);
    TEST_ASSERT_EQUAL(-1, status.moveByY);
}

void test_HP_calculateLinear() {
    HP_Remote_t remote = {0, 0, 0};
    HP_Status_t status;

    HP_calculateLinear(&remote, &status);

    printf("%f %f\n", status.moveByX, status.moveByY);
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_HP_calculateLinearNoMove);
    RUN_TEST(test_HP_calculateLinearMoveX);
    RUN_TEST(test_HP_calculateLinearMoveY);
    RUN_TEST(test_HP_calculateLinear);
    return UNITY_END();
}
