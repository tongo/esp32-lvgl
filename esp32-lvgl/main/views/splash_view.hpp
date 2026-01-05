#pragma once
#include "lvgl.h"
#include "ui_theme.hpp"

class SplashView {
public:
    void build();
    void destroy();

    lv_obj_t* getScreen() { return _screen; }
    
private:
    lv_obj_t* _screen = nullptr;

    void _buildTitle(lv_obj_t* parent);
    void _buildSubtitle(lv_obj_t* parent);
    void _buildSpinner(lv_obj_t* parent);
};