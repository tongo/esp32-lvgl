#include "home_view.hpp"

void HomeView::_buildContent() {
    _buildGearIndicator(_container);
    _buidGasIndicator(_container);
    _buidBrakeIndicator(_container);
    _buildActionSection(_container, "REC");
}

void HomeView::_buildGearIndicator(lv_obj_t* parent) {
    _gearIndicator = lv_label_create(parent);
    lv_label_set_text(_gearIndicator, _gears[0]);
    lv_obj_set_style_text_font(_gearIndicator, UiTheme::fontMarce, 0);
    lv_obj_set_style_text_color(_gearIndicator, UiTheme::accentYellowColor, 0);
    lv_obj_center(_gearIndicator);
}

void HomeView::_buidGasIndicator(lv_obj_t* parent) {
    _gasIndicator = _buidVerticalBar(parent, UiTheme::accentGreenColor);
    lv_obj_align(_gasIndicator, LV_ALIGN_LEFT_MID, 8, 0);
}

void HomeView::_buidBrakeIndicator(lv_obj_t* parent) {
    _brakeIndicator = _buidVerticalBar(parent, UiTheme::accentRedColor);
    lv_obj_align(_brakeIndicator, LV_ALIGN_RIGHT_MID, -8, 0);
}

lv_obj_t* HomeView::_buidVerticalBar(lv_obj_t* parent, lv_color_t color) {
    lv_obj_t* bar = lv_bar_create(parent);
    lv_obj_set_size(bar, 10, 200);
    lv_obj_set_style_border_color(bar, color, LV_PART_MAIN);
    lv_obj_set_style_border_width(bar, 2, LV_PART_MAIN);
    lv_obj_set_style_radius(bar, 16, LV_PART_MAIN);
    lv_obj_set_style_bg_opa(bar, LV_OPA_COVER, LV_PART_INDICATOR);
    lv_obj_set_style_border_color(bar, color, LV_PART_INDICATOR);
    lv_obj_set_style_radius(bar, 0, LV_PART_INDICATOR);

    lv_bar_set_value(bar, 0, LV_ANIM_OFF);

    return bar;
}

void HomeView::setGear(uint8_t gear) {
    lv_label_set_text(_gearIndicator, _gears[gear]);
    
    lv_anim_t animation;
    lv_anim_init(&animation);
    lv_anim_set_var(&animation, _gearIndicator);
    
    lv_anim_set_values(&animation, 0, 10);
    lv_anim_set_duration(&animation, 1000);
    lv_anim_set_exec_cb(&animation, [](void* var, int32_t v) {
        lv_obj_t * obj = (lv_obj_t *)var;
        lv_color_t color = (v % 2 == 0) ? UiTheme::accentYellowColor : UiTheme::textColor;
        lv_obj_set_style_text_color(obj, color, 0);
    });
    
    // Forza il colore Giallo a fine animazione
    lv_anim_set_completed_cb(&animation, [](lv_anim_t * anim) {
        lv_obj_set_style_text_color((lv_obj_t *)anim->var, UiTheme::accentYellowColor, 0);
    });

    lv_anim_start(&animation);
}