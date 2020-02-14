#include <V2/hexapod.h>
#include <unity.h>

void test_HP_calculateRotationCenterNoMove() {
    HP_Remote_t remote;
    HP_Moving_t moving;

    remote = (HP_Remote_t) {0, 0, 1};
    HP_calculateMovingRotate(&remote, &moving);

    TEST_ASSERT_EQUAL(0, moving.rotateZBy.x);
    TEST_ASSERT_EQUAL(0, moving.rotateZBy.y);

    remote = (HP_Remote_t) {0, 0, -1};
    HP_calculateMovingRotate(&remote, &moving);

    TEST_ASSERT_EQUAL(0, moving.rotateZBy.x);
    TEST_ASSERT_EQUAL(0, moving.rotateZBy.y);
}

void test_HP_calculateRotationCenterMoveX() {
    HP_Remote_t remote;
    HP_Moving_t moving;

    remote = (HP_Remote_t) {10, 0, 1};
    HP_calculateMovingRotate(&remote, &moving);

    TEST_ASSERT_EQUAL(0, moving.rotateZBy.x);
    TEST_ASSERT_EQUAL(HP_ROTATE_RADIUS, moving.rotateZBy.y);

    remote = (HP_Remote_t) {10, 0, -1};
    HP_calculateMovingRotate(&remote, &moving);

    TEST_ASSERT_EQUAL(0, moving.rotateZBy.x);
    TEST_ASSERT_EQUAL(-HP_ROTATE_RADIUS, moving.rotateZBy.y);
}

void test_HP_calculateRotationCenterMoveY() {
    HP_Remote_t remote;
    HP_Moving_t moving;

    remote = (HP_Remote_t) {0, 10, 1};
    HP_calculateMovingRotate(&remote, &moving);

    TEST_ASSERT_EQUAL(HP_ROTATE_RADIUS, moving.rotateZBy.x);
    TEST_ASSERT_EQUAL(0, moving.rotateZBy.y);

    remote = (HP_Remote_t) {0, 10, -1};
    HP_calculateMovingRotate(&remote, &moving);

    TEST_ASSERT_EQUAL(-HP_ROTATE_RADIUS, moving.rotateZBy.x);
    TEST_ASSERT_EQUAL(0, moving.rotateZBy.y);
}

void test_HP_calculateRotationCenterMoveXY1() {
    HP_Remote_t remote;
    HP_Moving_t moving;

    remote = (HP_Remote_t) {2, 3, 1};
    HP_calculateMovingRotate(&remote, &moving);

    TEST_ASSERT(0 < moving.rotateZBy.x)
    TEST_ASSERT(0 > moving.rotateZBy.y)

    remote = (HP_Remote_t) {2, 3, -1};
    HP_calculateMovingRotate(&remote, &moving);

    TEST_ASSERT(0 > moving.rotateZBy.x)
    TEST_ASSERT(0 < moving.rotateZBy.y)
}

void test_HP_calculateRotationCenterMoveXY2() {
    HP_Remote_t remote;
    HP_Moving_t moving;

    remote = (HP_Remote_t) {-2, 3, 1};
    HP_calculateMovingRotate(&remote, &moving);

    TEST_ASSERT(0 < moving.rotateZBy.x)
    TEST_ASSERT(0 < moving.rotateZBy.y)

    remote = (HP_Remote_t) {-2, 3, -1};
    HP_calculateMovingRotate(&remote, &moving);

    TEST_ASSERT(0 > moving.rotateZBy.x)
    TEST_ASSERT(0 > moving.rotateZBy.y)
}

void test_HP_calculateRotationCenterMoveXY3() {
    HP_Remote_t remote;
    HP_Moving_t moving;

    remote = (HP_Remote_t) {-2, -3, 1};
    HP_calculateMovingRotate(&remote, &moving);

    TEST_ASSERT(0 < moving.rotateZBy.x)
    TEST_ASSERT(0 > moving.rotateZBy.y)

    remote = (HP_Remote_t) {-2, -3, -1};
    HP_calculateMovingRotate(&remote, &moving);

    TEST_ASSERT(0 > moving.rotateZBy.x)
    TEST_ASSERT(0 < moving.rotateZBy.y)
}

void test_HP_calculateRotationCenterMoveXY4() {
    HP_Remote_t remote;
    HP_Moving_t moving;

    remote = (HP_Remote_t) {2, -3, 1};
    HP_calculateMovingRotate(&remote, &moving);

    TEST_ASSERT(0 < moving.rotateZBy.x)
    TEST_ASSERT(0 < moving.rotateZBy.y)

    remote = (HP_Remote_t) {2, -3, -1};
    HP_calculateMovingRotate(&remote, &moving);

    TEST_ASSERT(0 > moving.rotateZBy.x)
    TEST_ASSERT(0 > moving.rotateZBy.y)
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_HP_calculateRotationCenterNoMove);
    RUN_TEST(test_HP_calculateRotationCenterMoveX);
    RUN_TEST(test_HP_calculateRotationCenterMoveY);
    RUN_TEST(test_HP_calculateRotationCenterMoveXY1);
    RUN_TEST(test_HP_calculateRotationCenterMoveXY2);
    RUN_TEST(test_HP_calculateRotationCenterMoveXY3);
    RUN_TEST(test_HP_calculateRotationCenterMoveXY4);
    return UNITY_END();
}