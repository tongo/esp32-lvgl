#pragma once
#include "lvgl.h"
#include "base_view.hpp"

#define TOTAL_PAGES_COUNT 4
#define PAGE_INDICATOR_SIZE 12
#define PAGE_INDICATOR_GAP 8
#define CONTAINER_PADDING 8

class FooterView : public BaseView {
public:
    void _buildContent() override;
    void setActivePage(uint8_t pageIndex);
    
private:
    uint8_t _currentPageIndex = 0;
    lv_obj_t* _pageIndicators[TOTAL_PAGES_COUNT];
};