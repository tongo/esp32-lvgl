#pragma once
#include "lvgl.h"
#include "header_view.hpp"

enum class PageIndex {
    HOME = 0,
    INFO,
    SETTINGS,
    SHUTDOWN
};

class MainViewController {
public:
    MainViewController() = default;
    ~MainViewController();

    void build();
    
    void goToPage(PageIndex index);

    lv_obj_t* getScreen() { return _screen; }

private:
    lv_obj_t* _screen = nullptr;
    HeaderView* _header = nullptr;
    lv_obj_t* _footer = nullptr;
    lv_obj_t* _contentArea = nullptr;
    lv_obj_t* _currentPage = nullptr;

    PageIndex _currentPageIndex;

    void _buildHeader();
    void _buildFooter();
    void _animateSlide(lv_obj_t* newPage, lv_coord_t width);
};