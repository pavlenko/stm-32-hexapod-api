#include <PE_SpiderV2.h>
#include <stdio.h>
#include <unity.h>

PE_SpiderV2_t spider = {
    .remote = {.moveY = 1, .moveX = 0, .rotateZ = 0},
    .moving = {.height = 50},
    .legs = {
        {.cLength = 28, .fLength = 69, .tLength = 52, .mnt = {-85, 120, 0},  .src = {-135, 190, 0}},
        {.cLength = 28, .fLength = 69, .tLength = 52, .mnt = {85, 120, 0},   .src = {135, 190, 0}},
        {.cLength = 28, .fLength = 69, .tLength = 52, .mnt = {-170, 0, 0},   .src = {-270, 0, 0}},
        {.cLength = 28, .fLength = 69, .tLength = 52, .mnt = {170, 0, 0},    .src = {270, 0, 0}},
        {.cLength = 28, .fLength = 69, .tLength = 52, .mnt = {-85, -120, 0}, .src = {-135, -190, 0}},
        {.cLength = 28, .fLength = 69, .tLength = 52, .mnt = {85, -120, 0},  .src = {135, -190, 0}},
    },
    .calculate = PE_SpiderV2_calculateTargetLinear
};

float rad2deg(float value) {
    return value * 180 / ((float) M_PI);
}

void PE_SpiderV2_dump() {
    uint8_t index;
    printf("-----\n");

    printf("remote{moveX: %f, moveY: %f, rotateZ: %d}\n", spider.remote.moveX, spider.remote.moveY, spider.remote.rotateZ);
    printf(
        "moving{moveByX: %f, moveByY: %f, rotateZBy{x: %f, y: %f}}\n",
        spider.moving.moveByX,
        spider.moving.moveByY,
        spider.moving.rotateZBy.x,
        spider.moving.rotateZBy.y
    );

    for (index = 0; index < 6; index++) {
        printf(
            "%d: dst{x: %8.3f, y: %8.3f, z: %8.3f} deg{c: %7.3f, f: %7.3f, t: %7.3f}\n",
            index,
            spider.legs[index].dst.x,
            spider.legs[index].dst.y,
            spider.legs[index].dst.z,
            rad2deg(spider.legs[index].cDegree),
            rad2deg(spider.legs[index].fDegree),
            rad2deg(spider.legs[index].tDegree)
        );
    }
    printf("-----\n");
}

void test_0() {
    PE_SpiderV2_handlerIdle_onEntering(&spider);
    PE_SpiderV2_dump();
}

void test_1() {
    PE_SpiderV2_handlerMove1_onEntering(&spider);
    PE_SpiderV2_dump();
}

void test_2() {
    PE_SpiderV2_handlerMove2_onEntering(&spider);
    PE_SpiderV2_dump();
}

void test_3() {
    PE_SpiderV2_handlerMove3_onEntering(&spider);
    PE_SpiderV2_dump();
}

void test_4() {
    PE_SpiderV2_handlerMove4_onEntering(&spider);
    PE_SpiderV2_dump();
}

void test_5() {
    PE_SpiderV2_handlerMove5_onEntering(&spider);
    PE_SpiderV2_dump();
}

void test_6() {
    PE_SpiderV2_handlerMove6_onEntering(&spider);
    PE_SpiderV2_dump();
}

void test_7() {
    PE_SpiderV2_handlerMove7_onEntering(&spider);
    PE_SpiderV2_dump();
}

void test_8() {
    PE_SpiderV2_handlerMove8_onEntering(&spider);
    PE_SpiderV2_dump();
}

int main(int argc, char **argv) {
    PE_SpiderV2_calculateMovingLinear(&(spider.remote), &(spider.moving));
    PE_SpiderV2_calculateMovingRotate(&(spider.remote), &(spider.moving));

    UNITY_BEGIN();
    RUN_TEST(test_0);
    RUN_TEST(test_1);
    RUN_TEST(test_2);
    RUN_TEST(test_3);
    RUN_TEST(test_4);
    RUN_TEST(test_5);
    RUN_TEST(test_6);
    RUN_TEST(test_7);
    RUN_TEST(test_8);
    return UNITY_END();
}
