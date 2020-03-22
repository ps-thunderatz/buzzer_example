/**
 * @file main.c
 *
 * @brief Main function
 */

#include "mcu.h"
#include "buzzer.h"

/*****************************************
 * Main Function
 *****************************************/

int main(void) {
    mcu_init();
    buzzer_init();

    mcu_sleep(2000);

    buzzer_set_volume(0.15);

    for (;;) {
        for (uint16_t i = 800; i < 3500; i++) {
            buzzer_set_frequency(i);
            mcu_sleep(1);
        }
    }
}
