#include <PE_SpiderV2.h>
#include <stdio.h>
#include <unity.h>

#define SIN_45 0.707f

const float C_LENGTH = 28;
const float F_LENGTH = 70;
const float T_LENGTH = 52;

void setUp() {}
void tearDown() {}

float rad2deg(float value) {
    return value * 180 / ((float) M_PI);
}

void test_PE_SpiderV2_calculateDegree_0() {
//    PE_SpiderV2_Point3D_t target   = {300 * SIN_45, 0, 0};
//    PE_SpiderV2_Point3D_t mount    = {0, 0, 0};
//    PE_SpiderV2_LegConfig_t config = {C_LENGTH, F_LENGTH, T_LENGTH};
//    PE_SpiderV2_LegDegree_t degree = {0, 0, 0};

    PE_SpiderV2_Leg_t leg;

    leg.cLength = C_LENGTH;
    leg.fLength = F_LENGTH;
    leg.tLength = T_LENGTH;
    leg.mnt     = (PE_SpiderV2_Point3D_t) {0, 0, 0};
    leg.dst     = (PE_SpiderV2_Point3D_t) {300 * SIN_45, 0, 0};

    PE_SpiderV2_calculateDegree(&leg);

    TEST_ASSERT_FLOAT_WITHIN(1, 90.0, rad2deg(leg.cDegree));
    TEST_ASSERT_FLOAT_WITHIN(1, 90.0, rad2deg(leg.fDegree));
    TEST_ASSERT_FLOAT_WITHIN(1, 180.0, rad2deg(leg.tDegree));
}

/**
 * Calculate for X>0,Y=0
 */
void test_PE_SpiderV2_calculateDegree_1() {
//    PE_SpiderV2_Point3D_t target   = {100, 0, 0};
//    PE_SpiderV2_Point3D_t mount    = {0, 0, 50};
//    PE_SpiderV2_LegConfig_t config = {C_LENGTH, F_LENGTH, T_LENGTH};
//    PE_SpiderV2_LegDegree_t degree = {0, 0, 0};

    PE_SpiderV2_Leg_t leg;

    leg.cLength = C_LENGTH;
    leg.fLength = F_LENGTH;
    leg.tLength = T_LENGTH;
    leg.mnt     = (PE_SpiderV2_Point3D_t) {0, 0, 50};
    leg.dst     = (PE_SpiderV2_Point3D_t) {100, 0, 0};

    PE_SpiderV2_calculateDegree(&leg);

    TEST_ASSERT_FLOAT_WITHIN(1, 90.0, rad2deg(leg.cDegree));
    TEST_ASSERT_FLOAT_WITHIN(1, 91.6, rad2deg(leg.fDegree));
    TEST_ASSERT_FLOAT_WITHIN(1, 90.6, rad2deg(leg.tDegree));
}

/**
 * Calculate for X>0,Y>0
 */
void test_PE_SpiderV2_calculateDegree_2() {
//    PE_SpiderV2_Point3D_t target   = {100 * SIN_45, 100 * SIN_45, 0};
//    PE_SpiderV2_Point3D_t mount    = {0, 0, 50};
//    PE_SpiderV2_LegConfig_t config = {C_LENGTH, F_LENGTH, T_LENGTH};
//    PE_SpiderV2_LegDegree_t degree = {0, 0, 0};

    PE_SpiderV2_Leg_t leg;

    leg.cLength = C_LENGTH;
    leg.fLength = F_LENGTH;
    leg.tLength = T_LENGTH;
    leg.mnt     = (PE_SpiderV2_Point3D_t) {0, 0, 50};
    leg.dst     = (PE_SpiderV2_Point3D_t) {100 * SIN_45, 100 * SIN_45, 0};

    PE_SpiderV2_calculateDegree(&leg);

    TEST_ASSERT_FLOAT_WITHIN(1, 135.0, rad2deg(leg.cDegree));
    TEST_ASSERT_FLOAT_WITHIN(1, 91.6, rad2deg(leg.fDegree));
    TEST_ASSERT_FLOAT_WITHIN(1, 90.6, rad2deg(leg.tDegree));
}

/**
 * Calculate for X>0,Y<0
 */
void test_PE_SpiderV2_calculateDegree_3() {
//    PE_SpiderV2_Point3D_t target   = {100 * SIN_45, -100 * SIN_45, 0};
//    PE_SpiderV2_Point3D_t mount    = {0, 0, 50};
//    PE_SpiderV2_LegConfig_t config = {C_LENGTH, F_LENGTH, T_LENGTH};
//    PE_SpiderV2_LegDegree_t degree = {0, 0, 0};

    PE_SpiderV2_Leg_t leg;

    leg.cLength = C_LENGTH;
    leg.fLength = F_LENGTH;
    leg.tLength = T_LENGTH;
    leg.mnt     = (PE_SpiderV2_Point3D_t) {0, 0, 50};
    leg.dst     = (PE_SpiderV2_Point3D_t) {100 * SIN_45, -100 * SIN_45, 0};

    PE_SpiderV2_calculateDegree(&leg);

    TEST_ASSERT_FLOAT_WITHIN(1, 45.0, rad2deg(leg.cDegree));
    TEST_ASSERT_FLOAT_WITHIN(1, 91.6, rad2deg(leg.fDegree));
    TEST_ASSERT_FLOAT_WITHIN(1, 90.6, rad2deg(leg.tDegree));
}

