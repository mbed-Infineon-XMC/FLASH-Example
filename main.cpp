/* mbed Example Program
 * Copyright (c) 2006-2014 ARM Limited
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

/******************************************************************* Includes */
#include "mbed.h"
#include "Watchdog.h"

/******************************************************************** Globals */
Watchdog wd;
DigitalOut led1(LED1);
DigitalOut led2(LED2);
InterruptIn button(SW2);
volatile int wd_flag = 0;

/****************************************************************** Callbacks */

/**
 * Callback if rising edge detected
 */
void rise() {

    wd_flag = 1;
}

/****************************************************************** Functions */

/**
 * Main Function
 */
int main() {

    /* Check if watchdog was cause of reset */
    if (wd.watchdogCausedReset()){
        /* Turn led1 on if wadchdog timer expired */
        led1 = 1;
    }

    /* Attach rising callback function */
    button.rise(&rise);

    /* Configure & start watchdog timer 5 seconds */
    wd.configure(5.0);

    while (1) {
        wait(1);
        if(!wd_flag){
            /* Clear watchdog every second as long as button2 was not pressed */
            wd.service();
            led2 = !led2;
        }
    }
}

/*EOF*/
