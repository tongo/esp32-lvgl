#include "footer_view.hpp"

void FooterView::_buildContent() {
    lv_obj_set_size(_container, LV_PCT(100), (CONTAINER_PADDING * 2 + PAGE_INDICATOR_SIZE));
    lv_obj_set_style_pad_all(_container, CONTAINER_PADDING, 0);

    for (uint8_t i = 0; i < TOTAL_PAGES_COUNT; i++) {
        lv_obj_t* pageIndicator = lv_obj_create(_container);
        lv_obj_set_size(pageIndicator, PAGE_INDICATOR_SIZE, PAGE_INDICATOR_SIZE);
        
        int xOffset = 50 - CONTAINER_PADDING + (i * (PAGE_INDICATOR_GAP + PAGE_INDICATOR_SIZE));
        lv_obj_align(pageIndicator, LV_ALIGN_LEFT_MID, xOffset, 0);
        lv_obj_set_style_radius(pageIndicator, LV_RADIUS_CIRCLE, 0);
        lv_obj_set_style_bg_opa(pageIndicator, LV_OPA_COVER, 0);
        lv_obj_set_style_border_width(pageIndicator, 0, 0);
        lv_obj_set_style_bg_color(pageIndicator, (i == _currentPageIndex ) ? UiTheme::textColor : UiTheme::disableColor, 0);
        lv_obj_set_scrollbar_mode(pageIndicator, LV_SCROLLBAR_MODE_OFF);

        _pageIndicators[i] = pageIndicator;
    }
}

void FooterView::setActivePage(uint8_t pageIndex) {
    lv_obj_t* currentPageIndicator = _pageIndicators[_currentPageIndex];
    lv_obj_set_style_bg_color(currentPageIndicator, UiTheme::disableColor, 0);
    
    lv_obj_t* newPageIndicator = _pageIndicators[pageIndex];
    lv_obj_set_style_bg_color(newPageIndicator, UiTheme::textColor, 0);
    _currentPageIndex = pageIndex;
}