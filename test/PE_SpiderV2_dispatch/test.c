#include <PE_SpiderV2.h>
#include <unity.h>
#include "stm32f1xx_hal.h"

PE_SpiderV2_t spider;

void test_PE_SpiderV2_dispatch_millis_skip() {
    spider.millis = 0;

    PE_SpiderV2_dispatch(&spider, 5);

    TEST_ASSERT_EQUAL(0, spider.millis);
}

void test_PE_SpiderV2_dispatch_millis_update() {
    spider.millis = 0;

    PE_SpiderV2_dispatch(&spider, 25);

    TEST_ASSERT_EQUAL(25, spider.millis);
}

int main(int argc, char **argv) {
    HAL_Init();         // initialize the HAL library
    HAL_Delay(2000);    // service delay

    UNITY_BEGIN();
    RUN_TEST(test_PE_SpiderV2_dispatch_millis_skip);
    RUN_TEST(test_PE_SpiderV2_dispatch_millis_update);
    return UNITY_END();
}
