#include <hexapod.h>
#include <unity.h>
#include <stdio.h>

void test_HP_calculateTargetRotateXY1() {
    HP_Moving_t moving = {0, 0, 0, 100, 0};
    HP_Leg_t leg = {0,0,0,10,0,0,0,0,0};

    HP_calculateTargetRotate(&moving, &leg, -10, LEG_MODE_FLOATING);

    TEST_ASSERT(10 < leg.tgt.x)
    TEST_ASSERT(0 > leg.tgt.y)
}

void test_HP_calculateTargetRotateXY2() {
    HP_Moving_t moving = {0, 0, 0, -100, 0};
    HP_Leg_t leg = {0,0,0,10,0,0,0,0,0};

    HP_calculateTargetRotate(&moving, &leg, -10, LEG_MODE_FLOATING);

    TEST_ASSERT(10 > leg.tgt.x)
    TEST_ASSERT(0 < leg.tgt.y)
}

void test_HP_calculateTargetRotateZ() {
    HP_Moving_t moving = {10, 0, 0, 0, 0};
    HP_Leg_t leg = {0,0,0,20, 20, -20};

    leg.tgt = (Point3D_t) {0, 0, 0};
    HP_calculateTargetRotate(&moving, &leg, 0, LEG_MODE_FLOATING);

    TEST_ASSERT_EQUAL(-20, leg.tgt.z);

    leg.tgt = (Point3D_t) {0, 0, 0};
    HP_calculateTargetRotate(&moving, &leg, 0, LEG_MODE_GROUNDED);

    TEST_ASSERT_EQUAL(-30, leg.tgt.z);
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_HP_calculateTargetRotateXY1);
    RUN_TEST(test_HP_calculateTargetRotateXY2);
    RUN_TEST(test_HP_calculateTargetRotateZ);
    return UNITY_END();
}
