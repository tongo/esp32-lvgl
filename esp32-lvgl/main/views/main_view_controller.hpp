#pragma once
#include "lvgl.h"
#include "base_view.hpp"
#include "header_view.hpp"
#include "footer_view.hpp"

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
    void goToNextPage();

    lv_obj_t* getScreen() { return _screen; }

private:
    lv_obj_t* _screen = nullptr;
    HeaderView* _header = nullptr;
    FooterView* _footer = nullptr;
    lv_obj_t* _contentArea = nullptr;

    PageIndex _currentPageIndex;
    BaseView* _currentPage = nullptr;

    uint32_t _pressStartTime = 0;

    void _setupInputDevice();
    void _buildHeader();
    void _buildFooter();
    void _animateSlide(BaseView* newPage, lv_coord_t width);
};