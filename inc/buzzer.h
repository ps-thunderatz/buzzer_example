/**
 * @file buzzer.h
 *
 * @brief Buzzer control and initialization
 */

#ifndef __BUZZER_H__
#define __BUZZER_H__

#include <stdint.h>

/*****************************************
 * Public Function Prototypes
 *****************************************/

/**
 * @brief Buzzer initialization
 */
void buzzer_init(void);

/**
 * @brief Buzzer control
 *
 * @param volume Duty cycle of the PWM wave
 * @note Max value for volume is 0.8
 */
void buzzer_set_volume(float volume);

/**
 * @brief Buzzer control
 *
 * @param frequency Frequency of the sound to be emitted in Hz
 */
void buzzer_set_frequency(uint16_t frequency);

#endif // __BUZZER_H__
