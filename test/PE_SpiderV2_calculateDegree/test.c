#include <PE_SpiderV2.h>
#include <stdio.h>
#include <unity.h>

#define SIN_45 0.707f

const float C_LENGTH = 28;
const float F_LENGTH = 70;
const float T_LENGTH = 52;

void setUp() {}
void tearDown() {}

float convertRadianToDegree(float value) {
    return value * 180 / ((float) M_PI);
}

void test_PE_SpiderV2_calculateDegree_1() {
    PE_SpiderV2_Point3D_t target   = {100 * SIN_45, 100 * SIN_45, 0};
    PE_SpiderV2_Point3D_t mount    = {0, 0, 50};
    PE_SpiderV2_LegConfig_t config = {C_LENGTH, F_LENGTH, T_LENGTH};
    PE_SpiderV2_LegDegree_t degree = {0, 0, 0};

    PE_SpiderV2_calculateDegree(&target, &mount, &config, &degree);

    printf("%f\n%f\n%f\n\n", convertRadianToDegree(degree.debug1), degree.debug2, degree.debug3);

    printf(
        "%f\n%f\n%f\n",
        convertRadianToDegree(degree.cDegree),
        convertRadianToDegree(degree.fDegree),
        convertRadianToDegree(degree.tDegree)
    );
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_PE_SpiderV2_calculateDegree_1);
    return UNITY_END();
}
