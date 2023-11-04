# ESP32-WROOM-32-ESP_LOG
Repository towards the mission of mastering the ESP32. Here I will group information about timmed function and  mainly about LOGs (ESP_LOGW/I/D/V). I will try to discuss the differences between Serial Monitor and Terminal on IDF.

We need to recover information from the ESP32 board to aid during the development. The best way of doing that is using the `printf` command. The IDF/ESP32 offer not only the printf support but also the LOG support. Here we will explore both ways.

## USB-UART Monitor

To print and use the UART monitor, basicly we need to include the standard library for input/output, the `#include <stdio.h>`, and when desired to call the `printf()` functions.
Then, insted of just running on the Terminal the command to flash, we use: 

* `idf.py build flash monitor` or,
* `idf.py build`, `idf.py -p COM5 flash` and `idf.py -p COM5 monitor`.

As results:

![image](https://github.com/Rafaelatff/ESP32-WROOM-32-ESP_LOG/assets/58916022/d5ee0399-c518-4c22-adb4-46dca1d14ea8)

The message isn't static (and just being connected to the usb message will be dropped on monitor, not deppendent on having a while(1) loop running), there are also others messagens that are sent to monitor and important things may get lost. It is also possible to use the `scarf()` function, but it is not our point here.

Note: to stop the monitor, just type `Ctrl + ]`.

## LOG

To work with the log system from espressif, we first need to add its library, then define a TAG to appear in the message log.

```c
#include "esp_log.h"
#define TAG "my_tag"
```

Then to use the log, we just need to call:

```c
ESP_LOGI(TAG, "Iniciando o bagulho.");
```

It is possible to send `##__VA_ARGS__` if desired, so it can print some variable. As results we have:

![image](https://github.com/Rafaelatff/ESP32-WROOM-32-ESP_LOG/assets/58916022/5ec74534-914d-4f39-85f1-337fd523b9b7)

The LOG informations appears as: 

* I (Milliseconds since boot) TAG: "Message"

We can change the tymestamp by opening the **menuconfig** (`start idf.py menuconfig`) and then going to 'Component config' --> 'Log output' --> 'Log timestamps' and changint it to 'System time'.

![image](https://github.com/Rafaelatff/ESP32-WROOM-32-ESP_LOG/assets/58916022/f3a5f2e3-d2cd-4aaf-9494-ea2faef9d6d2)

We also can use different types of log, such as:

```c
ESP_LOGI("LOG", "This is an info");
ESP_LOGW("LOG", "This is a warning");
ESP_LOGD("LOG", "This is a debug");
ESP_LOGV("LOG", "This is a verbose");
ESP_LOGE("LOG", "This is an error"); 
```

As results we see that we can have diffent color coded messages, according with the log type choosen.

![image](https://github.com/Rafaelatff/ESP32-WROOM-32-ESP_LOG/assets/58916022/5a2e836d-3d09-49ed-b209-4da475c819c6)

The verbose and error messages didn't appear because they are not set. We changed the timestamp but we didn't configurated the FreeRTOS. Next part of this studie will discuss timmed functions (ESP32 clock, time between functions and others).

![image](https://github.com/Rafaelatff/ESP32-WROOM-32-ESP_LOG/assets/58916022/6ed5cc55-c473-48a1-8986-f1b6000d496b)

## Timmed functions

Here we will discuss a little bit about the configurations related to time. We already did some configurations by:

* Open the **menuconfig** (`start idf.py menuconfig`).
* Set the crystal frequency: 'Component config' ---> 'Hardware Settings' ---> 'Main XTAL Config' and 'Main XTAL frequency' and set it to '(X) 40 MHz'.
* Change the CPU frequency to 240 MHz by going to 'Component config --->' -> 'ESP System Settings' -> 'CPU frequency' -> '(X) 240 MHz'.
* In the source file, we add the incluse for time functions.
```c
#include "esp_timer.h"
```
* Inside a while(1) loop, we add only the code to read the time:
```c
    while(1){
       printf("Timer: %lld microseconds\n", esp_timer_get_time());
    }
```
* Now let's check the time that took between one get_time and another.
![image](https://github.com/Rafaelatff/ESP32-WROOM-32-ESP_LOG/assets/58916022/68e817ca-f09c-4fce-ba22-31951ed29cb9)

According to the printed message on the terminal, the time between one printf and another were: **2517** microseconds.
* Now comparint with the time between LOG messages:
```c
    while(1){
        ESP_LOGI(TAG, "Timer: %lld microseconds", esp_timer_get_time());
        //printf("Timer: %lld microseconds\n", esp_timer_get_time());
    }
```
* Let's check the results and compare with the printf message:
![image](https://github.com/Rafaelatff/ESP32-WROOM-32-ESP_LOG/assets/58916022/6ea9de59-dd77-43f6-a18e-3fbc90c0acc3)

Almost twice the time of the printf function, **4948**.

* A função `vTaskDelay()` faz parte da FreeRTOS. Ela é usada para atrasar a execução de uma tarefa (ou thread) por um período específico de tempo, permitindo que outras tarefas sejam executadas durante o atraso. Vamos adicionar a lib referente ao FreeRTOS.
```c
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
```
* Now let's use the `vTaskDelay()` to generate the delay. We can pass the number of ticks directly to the function by `vTaskDelay(1000)`. Adding this before the printf message we have as results:

![image](https://github.com/Rafaelatff/ESP32-WROOM-32-ESP_LOG/assets/58916022/157338e5-e554-482c-96ca-fab9f908368c)

It took **10000000** microseconds (10 seconds) between one reading and another. I guess my timming functions aren't configured so well. But this repositorie is here so we can leran how to, correcly configure it. Let's check our menuconfig:

On the `esp_timer` we have:

![image](https://github.com/Rafaelatff/ESP32-WROOM-32-ESP_LOG/assets/58916022/fda2c4f2-c961-469d-8730-13aa3ff2f8ea)

On the `freeRTOS` we have:

![image](https://github.com/Rafaelatff/ESP32-WROOM-32-ESP_LOG/assets/58916022/71e1925f-6aeb-4016-ab67-4b084103ce2d)

I tried to configure the `configTICK_RATE_HZ` to 1 (min value), but it returned the error (and rebooted):

```py
assert failed: esp_int_wdt_cpu_init int_wdt.c:147 ((CONFIG_ESP_INT_WDT_TIMEOUT_MS >= (portTICK_PERIOD_MS << 1)) && "Interrupt watchdog timeout needs to be at least twice the RTOS tick period!")
```

To fix that, I also had to change the 'Componet Config' ---> 'ESP System Settings' ---> 'Interrupt Watchdog Timeout (ms)' to 10000. ESP32 get slower..

![image](https://github.com/Rafaelatff/ESP32-WROOM-32-ESP_LOG/assets/58916022/a70df460-d9cb-483b-aa17-232ec574c864)

Then I configure the `configTICK_RATE_HZ` to 1000 (max value).
 
![image](https://github.com/Rafaelatff/ESP32-WROOM-32-ESP_LOG/assets/58916022/7259a821-8921-4938-bb95-38d3a73248a4)

Nothing changed :(. Today I wake up thinking about printing only the value, not the whole string (this takes time!). And it looks it takes really a lot of time! UART speed is 115200 kbps, this is limiting my code.

![image](https://github.com/Rafaelatff/ESP32-WROOM-32-ESP_LOG/assets/58916022/cb14e91f-4949-4de5-9cd5-efd9f03cc7cc)

**Now I have a speed of 781 microseconds.**

Maybe test the on/off of the blue LED on the oscilloscope (limited to 100 MHz). I guess it is okay for the moment.. test with oscilloscope can be placed during the PWM tests/learning.

# Bibliography

All the links that help me through the process of ESP32 learning.

* [ESP IDF printf and scanf via the console without UART definitions](https://www.youtube.com/watch?v=WzxZSvWVWpM).
* [ESP IDF Timer 1 - timer_esp_timer_get_time](https://www.youtube.com/watch?v=grBvdzKdNTY&list=PLgrKXQgo8LPt12719eN2-xVFqlmRZd2Qk&index=1).
* [ESP IDF Timer 2 - portTICK_PERIOD_MS vs portTICK_RATE_MS](https://www.youtube.com/watch?v=-IIXnF3NnyI&list=PLgrKXQgo8LPt12719eN2-xVFqlmRZd2Qk&index=2).
* [ESP IDF Timer 3 - vTaskDelay in ticks](https://www.youtube.com/watch?v=O4SwMBGzWa4&list=PLgrKXQgo8LPt12719eN2-xVFqlmRZd2Qk&index=3).
