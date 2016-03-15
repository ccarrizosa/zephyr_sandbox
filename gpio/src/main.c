/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <zephyr.h>
#include <device.h>
#include <gpio.h>
#include <sys_clock.h>
#define SLEEPTICKS  SECONDS(1)

#if defined(CONFIG_STDOUT_CONSOLE)
#include <stdio.h>
#define PRINT           printf
#else
#include <misc/printk.h>
#define PRINT           printk
#endif

#define LED_BLUE   21
#define LED_RED    22
#define LED_GREEN  26

void main(void)
{
    int count = 0;
    struct device *portB;
    struct device *portE;
    void *timer_data[1];
    struct nano_timer timer;
    int ret;

    nano_timer_init(&timer, timer_data);

    portB = device_get_binding(CONFIG_GPIO_K64_B_DEV_NAME);
    if (!portB) { 
        PRINT("Cannot find GPIO B dev!\n");
    }
    portE = device_get_binding(CONFIG_GPIO_K64_E_DEV_NAME);
    if (!portE) { 
        PRINT("Cannot find GPIO E dev!\n");
    }

    ret = gpio_pin_configure(portB, LED_BLUE, (GPIO_DIR_OUT));
    if (ret) { 
        PRINT("Error configuring GPIO_B_%d!\n",LED_BLUE);
    }
    ret = gpio_pin_configure(portB, LED_RED, (GPIO_DIR_OUT));
    if (ret) { 
        PRINT("Error configuring GPIO_B_%d!\n",LED_RED);
    }
    ret = gpio_pin_configure(portE, LED_GREEN, (GPIO_DIR_OUT));
    if (ret) { 
        PRINT("Error configuring GPIO_E_%d!\n",LED_GREEN);
    }

    while (1) {
        gpio_pin_write(portB, LED_BLUE, !((count % 3) == 0));
        gpio_pin_write(portB, LED_RED, !((count % 3) == 1));
        gpio_pin_write(portE, LED_GREEN, !((count % 3) == 2));

        count++;

        nano_timer_start(&timer, SLEEPTICKS);
        nano_timer_test(&timer, TICKS_UNLIMITED);
    }
}
