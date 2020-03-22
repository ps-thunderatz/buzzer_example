/**
 * @file main.c
 *
 * @brief Main function
 */

#include "stdint.h"
#include "stdbool.h"

#include "mcu.h"
#include "buzzer.h"
#include "pitches.h"
#include "utils.h"

/*****************************************
 * Private Constants
 *****************************************/

#define COMPASS_TIME 2400

/*****************************************
 * Private Variables
 *****************************************/

uint16_t notes[] = {
    0, 0, NOTE_FS5, NOTE_E5,
    NOTE_FS5, NOTE_E5, NOTE_FS5, NOTE_E5, NOTE_FS5, NOTE_E5, NOTE_FS5, NOTE_FS5, NOTE_A5, NOTE_GS5,
    NOTE_GS5, 0, NOTE_A5, NOTE_A5, NOTE_GS5,
    NOTE_GS5, NOTE_FS5, NOTE_FS5, NOTE_FS5, NOTE_E5, NOTE_FS5, NOTE_FS5, NOTE_E5, NOTE_FS5, NOTE_FS5, NOTE_A5, NOTE_GS5,
    NOTE_GS5, 0, 0, NOTE_E5, NOTE_FS5, NOTE_E5,
    NOTE_FS5, NOTE_E5, NOTE_FS5, NOTE_E5, NOTE_FS5, NOTE_E5, NOTE_FS5, NOTE_FS5, NOTE_A5, NOTE_GS5,
    NOTE_GS5, 0, 0, 0, NOTE_FS5, NOTE_GS5, NOTE_A5, NOTE_GS5,
    NOTE_GS5, NOTE_FS5, NOTE_FS5, NOTE_FS5, NOTE_E5, NOTE_FS5, NOTE_FS5, NOTE_E5, NOTE_FS5, NOTE_FS5, NOTE_A5, NOTE_A5,
    NOTE_GS5, 0, NOTE_CS6, NOTE_B5,
    NOTE_B5, NOTE_A5, NOTE_B5, NOTE_A5, NOTE_B5, NOTE_A5, NOTE_GS5, NOTE_GS5, NOTE_GS5,
    NOTE_GS5, NOTE_E5, NOTE_FS5, 0, 0, NOTE_FS5, NOTE_E5, NOTE_A5, NOTE_GS5,
    NOTE_GS5, NOTE_A5, NOTE_A5, NOTE_GS5, NOTE_GS5, NOTE_FS5, NOTE_FS5, NOTE_FS5, NOTE_FS5, NOTE_FS5,
    NOTE_A5, 0, NOTE_B5, 0, NOTE_A5,
    NOTE_GS5, NOTE_FS5, NOTE_GS5, NOTE_FS5, NOTE_GS5, NOTE_FS5, NOTE_FS5, NOTE_FS5, NOTE_A5,
    NOTE_A5, 0, 0, 0, NOTE_FS5, NOTE_A5, NOTE_A5, NOTE_GS5,
    NOTE_GS5, NOTE_FS5, NOTE_GS5, NOTE_GS5, NOTE_FS5, NOTE_GS5, NOTE_GS5, NOTE_FS5, NOTE_FS5, NOTE_FS5, NOTE_A5, NOTE_A5,
    // NC
    NOTE_GS5, 0, 0, NOTE_FS5, NOTE_FS5, NOTE_FS5,
    NOTE_A5, NOTE_A5, NOTE_A5, NOTE_GS5, NOTE_GS5, NOTE_GS5, NOTE_GS5, NOTE_FS5, NOTE_FS5, NOTE_A5, NOTE_A5, NOTE_FS5,
    NOTE_FS5, 0, 0, 0, NOTE_FS5, NOTE_A5, NOTE_A5, NOTE_GS5,
    NOTE_GS5, NOTE_GS5, NOTE_FS5, NOTE_GS5, NOTE_FS5, NOTE_GS5, NOTE_FS5, NOTE_FS5, NOTE_GS5, NOTE_FS5, NOTE_A5, NOTE_GS5,
    NOTE_FS5, NOTE_A5, 0, NOTE_FS5, NOTE_FS5,
    NOTE_A5, NOTE_A5, NOTE_A5, NOTE_GS5, NOTE_GS5, NOTE_GS5, NOTE_GS5, NOTE_FS5, NOTE_FS5, NOTE_A5, NOTE_A5, NOTE_FS5,
    NOTE_FS5, 0, 0, 0, NOTE_FS5, NOTE_A5, NOTE_A5, NOTE_GS5,
    NOTE_GS5, NOTE_FS5, NOTE_GS5, NOTE_FS5, NOTE_GS5, NOTE_FS5, NOTE_A5, NOTE_A5, NOTE_GS5,
    NOTE_FS5, NOTE_A5, 0, 0
};

uint8_t duration[] = {
    2, 4, 8, 8,
    8, 8, 8, 8, 16, 8, 16, 16, 8, 16,
    4, 2, 16, 8, 16,
    8, 16, 16, 8, 16, 16, 16, 8, 16, 16, 8, 16,
    4, 4, 8, 8, 8, 8,
    8, 8, 8, 8, 16, 8, 16, 16, 8, 16,
    4, 4, 8, 16, 16, 16, 8, 16,
    8, 16, 16, 8, 16, 16, 8, 16, 16, 16, 8, 16,
    4, 4, 4, 4,
    8, 8, 8, 8, 8, 8, 16, 8, 16,
    8, 8, 4, 8, 16, 16, 16, 8, 16,
    4, 8, 16, 16, 4, 16, 16, 16, 8, 16,
    4, 4, 4, 8, 8,
    8, 8, 8, 8, 8, 8, 16, 8, 16,
    4, 4, 8, 16, 16, 16, 8, 16,
    8, 16, 16, 8, 16, 16, 8, 16, 16, 16, 8, 16,
    // NC
    4, 8, 16, 16, 4, 4,
    8, 16, 16, 8, 16, 16, 8, 16, 16, 8, 16, 16,
    5, 5, 8, 16, 16, 16, 8, 16,
    8, 16, 16, 16, 16, 16, 16, 16, 8, 16, 8, 8,
    8, 8, 4, 4, 4,
    8, 16, 16, 8, 16, 16, 8, 16, 16, 8, 16, 16,
    5, 5, 8, 16, 16, 16, 8, 16,
    8, 8, 8, 8, 16, 8, 16, 8, 8,
    8, 8, 2, 4
};

uint8_t connected[] = {
    1, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 1, 0, 0, 1,
    0, 0, 0, 0, 1,
    0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1,
    0, 1, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 1, 0, 0, 1,
    0, 1, 1, 0, 0, 0, 0, 1,
    0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0,
    0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 1,
    0, 0, 0, 1, 0, 0, 0, 0, 1,
    0, 1, 0, 1, 0, 0, 1, 0, 1, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 1,
    0, 1, 1, 0, 0, 0, 0, 1,
    0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0,
    // NC
    0, 1, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
    0, 1, 1, 0, 0, 0, 0, 1,
    0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
    0, 1, 1, 0, 0, 0, 0, 1,
    0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 1, 0
};

/*****************************************
 * Main Function
 *****************************************/

int main(void) {
    mcu_init();
    buzzer_init();

    for (;;) {
        for (uint16_t i = 0; i < len(notes); i++) {
            buzzer_set_frequency(notes[i]);
            mcu_sleep(COMPASS_TIME / duration[i]);

            if (!connected[i]) {
                buzzer_set_frequency(0);
                mcu_sleep(COMPASS_TIME / 128);
            }
        }

        buzzer_set_frequency(0);
        mcu_sleep(1000);
    }
}
