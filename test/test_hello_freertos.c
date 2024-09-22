#include <stdio.h>
#include <pico/stdlib.h>
#include <stdint.h>
#include <unity.h>
#include "unity_config.h"

void setUp(void) {}

void tearDown(void) {}

void test_blink_loop()
{

}

void test_main_loop(void)
{
    TEST_ASSERT_EQUAL('Z', main_loop('z'));
    TEST_ASSERT_EQUAL('s', main_loop('S'));
    TEST_ASSERT_EQUAL('!', main_loop('!'));
    TEST_ASSERT_EQUAL('6', main_loop('6'));
    TEST_ASSERT_EQUAL('/n', main_loop('/n'));
    TEST_ASSERT_EQUAL('G' + 1, main_loop('g' + 1));
    TEST_ASSERT_EQUAL('t' - 1, main_loop('T' - 1));
}

int main (void)
{
    stdio_init_all();
    hard_assert(cyw43_arch_init() == PICO_OK);
    sleep_ms(5000); // Give time for TTY to attach.
    printf("Start tests\n");
    UNITY_BEGIN();
    RUN_TEST(test_blink_loop);
    RUN_TEST(test_main_loop);
    sleep_ms(5000);
    return UNITY_END();
}