#include "settings_view.hpp"
#include "ui_theme.hpp"

void SettingsView::_buildContent() {
    lv_obj_t *label = lv_label_create(_container);
    lv_obj_set_style_text_color(label, UiTheme::textColor, 0);
    lv_label_set_text(label, "SETTINGS");
    lv_obj_center(label);

    _buildActionSection(_container, "START WIFI");
}