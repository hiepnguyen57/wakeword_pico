/*
 * Copyright (c) 2021 Arm Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 * 
 */

#include <stdio.h>

#include "pico/stdlib.h"
#include "hardware/pwm.h"

extern "C" {
#include "pico/pdm_microphone.h"
}

#include "tflite_model.h"
#include "ml_model.h"

// constants
#define SAMPLE_RATE       16000
#define FFT_SIZE          256
#define SPECTRUM_SHIFT    4
#define INPUT_BUFFER_SIZE ((FFT_SIZE / 2) * SPECTRUM_SHIFT)
#define INPUT_SHIFT       0

// microphone configuration
const struct pdm_microphone_config pdm_config = {
    // GPIO pin for the PDM DAT signal
    .gpio_data = 2,

    // GPIO pin for the PDM CLK signal
    .gpio_clk = 3,

    // PIO instance to use
    .pio = pio0,

    // PIO State Machine instance to use
    .pio_sm = 0,

    // sample rate in Hz
    .sample_rate = SAMPLE_RATE,

    // number of samples to buffer
    .sample_buffer_size = INPUT_BUFFER_SIZE,
};

MLModel ml_model(tflite_model, 128 * 1024);

void on_pdm_samples_ready();

int main( void )
{
    // initialize stdio
    stdio_init_all();

    printf("hello pico fire alarm detection\n");

    gpio_set_function(PICO_DEFAULT_LED_PIN, GPIO_FUNC_PWM);
    
    uint pwm_slice_num = pwm_gpio_to_slice_num(PICO_DEFAULT_LED_PIN);
    uint pwm_chan_num = pwm_gpio_to_channel(PICO_DEFAULT_LED_PIN);

    // Set period of 256 cycles (0 to 255 inclusive)
    pwm_set_wrap(pwm_slice_num, 256);

    // Set the PWM running
    pwm_set_enabled(pwm_slice_num, true);

    if (!ml_model.init()) {
        printf("Failed to initialize ML model!\n");
        while (1) { tight_loop_contents(); }
    }

    // initialize the PDM microphone
    if (pdm_microphone_init(&pdm_config) < 0) {
        printf("PDM microphone initialization failed!\n");
        while (1) { tight_loop_contents(); }
    }

    // set callback that is called when all the samples in the library
    // internal sample buffer are ready for reading
    pdm_microphone_set_samples_ready_handler(on_pdm_samples_ready);

    // start capturing data from the PDM microphone
    if (pdm_microphone_start() < 0) {
        printf("PDM microphone start failed!\n");
        while (1) { tight_loop_contents(); }
    }

    while (1) {
        // wait for new samples
        tight_loop_contents();
    }

    return 0;
}