/**
 * Calculate for X<0,Y=0
 */
void test_PE_SpiderV2_calculateDegree_4() {
//    PE_SpiderV2_Point3D_t target   = {-100, 0, 0};
//    PE_SpiderV2_Point3D_t mount    = {0, 0, 50};
//    PE_SpiderV2_LegConfig_t config = {C_LENGTH, F_LENGTH, T_LENGTH};
//    PE_SpiderV2_LegDegree_t degree = {0, 0, 0};

    PE_SpiderV2_Leg_t leg;

    leg.cLength = C_LENGTH;
    leg.fLength = F_LENGTH;
    leg.tLength = T_LENGTH;
    leg.mnt     = (PE_SpiderV2_Point3D_t) {0, 0, 50};
    leg.dst     = (PE_SpiderV2_Point3D_t) {-100, 0, 0};

    PE_SpiderV2_calculateDegree(&leg);

    TEST_ASSERT_FLOAT_WITHIN(1, 90.0, rad2deg(leg.cDegree));
    TEST_ASSERT_FLOAT_WITHIN(1, 91.6, rad2deg(leg.fDegree));
    TEST_ASSERT_FLOAT_WITHIN(1, 90.6, rad2deg(leg.tDegree));
}

/**
 * Calculate for X<0,Y>0
 */
void test_PE_SpiderV2_calculateDegree_5() {
//    PE_SpiderV2_Point3D_t target   = {-100 * SIN_45, 100 * SIN_45, 0};
//    PE_SpiderV2_Point3D_t mount    = {0, 0, 50};
//    PE_SpiderV2_LegConfig_t config = {C_LENGTH, F_LENGTH, T_LENGTH};
//    PE_SpiderV2_LegDegree_t degree = {0, 0, 0};

    PE_SpiderV2_Leg_t leg;

    leg.cLength = C_LENGTH;
    leg.fLength = F_LENGTH;
    leg.tLength = T_LENGTH;
    leg.mnt     = (PE_SpiderV2_Point3D_t) {0, 0, 50};
    leg.dst     = (PE_SpiderV2_Point3D_t) {-100 * SIN_45, 100 * SIN_45, 0};

    PE_SpiderV2_calculateDegree(&leg);

    TEST_ASSERT_FLOAT_WITHIN(1, 45.0, rad2deg(leg.cDegree));
    TEST_ASSERT_FLOAT_WITHIN(1, 91.6, rad2deg(leg.fDegree));
    TEST_ASSERT_FLOAT_WITHIN(1, 90.6, rad2deg(leg.tDegree));
}

/**
 * Calculate for X<0,Y<0
 */
void test_PE_SpiderV2_calculateDegree_6() {
//    PE_SpiderV2_Point3D_t target   = {-100 * SIN_45, -100 * SIN_45, 0};
//    PE_SpiderV2_Point3D_t mount    = {0, 0, 50};
//    PE_SpiderV2_LegConfig_t config = {C_LENGTH, F_LENGTH, T_LENGTH};
//    PE_SpiderV2_LegDegree_t degree = {0, 0, 0};

    PE_SpiderV2_Leg_t leg;

    leg.cLength = C_LENGTH;
    leg.fLength = F_LENGTH;
    leg.tLength = T_LENGTH;
    leg.mnt     = (PE_SpiderV2_Point3D_t) {0, 0, 50};
    leg.dst     = (PE_SpiderV2_Point3D_t) {-100 * SIN_45, -100 * SIN_45, 0};

    PE_SpiderV2_calculateDegree(&leg);

    TEST_ASSERT_FLOAT_WITHIN(1, 135.0, rad2deg(leg.cDegree));
    TEST_ASSERT_FLOAT_WITHIN(1, 91.6, rad2deg(leg.fDegree));
    TEST_ASSERT_FLOAT_WITHIN(1, 90.6, rad2deg(leg.tDegree));
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_PE_SpiderV2_calculateDegree_0);
    RUN_TEST(test_PE_SpiderV2_calculateDegree_1);
    RUN_TEST(test_PE_SpiderV2_calculateDegree_2);
    RUN_TEST(test_PE_SpiderV2_calculateDegree_3);
    RUN_TEST(test_PE_SpiderV2_calculateDegree_4);
    RUN_TEST(test_PE_SpiderV2_calculateDegree_5);
    RUN_TEST(test_PE_SpiderV2_calculateDegree_6);
    return UNITY_END();
}
