# esp-mux-hc4067
Component ESP-IDF for HC4067 support 

# Example:
```c++
#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/gpio.h>
#include <esp_log.h>

#include "mux_hc4067.hpp"

#define S0_PIN (gpio_num_t) 36
#define S1_PIN (gpio_num_t) 35
#define S2_PIN (gpio_num_t) 38
#define S3_PIN (gpio_num_t) 37
#define SIG_PIN (gpio_num_t) 0

extern "C" void app_main()
{
    MuxHC4067 mux = MuxHC4067(S0_PIN, S1_PIN, S2_PIN, S3_PIN, SIG_PIN);
    
    bool state = true;

    while (true)
    {
        printf("pin state: %d\n", state);
        mux.set(9, state);
        state = !state;

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
```