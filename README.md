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

```py
#include "esp_log.h"
#define TAG "my_tag"
```

Then to use the log, we just need to call:

```py
ESP_LOGI(TAG, "Iniciando o bagulho.");
```

It is possible to send `##__VA_ARGS__` if desired, so it can print some variable. As results we have:

![image](https://github.com/Rafaelatff/ESP32-WROOM-32-ESP_LOG/assets/58916022/5ec74534-914d-4f39-85f1-337fd523b9b7)

The LOG informations appears as: 

* I (Milliseconds since boot) TAG: "Message"

We can change the tymestamp by opening the **menuconfig** (`start idf.py menuconfig`) and then going to 'Component config' --> 'Log output' --> 'Log timestamps' and changint it to 'System time'.

![image](https://github.com/Rafaelatff/ESP32-WROOM-32-ESP_LOG/assets/58916022/f3a5f2e3-d2cd-4aaf-9494-ea2faef9d6d2)

We also can use different types of log, such as:

```py
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
* Set the crystal frequency: 'Component config --->' -> 'Hardware Settings' -> 'Main XTAL Config' and 'Main XTAL frequency' and set it to '(X) 40 MHz'.
* Change the CPU frequency to 240 MHz by going to 'Component config --->' -> 'ESP System Settings' -> 'CPU frequency' -> '(X) 240 MHz'.
* 

# Bibliography

All the links that help me through the process of ESP32 learning.

* [ESP IDF printf and scanf via the console without UART definitions](https://www.youtube.com/watch?v=WzxZSvWVWpM).
