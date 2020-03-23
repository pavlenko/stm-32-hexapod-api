#include <PE_SpiderV2.h>
#include <unity.h>

void test_PE_SpiderV2_calculateLinearNoMove() {
    PE_SpiderV2_Remote_t remote = {0, 0};
    PE_SpiderV2_Moving_t moving;

    PE_SpiderV2_calculateMovingLinear(&remote, &moving);

    TEST_ASSERT_EQUAL(0, moving.moveByX);
    TEST_ASSERT_EQUAL(0, moving.moveByY);
}

void test_PE_SpiderV2_calculateLinearMoveX() {
    PE_SpiderV2_Remote_t remote;
    PE_SpiderV2_Moving_t moving;

    remote = (PE_SpiderV2_Remote_t) {10, 0};
    PE_SpiderV2_calculateMovingLinear(&remote, &moving);

    TEST_ASSERT_EQUAL(1, moving.moveByX);
    TEST_ASSERT_EQUAL(0, moving.moveByY);

    remote = (PE_SpiderV2_Remote_t) {-10, 0};
    PE_SpiderV2_calculateMovingLinear(&remote, &moving);

    TEST_ASSERT_EQUAL(-1, moving.moveByX);
    TEST_ASSERT_EQUAL(0, moving.moveByY);
}

void test_PE_SpiderV2_calculateLinearMoveY() {
    PE_SpiderV2_Remote_t remote;
    PE_SpiderV2_Moving_t moving;

    remote = (PE_SpiderV2_Remote_t) {0, 10};
    PE_SpiderV2_calculateMovingLinear(&remote, &moving);

    TEST_ASSERT_EQUAL(0, moving.moveByX);
    TEST_ASSERT_EQUAL(1, moving.moveByY);

    remote = (PE_SpiderV2_Remote_t) {0, -10};
    PE_SpiderV2_calculateMovingLinear(&remote, &moving);

    TEST_ASSERT_EQUAL(0, moving.moveByX);
    TEST_ASSERT_EQUAL(-1, moving.moveByY);
}

void test_PE_SpiderV2_calculateLinearMoveXY() {
    PE_SpiderV2_Remote_t remote;
    PE_SpiderV2_Moving_t moving;

    remote = (PE_SpiderV2_Remote_t) {10, 10};
    PE_SpiderV2_calculateMovingLinear(&remote, &moving);

    TEST_ASSERT_EQUAL(M_SQRT1_2, moving.moveByX);
    TEST_ASSERT_EQUAL(M_SQRT1_2, moving.moveByY);

    remote = (PE_SpiderV2_Remote_t) {-10, 10};
    PE_SpiderV2_calculateMovingLinear(&remote, &moving);

    TEST_ASSERT_EQUAL(-M_SQRT1_2, moving.moveByX);
    TEST_ASSERT_EQUAL(M_SQRT1_2, moving.moveByY);

    remote = (PE_SpiderV2_Remote_t) {10, -10};
    PE_SpiderV2_calculateMovingLinear(&remote, &moving);

    TEST_ASSERT_EQUAL(M_SQRT1_2, moving.moveByX);
    TEST_ASSERT_EQUAL(-M_SQRT1_2, moving.moveByY);

    remote = (PE_SpiderV2_Remote_t) {-10, -10};
    PE_SpiderV2_calculateMovingLinear(&remote, &moving);

    TEST_ASSERT_EQUAL(-M_SQRT1_2, moving.moveByX);
    TEST_ASSERT_EQUAL(-M_SQRT1_2, moving.moveByY);
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_PE_SpiderV2_calculateLinearNoMove);
    RUN_TEST(test_PE_SpiderV2_calculateLinearMoveX);
    RUN_TEST(test_PE_SpiderV2_calculateLinearMoveY);
    RUN_TEST(test_PE_SpiderV2_calculateLinearMoveXY);
    return UNITY_END();
}
