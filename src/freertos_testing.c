#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"
#include "freertos_testing.h"

#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "pico/cyw43_arch.h"

/**
 * Blinks the LED at an interval of count % 11.
 * Increments count on each iteration and returns
 * whether LED is on or off.
 */
bool blink_loop(bool on,int *count){
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, on);
    *count += 1;
    if (*count % 11) on = !on;
    return on;
}

/**
 * If the input character is lowercase letter it will
 * return the capital letter. If uppercase letter is
 * the input character the lowercase of that letter is returned.
 * Else if the character is not a letter then the return is the
 * inputted character.
 */
char main_loop(char c){
    if (c <= 'z' && c >= 'a') return c - 32;
    else if (c >= 'A' && c <= 'Z') return c + 32;
    else return c;
}