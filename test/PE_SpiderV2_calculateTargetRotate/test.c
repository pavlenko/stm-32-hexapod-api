#include <PE_SpiderV2.h>
#include <unity.h>
#include <stdio.h>

void setUp() {}
void tearDown() {}

void test_PE_SpiderV2_calculateTargetRotateXY1() {
    PE_SpiderV2_t spider;
    spider.moving        = (PE_SpiderV2_moving_t) {0, 0, 0, 100, 0};
    spider.legMounts[0]  = (PE_SpiderV2_Point3D_t) {0, 0, 0};
    spider.legSources[0] = (PE_SpiderV2_Point3D_t) {10,0,0};
    spider.legTargets[0] = (PE_SpiderV2_Point3D_t) {0, 0, 0};

    PE_SpiderV2_calculateTargetRotate(&spider, 0, -10, PE_SPIDER_V2_LEG_MODE_FLOATING);

    TEST_ASSERT(10 < spider.legTargets[0].x)
    TEST_ASSERT(0 > spider.legTargets[0].y)
}

void test_PE_SpiderV2_calculateTargetRotateXY2() {
    PE_SpiderV2_t spider;
    spider.moving        = (PE_SpiderV2_moving_t) {0, 0, 0, -100, 0};
    spider.legMounts[0]  = (PE_SpiderV2_Point3D_t) {0, 0, 0};
    spider.legSources[0] = (PE_SpiderV2_Point3D_t) {10,0,0};
    spider.legTargets[0] = (PE_SpiderV2_Point3D_t) {0, 0, 0};

    PE_SpiderV2_calculateTargetRotate(&spider, 0, -10, PE_SPIDER_V2_LEG_MODE_FLOATING);

    TEST_ASSERT(10 > spider.legTargets[0].x)
    TEST_ASSERT(0 < spider.legTargets[0].y)
}

void test_PE_SpiderV2_calculateTargetRotateZ() {
    PE_SpiderV2_t spider;
    spider.moving        = (PE_SpiderV2_moving_t) {10, 0, 0, 0, 0};
    spider.legMounts[0]  = (PE_SpiderV2_Point3D_t) {0, 0, 0};
    spider.legSources[0] = (PE_SpiderV2_Point3D_t) {20, 20, -20};

    spider.legTargets[0] = (PE_SpiderV2_Point3D_t) {0, 0, 0};
    PE_SpiderV2_calculateTargetRotate(&spider, 0, 0, PE_SPIDER_V2_LEG_MODE_FLOATING);

    TEST_ASSERT_EQUAL(-20, spider.legTargets[0].z);

    spider.legTargets[0] = (PE_SpiderV2_Point3D_t) {0, 0, 0};
    PE_SpiderV2_calculateTargetRotate(&spider, 0, 0, PE_SPIDER_V2_LEG_MODE_GROUNDED);

    TEST_ASSERT_EQUAL(-30, spider.legTargets[0].z);
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_PE_SpiderV2_calculateTargetRotateXY1);
    RUN_TEST(test_PE_SpiderV2_calculateTargetRotateXY2);
    RUN_TEST(test_PE_SpiderV2_calculateTargetRotateZ);
    return UNITY_END();
}
