#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"
#include "freertos_testing.h"

#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "pico/cyw43_arch.h"

bool blink_loop(bool on,int *count){
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, on);
    *count++;
    if (*count % 11) on = !on;
    return on;
}

char main_loop(char c){
    if (c <= 'z' && c >= 'a') return c - 32;
    else if (c >= 'A' && c <= 'Z') return c + 32;
    else return c;
}