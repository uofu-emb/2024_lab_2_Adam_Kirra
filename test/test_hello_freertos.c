#include <stdio.h>
#include <pico/stdlib.h>
#include <stdint.h>
#include <unity.h>
#include "unity_config.h"
#include "pico/cyw43_arch.h"
#include "freertos_testing.h"

void setUp(void) {}

void tearDown(void) {}

/**
 * Tests the blink loop to ensure count and on are correctly
 * updating every loop through.
 */
void test_blink_loop()
{
    int count = 0;
    bool on = 0;
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, on);

    for(int i = 0; i < 800; i++){
        int current_count = count;
        bool next_on = blink_loop(on, &count);
        int gpio = cyw43_arch_gpio_get(CYW43_WL_GPIO_LED_PIN);
        TEST_ASSERT_EQUAL_MESSAGE(gpio, on, "GPIO should be set to the state of 'on' variable.");
        TEST_ASSERT_EQUAL_MESSAGE(current_count + 1, count, "Count is incremented each iteration.");
        if((i+1) % 11){
            TEST_ASSERT_NOT_EQUAL_MESSAGE(on, next_on, "Should change when count is a multiple of 11.");
        }else{
            TEST_ASSERT_EQUAL_MESSAGE(on, next_on, "Should not change when count isn't a multiple of 11.");
        }
        on = next_on;
    }
}

/**
 * Tests the main loop's switch case.
 */
void test_main_loop(void)
{
    TEST_ASSERT_EQUAL('Z', main_loop('z'));
    TEST_ASSERT_EQUAL('s', main_loop('S'));
    TEST_ASSERT_EQUAL('!', main_loop('!'));
    TEST_ASSERT_EQUAL('6', main_loop('6'));
    TEST_ASSERT_EQUAL('\n', main_loop('\n'));
    TEST_ASSERT_EQUAL('G' + 1, main_loop('g' + 1));
    TEST_ASSERT_EQUAL('t' - 1, main_loop('T' - 1));
}

int main (void)
{
    stdio_init_all();
    hard_assert(cyw43_arch_init() == PICO_OK);
    sleep_ms(10000); // Give time for TTY to attach.
    printf("Start tests\n");
    UNITY_BEGIN();
    RUN_TEST(test_blink_loop);
    RUN_TEST(test_main_loop);
    sleep_ms(10000);
    return UNITY_END();
}