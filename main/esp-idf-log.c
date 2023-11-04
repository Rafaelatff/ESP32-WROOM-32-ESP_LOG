#include <stdio.h>
#include "sdkconfig.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
#include "esp_timer.h"
#include "FreeRTOSConfig.h"

#define TAG "my_tag"

void app_main(void)
{

    gpio_set_direction(GPIO_NUM_2,GPIO_MODE_OUTPUT);
    gpio_set_level(GPIO_NUM_2,1); // To test - GPIO2 is connected to the anode of blue led.

    ESP_LOGI("LOG", "This is an info");
    ESP_LOGW("LOG", "This is a warning");
    ESP_LOGD("LOG", "This is a debug");
    ESP_LOGV("LOG", "This is a verbose");
    ESP_LOGE("LOG", "This is an error"); 
    printf("Iniciando o bagulho. \n\n");

    printf("The portTICK_PERIOD_MS is %ld\n", portTICK_PERIOD_MS);

    while(1){
        ESP_LOGI(TAG, "Timer: %lld microseconds", esp_timer_get_time());
        printf("Timer: %lld microseconds\n", esp_timer_get_time());
        vTaskDelay(1);
    }
}