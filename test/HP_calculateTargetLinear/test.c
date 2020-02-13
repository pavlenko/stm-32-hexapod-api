#include <V2/hexapod.h>
#include <unity.h>

void test_HP_calculateTargetLinearX() {
    HP_Status_t status = {0,1,0,0,0};
    HP_Leg_t leg = {0,0,0,20, 20, 20};

    leg.tgt = (Point3D_t) {0, 0, 0};
    HP_calculateTargetLinear(&status, &leg, 10, LEG_MODE_FLOATING);

    TEST_ASSERT_EQUAL(30, leg.tgt.x);

    leg.tgt = (Point3D_t) {0, 0, 0};
    HP_calculateTargetLinear(&status, &leg, -10, LEG_MODE_FLOATING);

    TEST_ASSERT_EQUAL(10, leg.tgt.x);
}

void test_HP_calculateTargetLinearY() {
    HP_Status_t status = {0,0,1,0,0};
    HP_Leg_t leg = {0,0,0,20, 20, 20};

    leg.tgt = (Point3D_t) {0, 0, 0};
    HP_calculateTargetLinear(&status, &leg, 10, LEG_MODE_FLOATING);

    TEST_ASSERT_EQUAL(30, leg.tgt.y);

    leg.tgt = (Point3D_t) {0, 0, 0};
    HP_calculateTargetLinear(&status, &leg, -10, LEG_MODE_FLOATING);

    TEST_ASSERT_EQUAL(10, leg.tgt.y);
}

void test_HP_calculateTargetLinearZ() {
    HP_Status_t status = {10,0,0,0,0};
    HP_Leg_t leg = {0,0,0,20, 20, -20};

    leg.tgt = (Point3D_t) {0, 0, 0};
    HP_calculateTargetLinear(&status, &leg, 0, LEG_MODE_FLOATING);

    TEST_ASSERT_EQUAL(-20, leg.tgt.z);

    leg.tgt = (Point3D_t) {0, 0, 0};
    HP_calculateTargetLinear(&status, &leg, 0, LEG_MODE_GROUNDED);

    TEST_ASSERT_EQUAL(-30, leg.tgt.z);
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_HP_calculateTargetLinearX);
    RUN_TEST(test_HP_calculateTargetLinearY);
    RUN_TEST(test_HP_calculateTargetLinearZ);
    return UNITY_END();
}
