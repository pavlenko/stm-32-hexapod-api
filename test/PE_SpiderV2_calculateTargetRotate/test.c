#include <PE_SpiderV2.h>
#include <unity.h>
#include <stdio.h>

void test_PE_SpiderV2_calculateTargetRotateXY1() {
    PE_SpiderV2_Moving_t moving = {0, 0, 0, {100, 0}};

    PE_SpiderV2_Leg_t leg;

    leg.mnt = (PE_SpiderV2_Point3D_t) {0, 0, 0};
    leg.src = (PE_SpiderV2_Point3D_t) {10,0,0};
    leg.dst = (PE_SpiderV2_Point3D_t) {0, 0, 0};

    PE_SpiderV2_calculateTargetRotate(&moving, &leg, -10, PE_SPIDER_V2_LEG_MODE_FLOATING);

    TEST_ASSERT(10 < leg.dst.x)
    TEST_ASSERT(0 > leg.dst.y)
}

void test_PE_SpiderV2_calculateTargetRotateXY2() {
    PE_SpiderV2_Moving_t moving = {0, 0, 0, {-100, 0}};

    PE_SpiderV2_Leg_t leg;

    leg.mnt = (PE_SpiderV2_Point3D_t) {0, 0, 0};
    leg.src = (PE_SpiderV2_Point3D_t) {10,0,0};
    leg.dst = (PE_SpiderV2_Point3D_t) {0, 0, 0};

    PE_SpiderV2_calculateTargetRotate(&moving, &leg, -10, PE_SPIDER_V2_LEG_MODE_FLOATING);

    TEST_ASSERT(10 > leg.dst.x)
    TEST_ASSERT(0 < leg.dst.y)
}

void test_PE_SpiderV2_calculateTargetRotateZ() {
    PE_SpiderV2_Moving_t moving = {10, 0, 0, {0, 0}};

    PE_SpiderV2_Leg_t leg;

    leg.mnt = (PE_SpiderV2_Point3D_t) {0, 0, 0};
    leg.src = (PE_SpiderV2_Point3D_t) {20, 20, -20};
    leg.dst = (PE_SpiderV2_Point3D_t) {0, 0, 0};

    PE_SpiderV2_calculateTargetRotate(&moving, &leg, 0, PE_SPIDER_V2_LEG_MODE_FLOATING);

    TEST_ASSERT_EQUAL(-20, leg.dst.z);

    leg.dst = (PE_SpiderV2_Point3D_t) {0, 0, 0};

    PE_SpiderV2_calculateTargetRotate(&moving, &leg, 0, PE_SPIDER_V2_LEG_MODE_GROUNDED);

    TEST_ASSERT_EQUAL(-30, leg.dst.z);
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_PE_SpiderV2_calculateTargetRotateXY1);
    RUN_TEST(test_PE_SpiderV2_calculateTargetRotateXY2);
    RUN_TEST(test_PE_SpiderV2_calculateTargetRotateZ);
    return UNITY_END();
}
