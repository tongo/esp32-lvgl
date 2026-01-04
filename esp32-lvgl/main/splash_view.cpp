#include "splash_view.hpp"

void SplashView::build(lv_obj_t* parent) {
    container = lv_obj_create(parent);
    lv_obj_set_size(container, LV_PCT(100), LV_PCT(100));
    lv_obj_set_style_bg_color(container, UiTheme::bgColor, 0);
    lv_obj_set_style_border_width(container, 0, 0);

    buildTitle(parent);
    buildSubtitle(parent);
    buildSpinner(parent);
}

void SplashView::buildTitle(lv_obj_t* parent) {
    lv_color_t colors[] = { UiTheme::accentRedColor, UiTheme::textColor };
    for (int i=0; i<2; i++) {
        lv_obj_t *label = lv_label_create(parent);
        lv_label_set_text(label, "TANGODEV");
        lv_obj_set_style_bg_opa(label, LV_OPA_TRANSP, 0);
        lv_obj_set_style_text_color(label, colors[i], 0);
        lv_obj_set_style_text_font(label, UiTheme::fontH2, 0);
        lv_obj_align(label, LV_ALIGN_CENTER, (i * 2), (-20 - i));
    }
}

void SplashView::buildSubtitle(lv_obj_t* parent) {
    lv_obj_t *subtitle = lv_label_create(parent);
    lv_label_set_text(subtitle, "DATA\nACQUISITION");
    lv_obj_align(subtitle, LV_ALIGN_CENTER, 0, 20);
    lv_obj_set_style_text_align(subtitle, LV_TEXT_ALIGN_CENTER, 0);
}

void SplashView::buildSpinner(lv_obj_t* parent) {
    lv_obj_t * spinner = lv_spinner_create(parent);
    lv_obj_set_size(spinner, 30, 30);
    lv_obj_align(spinner, LV_ALIGN_BOTTOM_MID, 0, -12);
    lv_spinner_set_anim_params(spinner, 3000, 330);
    lv_obj_set_style_arc_color(spinner, UiTheme::bgColor, LV_PART_MAIN);
    lv_obj_set_style_arc_width(spinner, 3, LV_PART_MAIN);
    lv_obj_set_style_arc_color(spinner, UiTheme::textColor, LV_PART_INDICATOR);
    lv_obj_set_style_arc_width(spinner, 3, LV_PART_INDICATOR);
    lv_obj_set_style_arc_rounded(spinner, true, LV_PART_INDICATOR);
}

void SplashView::destroy() {
    if (container != nullptr) {
        lv_obj_del(container);
        container = nullptr;
    }
}