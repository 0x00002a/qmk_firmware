
#ifdef __CLANGD_SHIM__
#define RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#else
RGB_MATRIX_EFFECT(layered_effect)
RGB_MATRIX_EFFECT(multi_colour_wave)
#endif

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static bool(*rgb_effect_layers[])(effect_params_t*) = {
};


static const HSV colour_wave_series[] = {
    {HSV_CYAN},
    {HSV_PINK},
    //{HSV_WHITE},
};

static const int8_t colour_wave_w = 3;



static bool multi_colour_wave(effect_params_t* params) {
    const HSV background = rgb_matrix_config.hsv;
    (void)background;

    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    for (uint8_t led = led_min; led < led_max; ++led) {
        rgb_matrix_set_color(led, RGB_WHITE);
        led_point_t pt = g_led_config.point[led];

        const uint8_t time  = scale16by8(g_rgb_timer + (led * 315), rgb_matrix_config.speed / 800);
        //const uint8_t xpos = (pt.x * time) % sizeof colour_wave_series;
        const uint8_t vt = scale8(abs8(sin8(time) - 128) * 2, pt.x);
        HSV hc = colour_wave_series[vt % sizeof colour_wave_series];
        hc.v = rgb_matrix_config.hsv.v;
        const RGB rgb = hsv_to_rgb(hc);

        rgb_matrix_set_color(led, rgb.r, rgb.g, rgb.b);
    }

    return rgb_matrix_check_finished_leds(led_max);
}

static bool layered_effect(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    for (size_t n = 0; n != sizeof(rgb_effect_layers); ++n) {
        rgb_effect_layers[n](params);
    }
    return rgb_matrix_check_finished_leds(led_max);
}


#endif
