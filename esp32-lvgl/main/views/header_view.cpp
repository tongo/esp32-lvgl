#include "header_view.hpp"

void HeaderView::_buildContent() {
    lv_obj_set_size(_container, LV_PCT(100), 32);
    lv_obj_set_style_pad_all(_container, 8, 0);

    lv_obj_t * _recordStatusIcon = lv_obj_create(_container);
    lv_obj_set_size(_recordStatusIcon, 16, 16);
    lv_obj_align(_recordStatusIcon, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_radius(_recordStatusIcon, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_style_bg_opa(_recordStatusIcon, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_width(_recordStatusIcon, 2, 0);
    lv_obj_set_style_border_color(_recordStatusIcon, UiTheme::accentRedColor, 0);
    lv_obj_set_scrollbar_mode(_recordStatusIcon, LV_SCROLLBAR_MODE_OFF);

    lv_obj_t *label = lv_label_create(_container);
    lv_obj_set_style_text_color(label, UiTheme::textColor, 0);
    lv_label_set_text(label, "REC");
    lv_obj_align(label, LV_ALIGN_LEFT_MID, 20, 0);

    lv_obj_t *canStatus = lv_label_create(_container);
    lv_obj_set_style_text_color(canStatus, UiTheme::disableColor, 0);
    lv_label_set_text(canStatus, "CAN");
    lv_obj_align(canStatus, LV_ALIGN_RIGHT_MID, 0, 0);
}