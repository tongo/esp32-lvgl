#include "shutdown_view.hpp"

void ShutdownView::_buildContent() {
    lv_obj_t *label = lv_label_create(_container);
    lv_obj_set_style_text_color(label, UiTheme::textColor, 0);
    lv_label_set_text(label, "SHUTDOWN");
    lv_obj_center(label);
}