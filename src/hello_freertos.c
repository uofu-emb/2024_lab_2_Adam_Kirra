#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "pico/cyw43_arch.h"

// Macros defining our task properties
#define MAIN_TASK_PRIORITY      ( tskIDLE_PRIORITY + 2UL )
#define BLINK_TASK_PRIORITY     ( tskIDLE_PRIORITY + 1UL )

#define MAIN_TASK_STACK_SIZE configMINIMAL_STACK_SIZE
#define BLINK_TASK_STACK_SIZE configMINIMAL_STACK_SIZE

// Global variables
int counter;
bool led_is_on;

/// @brief Blinks the LED at a specified rate.
/// @param params 
void blink_task(__unused void *params)
{
    counter = 0;
    led_is_on = false;
    // Initialize CYW43 architecture, if 0 initialize worked
    hard_assert(cyw43_arch_init() == PICO_OK);

    // Set to false so LED is off
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, false);
    // Controls the LED toggle
    while (true) {
	cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, led_is_on);

    // if counter divided by 47 is nonzero toggle LED
	if (counter++ % 47)
	    led_is_on = !led_is_on;
        // Delays for 1000 ticks (1s possibly)
        vTaskDelay(1000);
    }
}

/// @brief Creates the blink task and loops over characters
/// modifies based on specs.
/// @param params 
void main_task(__unused void *params)
{
    // blink task is created
    xTaskCreate(blink_task, "BlinkThread", BLINK_TASK_STACK_SIZE, NULL, BLINK_TASK_PRIORITY, NULL);
    int count = 0;
    char c;

    // Loop converts input characters to upper or lower case
    while(c = getchar()) {
        // if lower case change to upper case
	if (c <= 'z' && c >= 'a') putchar(c - 32);
        // if upper case change to upper case
	else if (c >= 'A' && c <= 'Z') putchar(c + 32);
        // If not a letter then leave unchanged
	else putchar(c);
    }
}

int main( void )
{
    // Initializes UART and USB for Pico
    stdio_init_all();

    // Create new task for OS to use
    TaskHandle_t task;

    // Creates the main task
    xTaskCreate(main_task, "MainThread", MAIN_TASK_STACK_SIZE, NULL, MAIN_TASK_PRIORITY, &task);

    // Starts the freertos tasks
    vTaskStartScheduler();
    return 0;
}
