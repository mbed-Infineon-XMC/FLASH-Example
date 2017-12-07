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

/******************************************************************** Globals */
Serial pc(P0_5, P0_4); // tx, rx (9600 8N1)

/****************************************************************** Functions */

/**
 * Main Function
 */
int main() {
    set_time(1512652152);  // Set RTC time to Thursday, December 7, 2017 1:09:12 PM

    while (true) {
        time_t seconds = time(NULL);

        pc.printf("Time as seconds since January 1, 1970 = %d\n", seconds);

        pc.printf("Time as a basic string = %s", ctime(&seconds));

        char buffer[32];
        strftime(buffer, 32, "%I:%M %p\n", localtime(&seconds));
        pc.printf("Time as a custom formatted string = %s", buffer);

        wait(1);
    }
}

/*EOF*/
