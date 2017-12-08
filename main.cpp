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
#include "rtos.h"

/******************************************************************** Globals */

InterruptIn button(SW2);
DigitalIn button2(SW1);
DigitalOut led1(LED1);
DigitalOut led2(LED2);
FlashIAP nvm;
volatile uint8_t cnt[256] = { 0 };
volatile uint8_t local_cnt;

Serial pc(P0_5, P0_4); // tx, rx (9600 8N1)

/****************************************************************** Callbacks */

/**
 * Callback if rising edge detected
 */
void rise() {

    local_cnt++;
    led1 = !led1;
}

/****************************************************************** Functions */

void nvm_thread()
{
    /* Load data from Flash after power up */
    uint32_t addr = nvm.get_flash_start();
    nvm.read((void*)&cnt[0], addr, sizeof(cnt));
    local_cnt = cnt[0];

    while (true) {
        /* Wait for press event */
        if (!button2) {
            led2 = 1;
            cnt[0] = local_cnt;
            /* Save new data into flash */
            nvm.erase(addr, nvm.get_sector_size(addr));
            nvm.program((void*)cnt, addr, sizeof(cnt));
            led2 = 0;
        }
        wait(0.2);
    }
}

/**
 * Main Function
 */
int main() {

    Thread worker;
    worker.start(callback(nvm_thread));

    /* Attach rising callback function */
    button.rise(&rise);

    while (true) {
        wait(1);
        pc.printf("Button was pressed %d times!\n", local_cnt);
    }
}

/*EOF*/
