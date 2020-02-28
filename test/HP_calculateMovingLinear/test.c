#include <hexapod.h>
#include <unity.h>

void test_HP_calculateLinearNoMove() {
    HP_Remote_t remote = {0, 0};
    HP_Moving_t moving;

    HP_calculateMovingLinear(&remote, &moving);

    TEST_ASSERT_EQUAL(0, moving.moveByX);
    TEST_ASSERT_EQUAL(0, moving.moveByY);
}

void test_HP_calculateLinearMoveX() {
    HP_Remote_t remote;
    HP_Moving_t moving;

    remote = (HP_Remote_t) {10, 0};
    HP_calculateMovingLinear(&remote, &moving);

    TEST_ASSERT_EQUAL(1, moving.moveByX);
    TEST_ASSERT_EQUAL(0, moving.moveByY);

    remote = (HP_Remote_t) {-10, 0};
    HP_calculateMovingLinear(&remote, &moving);

    TEST_ASSERT_EQUAL(-1, moving.moveByX);
    TEST_ASSERT_EQUAL(0, moving.moveByY);
}

void test_HP_calculateLinearMoveY() {
    HP_Remote_t remote;
    HP_Moving_t moving;

    remote = (HP_Remote_t) {0, 10};
    HP_calculateMovingLinear(&remote, &moving);

    TEST_ASSERT_EQUAL(0, moving.moveByX);
    TEST_ASSERT_EQUAL(1, moving.moveByY);

    remote = (HP_Remote_t) {0, -10};
    HP_calculateMovingLinear(&remote, &moving);

    TEST_ASSERT_EQUAL(0, moving.moveByX);
    TEST_ASSERT_EQUAL(-1, moving.moveByY);
}

void test_HP_calculateLinearMoveXY() {
    HP_Remote_t remote;
    HP_Moving_t moving;

    remote = (HP_Remote_t) {10, 10};
    HP_calculateMovingLinear(&remote, &moving);

    TEST_ASSERT_EQUAL(M_SQRT1_2, moving.moveByX);
    TEST_ASSERT_EQUAL(M_SQRT1_2, moving.moveByY);

    remote = (HP_Remote_t) {-10, 10};
    HP_calculateMovingLinear(&remote, &moving);

    TEST_ASSERT_EQUAL(-M_SQRT1_2, moving.moveByX);
    TEST_ASSERT_EQUAL(M_SQRT1_2, moving.moveByY);

    remote = (HP_Remote_t) {10, -10};
    HP_calculateMovingLinear(&remote, &moving);

    TEST_ASSERT_EQUAL(M_SQRT1_2, moving.moveByX);
    TEST_ASSERT_EQUAL(-M_SQRT1_2, moving.moveByY);

    remote = (HP_Remote_t) {-10, -10};
    HP_calculateMovingLinear(&remote, &moving);

    TEST_ASSERT_EQUAL(-M_SQRT1_2, moving.moveByX);
    TEST_ASSERT_EQUAL(-M_SQRT1_2, moving.moveByY);
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_HP_calculateLinearNoMove);
    RUN_TEST(test_HP_calculateLinearMoveX);
    RUN_TEST(test_HP_calculateLinearMoveY);
    RUN_TEST(test_HP_calculateLinearMoveXY);
    return UNITY_END();
}
