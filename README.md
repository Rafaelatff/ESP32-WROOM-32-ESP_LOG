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

![image](https://github.com/Rafaelatff/ESP32-WROOM-32-ESP_LOG/assets/58916022/5ec74534-914d-4f39-85f1-337fd523b9b7)



# Bibliography

All the links that help me through the process of ESP32 learning.

* [ESP IDF printf and scanf via the console without UART definitions](https://www.youtube.com/watch?v=WzxZSvWVWpM).
