#include <PE_SpiderV2.h>
#include <stdio.h>
#include <unity.h>

void setUp() {}
void tearDown() {}

float convertRadianToDegree(float value) {
    return value * 180 / ((float) M_PI);
}

void test_PE_SpiderV2_calculateDegree_1() {
    PE_SpiderV2_Point3D_t target   = {-20, 20, -10};
    PE_SpiderV2_Point3D_t mount    = {-10, 10, 0};
    PE_SpiderV2_LegConfig_t config = {5, 10, 10};
    PE_SpiderV2_LegDegree_t degree = {0, 0, 0};

    PE_SpiderV2_calculateDegree(&target, &mount, &config, &degree);

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
