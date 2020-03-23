#include <PE_SpiderV2.h>
#include <unity.h>

void test_PE_SpiderV2_calculateRotationCenterNoMove() {
    PE_SpiderV2_Remote_t remote;
    PE_SpiderV2_Moving_t moving;

    remote = (PE_SpiderV2_Remote_t) {0, 0, 1};
    PE_SpiderV2_calculateMovingRotate(&remote, &moving);

    TEST_ASSERT_EQUAL(0, moving.rotateZBy.x);
    TEST_ASSERT_EQUAL(0, moving.rotateZBy.y);

    remote = (PE_SpiderV2_Remote_t) {0, 0, -1};
    PE_SpiderV2_calculateMovingRotate(&remote, &moving);

    TEST_ASSERT_EQUAL(0, moving.rotateZBy.x);
    TEST_ASSERT_EQUAL(0, moving.rotateZBy.y);
}

void test_PE_SpiderV2_calculateRotationCenterMoveX() {
    PE_SpiderV2_Remote_t remote;
    PE_SpiderV2_Moving_t moving;

    remote = (PE_SpiderV2_Remote_t) {10, 0, 1};
    PE_SpiderV2_calculateMovingRotate(&remote, &moving);

    TEST_ASSERT_EQUAL(0, moving.rotateZBy.x);
    TEST_ASSERT_EQUAL(PE_SpiderV2_ROTATE_RADIUS, moving.rotateZBy.y);

    remote = (PE_SpiderV2_Remote_t) {10, 0, -1};
    PE_SpiderV2_calculateMovingRotate(&remote, &moving);

    TEST_ASSERT_EQUAL(0, moving.rotateZBy.x);
    TEST_ASSERT_EQUAL(-PE_SpiderV2_ROTATE_RADIUS, moving.rotateZBy.y);
}

void test_PE_SpiderV2_calculateRotationCenterMoveY() {
    PE_SpiderV2_Remote_t remote;
    PE_SpiderV2_Moving_t moving;

    remote = (PE_SpiderV2_Remote_t) {0, 10, 1};
    PE_SpiderV2_calculateMovingRotate(&remote, &moving);

    TEST_ASSERT_EQUAL(PE_SpiderV2_ROTATE_RADIUS, moving.rotateZBy.x);
    TEST_ASSERT_EQUAL(0, moving.rotateZBy.y);

    remote = (PE_SpiderV2_Remote_t) {0, 10, -1};
    PE_SpiderV2_calculateMovingRotate(&remote, &moving);

    TEST_ASSERT_EQUAL(-PE_SpiderV2_ROTATE_RADIUS, moving.rotateZBy.x);
    TEST_ASSERT_EQUAL(0, moving.rotateZBy.y);
}

void test_PE_SpiderV2_calculateRotationCenterMoveXY1() {
    PE_SpiderV2_Remote_t remote;
    PE_SpiderV2_Moving_t moving;

    remote = (PE_SpiderV2_Remote_t) {2, 3, 1};
    PE_SpiderV2_calculateMovingRotate(&remote, &moving);

    TEST_ASSERT(0 < moving.rotateZBy.x)
    TEST_ASSERT(0 > moving.rotateZBy.y)

    remote = (PE_SpiderV2_Remote_t) {2, 3, -1};
    PE_SpiderV2_calculateMovingRotate(&remote, &moving);

    TEST_ASSERT(0 > moving.rotateZBy.x)
    TEST_ASSERT(0 < moving.rotateZBy.y)
}

void test_PE_SpiderV2_calculateRotationCenterMoveXY2() {
    PE_SpiderV2_Remote_t remote;
    PE_SpiderV2_Moving_t moving;

    remote = (PE_SpiderV2_Remote_t) {-2, 3, 1};
    PE_SpiderV2_calculateMovingRotate(&remote, &moving);

    TEST_ASSERT(0 < moving.rotateZBy.x)
    TEST_ASSERT(0 < moving.rotateZBy.y)

    remote = (PE_SpiderV2_Remote_t) {-2, 3, -1};
    PE_SpiderV2_calculateMovingRotate(&remote, &moving);

    TEST_ASSERT(0 > moving.rotateZBy.x)
    TEST_ASSERT(0 > moving.rotateZBy.y)
}

void test_PE_SpiderV2_calculateRotationCenterMoveXY3() {
    PE_SpiderV2_Remote_t remote;
    PE_SpiderV2_Moving_t moving;

    remote = (PE_SpiderV2_Remote_t) {-2, -3, 1};
    PE_SpiderV2_calculateMovingRotate(&remote, &moving);

    TEST_ASSERT(0 < moving.rotateZBy.x)
    TEST_ASSERT(0 > moving.rotateZBy.y)

    remote = (PE_SpiderV2_Remote_t) {-2, -3, -1};
    PE_SpiderV2_calculateMovingRotate(&remote, &moving);

    TEST_ASSERT(0 > moving.rotateZBy.x)
    TEST_ASSERT(0 < moving.rotateZBy.y)
}

void test_PE_SpiderV2_calculateRotationCenterMoveXY4() {
    PE_SpiderV2_Remote_t remote;
    PE_SpiderV2_Moving_t moving;

    remote = (PE_SpiderV2_Remote_t) {2, -3, 1};
    PE_SpiderV2_calculateMovingRotate(&remote, &moving);

    TEST_ASSERT(0 < moving.rotateZBy.x)
    TEST_ASSERT(0 < moving.rotateZBy.y)

    remote = (PE_SpiderV2_Remote_t) {2, -3, -1};
    PE_SpiderV2_calculateMovingRotate(&remote, &moving);

    TEST_ASSERT(0 > moving.rotateZBy.x)
    TEST_ASSERT(0 > moving.rotateZBy.y)
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_PE_SpiderV2_calculateRotationCenterNoMove);
    RUN_TEST(test_PE_SpiderV2_calculateRotationCenterMoveX);
    RUN_TEST(test_PE_SpiderV2_calculateRotationCenterMoveY);
    RUN_TEST(test_PE_SpiderV2_calculateRotationCenterMoveXY1);
    RUN_TEST(test_PE_SpiderV2_calculateRotationCenterMoveXY2);
    RUN_TEST(test_PE_SpiderV2_calculateRotationCenterMoveXY3);
    RUN_TEST(test_PE_SpiderV2_calculateRotationCenterMoveXY4);
    return UNITY_END();
}