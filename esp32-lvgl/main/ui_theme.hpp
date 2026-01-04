#pragma once

#include "lvgl.h"

extern "C" {
    extern const lv_font_t font_testo;
    extern const lv_font_t font_marce;
    extern const lv_font_t font_h1;
    extern const lv_font_t font_h2;
}

class UiTheme {
public:
    static constexpr const lv_font_t* fontTesto  = &font_testo;
    static constexpr const lv_font_t* fontMarce  = &font_marce;
    static constexpr const lv_font_t* fontH1  = &font_h1;
    static constexpr const lv_font_t* fontH2  = &font_h2;

    static constexpr lv_color_t bgColor = LV_COLOR_MAKE(0, 0, 0);
    static constexpr lv_color_t textColor = LV_COLOR_MAKE(255, 255, 255);
    static constexpr lv_color_t disableColor = LV_COLOR_MAKE(159, 159, 159);
    static constexpr lv_color_t accentYellowColor = LV_COLOR_MAKE(255, 255, 0);
    static constexpr lv_color_t accentGreenColor = LV_COLOR_MAKE(52, 199, 89);
    static constexpr lv_color_t accentRedColor = LV_COLOR_MAKE(255, 56, 60);
    static constexpr lv_color_t accentCyanColor = LV_COLOR_MAKE(130, 238, 255);
    static constexpr lv_color_t accentBlueColor = LV_COLOR_MAKE(56, 129, 255);
};
