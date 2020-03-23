#include <PE_SpiderV2.h>
#include <unity.h>

void test_PE_SpiderV2_calculateTargetLinearX() {
    PE_SpiderV2_Moving_t moving = {0, 1, 0, {0, 0}};

    PE_SpiderV2_Leg_t leg;

    leg.mnt = (PE_SpiderV2_Point3D_t) {0, 0, 0};
    leg.src = (PE_SpiderV2_Point3D_t) {20, 20, 20};
    leg.dst = (PE_SpiderV2_Point3D_t) {0, 0, 0};

    PE_SpiderV2_calculateTargetLinear(&moving, &leg, 10, PE_SPIDER_V2_LEG_MODE_FLOATING);

    TEST_ASSERT_EQUAL(30, leg.dst.x);

    leg.dst = (PE_SpiderV2_Point3D_t) {0, 0, 0};

    PE_SpiderV2_calculateTargetLinear(&moving, &leg, -10, PE_SPIDER_V2_LEG_MODE_FLOATING);

    TEST_ASSERT_EQUAL(10, leg.dst.x);
}

void test_PE_SpiderV2_calculateTargetLinearY() {
    PE_SpiderV2_Moving_t moving = {0, 0, 1, {0, 0}};

    PE_SpiderV2_Leg_t leg;

    leg.mnt = (PE_SpiderV2_Point3D_t) {0, 0, 0};
    leg.src = (PE_SpiderV2_Point3D_t) {20, 20, 20};
    leg.dst = (PE_SpiderV2_Point3D_t) {0, 0, 0};

    PE_SpiderV2_calculateTargetLinear(&moving, &leg, 10, PE_SPIDER_V2_LEG_MODE_FLOATING);

    TEST_ASSERT_EQUAL(30, leg.dst.y);

    leg.dst = (PE_SpiderV2_Point3D_t) {0, 0, 0};

    PE_SpiderV2_calculateTargetLinear(&moving, &leg, -10, PE_SPIDER_V2_LEG_MODE_FLOATING);

    TEST_ASSERT_EQUAL(10, leg.dst.y);
}

void test_PE_SpiderV2_calculateTargetLinearZ() {
    PE_SpiderV2_Moving_t moving = {10, 0, 0, {0, 0}};

    PE_SpiderV2_Leg_t leg;

    leg.mnt = (PE_SpiderV2_Point3D_t) {0, 0, 0};
    leg.src = (PE_SpiderV2_Point3D_t) {20, 20, -20};
    leg.dst = (PE_SpiderV2_Point3D_t) {0, 0, 0};

    PE_SpiderV2_calculateTargetLinear(&moving, &leg, 0, PE_SPIDER_V2_LEG_MODE_FLOATING);

    TEST_ASSERT_EQUAL(-20, leg.dst.z);

    leg.dst = (PE_SpiderV2_Point3D_t) {0, 0, 0};

    PE_SpiderV2_calculateTargetLinear(&moving, &leg, 0, PE_SPIDER_V2_LEG_MODE_GROUNDED);

    TEST_ASSERT_EQUAL(-30, leg.dst.z);
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_PE_SpiderV2_calculateTargetLinearX);
    RUN_TEST(test_PE_SpiderV2_calculateTargetLinearY);
    RUN_TEST(test_PE_SpiderV2_calculateTargetLinearZ);
    return UNITY_END();
}
