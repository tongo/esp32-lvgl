#include "info_view.hpp"
#include "ui_theme.hpp"

void InfoView::_buildContent() {
    lv_obj_set_style_bg_color(_container, UiTheme::accentYellowColor, 0);
    lv_obj_t *label = lv_label_create(_container);
    lv_obj_set_style_text_color(label, UiTheme::bgColor, 0);
    lv_label_set_text(label, "INFO");
    lv_obj_center(label);
}