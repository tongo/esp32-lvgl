#include "base_view.hpp"
#include "ui_theme.hpp"

lv_obj_t* BaseView::build(lv_obj_t* parent) {
    _container = lv_obj_create(parent);
    lv_obj_set_size(_container, LV_PCT(100), LV_PCT(100));
    lv_obj_set_style_bg_color(_container, UiTheme::bgColor, 0);
    lv_obj_set_style_border_width(_container, 0, 0);
    lv_obj_set_style_pad_all(_container, 0, 0);
    lv_obj_set_scrollbar_mode(_container, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_radius(_container, 0, 0);

    _buildContent();
    return _container;
}

void BaseView::_buildActionSection(lv_obj_t* parent, const char *actionLabel) {
    lv_obj_t *label = lv_label_create(parent);
    lv_obj_set_style_text_color(label, UiTheme::textColor, 0);
    lv_label_set_text(label, actionLabel);
    lv_obj_align(label, LV_ALIGN_BOTTOM_MID, 0, -20);

    static lv_style_t style_bg;
    static lv_style_t style_indic;

    lv_style_init(&style_bg);
    lv_style_set_border_color(&style_bg, UiTheme::textColor);
    lv_style_set_border_width(&style_bg, 2);
    lv_style_set_radius(&style_bg, 16);

    lv_style_init(&style_indic);
    lv_style_set_bg_opa(&style_indic, LV_OPA_COVER);
    lv_style_set_bg_color(&style_indic, UiTheme::textColor);
    lv_style_set_radius(&style_indic, 0);

    _actionBar = lv_bar_create(parent);
    lv_obj_add_style(_actionBar, &style_bg, 0);
    lv_obj_add_style(_actionBar, &style_indic, LV_PART_INDICATOR);
    lv_obj_set_size(_actionBar, 100, 10);
    lv_bar_set_value(_actionBar, 0, LV_ANIM_OFF);
    lv_obj_align(_actionBar, LV_ALIGN_BOTTOM_MID, 0, -8);
}

void BaseView::startLongPressAnimation(uint32_t duration) {
    if (_actionBar == nullptr) return;

    lv_obj_remove_flag(_actionBar, LV_OBJ_FLAG_HIDDEN);
    lv_bar_set_value(_actionBar, 0, LV_ANIM_OFF);

    lv_anim_t animation;
    lv_anim_init(&animation);
    lv_anim_set_var(&animation, _actionBar);
    lv_anim_set_values(&animation, 0, 100);
    lv_anim_set_duration(&animation, duration);
    lv_anim_set_exec_cb(&animation, [](void* var, int32_t v) {
        lv_bar_set_value(static_cast<lv_obj_t*>(var), v, LV_ANIM_OFF);
    });
    lv_anim_set_path_cb(&animation, lv_anim_path_linear);
    lv_anim_start(&animation);
}

void BaseView::stopLongPressAnimation() {
    if (_actionBar == nullptr) return;
    lv_anim_delete(_actionBar, nullptr);
    lv_bar_set_value(_actionBar, 0, LV_ANIM_OFF);
}

void BaseView::destroy() {
    if (_container != nullptr) {
        lv_obj_del(_container);
        _container = nullptr;
    }
}