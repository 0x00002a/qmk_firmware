// Copyright 2021 Mike Tsao
// Copyright 2024 Richard Dawe (@richdawe)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define WS2812_PWM_DRIVER PWMD4
#define WS2812_PWM_CHANNEL 4
#define WS2812_PWM_PAL_MODE 2
#define WS2812_DMA_STREAM STM32_DMA1_STREAM7
#define WS2812_DMA_CHANNEL 7

//#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_CUSTOM_multi_colour_wave
//#define RGB_MATRIX_DEFAULT_SPD 30
#define TAPPING_TERM 100
