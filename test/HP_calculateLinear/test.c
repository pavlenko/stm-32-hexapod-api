#include <V2/hexapod.h>
#include <unity.h>
#include <stdio.h>

void test_HP_calculateLinear() {
    HP_Remote_t remote = {0, 0, 0};
    HP_Status_t status;

    HP_calculateLinear(&remote, &status);

    printf("%f %f\n", status.rotateZBy.x, status.rotateZBy.y);
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_HP_calculateLinear);
    return UNITY_END();
}
