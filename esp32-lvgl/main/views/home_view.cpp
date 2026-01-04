#include "home_view.hpp"

void HomeView::build(lv_obj_t* parent) {
    _container = lv_obj_create(parent);
    lv_obj_set_size(_container, LV_PCT(100), LV_PCT(100));
    lv_obj_set_style_bg_color(_container, UiTheme::bgColor, 0);
    lv_obj_set_style_border_width(_container, 0, 0);
    lv_obj_set_style_pad_all(_container, 0, 0);

    _buildStatusBar(_container);
    _buildGearIndicator(_container);
    _buidGasIndicator(_container);
    _buidBrakeIndicator(_container);

    _buildActionSection(_container);
    _buildPageIndicator(_container, 0);
}

void HomeView::_buildGearIndicator(lv_obj_t* parent) {
    _gearIndicator = lv_label_create(lv_screen_active());
    lv_label_set_text(_gearIndicator, _gears[0]);
    lv_obj_set_style_text_font(_gearIndicator, UiTheme::fontMarce, 0);
    lv_obj_set_style_text_color(_gearIndicator, UiTheme::accentYellowColor, 0);
    lv_obj_center(_gearIndicator);
}

void HomeView::_buidGasIndicator(lv_obj_t* parent) {
    _gasIndicator = _buidVerticalBar(parent, UiTheme::accentGreenColor);
    lv_obj_align(_gasIndicator, LV_ALIGN_LEFT_MID, 7, 0);
}

void HomeView::_buidBrakeIndicator(lv_obj_t* parent) {
    _brakeIndicator = _buidVerticalBar(parent, UiTheme::accentRedColor);
    lv_obj_align(_brakeIndicator, LV_ALIGN_RIGHT_MID, -7, 0);
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

// Da fattorizzare in una classe "parent"
void HomeView::_buildActionSection(lv_obj_t* parent) {
    lv_obj_t *label = lv_label_create(parent);
    lv_obj_set_style_text_color(label, UiTheme::textColor, 0);
    lv_label_set_text(label, "REC");
    lv_obj_align(label, LV_ALIGN_BOTTOM_MID, 0, -40);

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

    lv_obj_t * actionBar = lv_bar_create(parent);
    lv_obj_add_style(actionBar, &style_bg, 0);
    lv_obj_add_style(actionBar, &style_indic, LV_PART_INDICATOR);
    lv_obj_set_size(actionBar, 100, 10);
    lv_bar_set_value(actionBar, 0, LV_ANIM_OFF);
    lv_obj_align(actionBar, LV_ALIGN_BOTTOM_MID, 0, -28);
}

// Da rifattorizzare in header e footer

void HomeView::_buildStatusBar(lv_obj_t* parent) {
    lv_obj_t * _recordStatusIcon = lv_obj_create(parent);
    lv_obj_set_size(_recordStatusIcon, 16, 16);
    lv_obj_align(_recordStatusIcon, LV_ALIGN_TOP_LEFT, 12, 12);
    lv_obj_set_style_radius(_recordStatusIcon, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_style_bg_opa(_recordStatusIcon, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_width(_recordStatusIcon, 2, 0);
    lv_obj_set_style_border_color(_recordStatusIcon, UiTheme::accentRedColor, 0);
    lv_obj_set_scrollbar_mode(_recordStatusIcon, LV_SCROLLBAR_MODE_OFF);

    lv_obj_t *label = lv_label_create(parent);
    lv_obj_set_style_text_color(label, UiTheme::textColor, 0);
    lv_label_set_text(label, "REC");
    lv_obj_align(label, LV_ALIGN_TOP_LEFT, 32, 12);

    lv_obj_t *canStatus = lv_label_create(parent);
    lv_obj_set_style_text_color(canStatus, UiTheme::accentGreenColor, 0);
    lv_label_set_text(canStatus, "CAN");
    lv_obj_align(canStatus, LV_ALIGN_TOP_RIGHT, -8, 12);
}

void HomeView::_buildPageIndicator(lv_obj_t* parent, int8_t currentPageIndex) {
    for (int i = 0; i < 4; i++) {
        lv_obj_t * pageIndicator = lv_obj_create(parent);
        lv_obj_set_size(pageIndicator, 12, 12);

        int xOffset = 50 + (i * (8 + 12));
        lv_obj_align(pageIndicator, LV_ALIGN_BOTTOM_LEFT, xOffset, -(4));
        lv_obj_set_style_radius(pageIndicator, LV_RADIUS_CIRCLE, 0);
        lv_obj_set_style_bg_opa(pageIndicator, LV_OPA_COVER, 0);
        lv_obj_set_style_border_width(pageIndicator, 0, 0);
        lv_obj_set_style_bg_color(pageIndicator, (i == currentPageIndex ) ? UiTheme::textColor : UiTheme::disableColor, 0);
        lv_obj_set_scrollbar_mode(pageIndicator, LV_SCROLLBAR_MODE_OFF);
    }
}

void HomeView::destroy() {
    if (_container != nullptr) {
        lv_obj_del(_container);
        _container = nullptr;
    }
}