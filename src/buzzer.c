/**
 * @file buzzer.c
 *
 * @brief Buzzer control and initialization
 */

#include "buzzer.h"
#include "utils.h"

#include "tim.h"

/*****************************************
 * Private Variables
 *****************************************/

#define TIM_FREQUENCY_HZ 2000000U /**< This is the internal clock divided by the prescaler */

#define MAX_FREQUENCY_HZ 20000U
#define MIN_FREQUENCY_HZ 20U

/*****************************************
 * Private Variables
 *****************************************/

float m_volume;
uint32_t m_counter;

/*****************************************
 * Public Function Body Definitions
 *****************************************/

void buzzer_init(void) {
    MX_TIM1_Init();
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);

    m_volume = 0.0;
    buzzer_set_frequency(440); /**< A4 frequency */
}

void buzzer_set_volume(float volume) {
    m_volume = volume;
    uint32_t compare = (uint32_t) ((float) m_counter * m_volume);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, compare);
}

void buzzer_set_frequency(uint16_t frequency) {
    frequency = constrain(frequency, MIN_FREQUENCY_HZ, MAX_FREQUENCY_HZ);
    m_counter = TIM_FREQUENCY_HZ / frequency;
    uint32_t compare = (uint32_t) ((float) m_counter * m_volume);

    __HAL_TIM_SET_AUTORELOAD(&htim1, m_counter);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, compare);
}
