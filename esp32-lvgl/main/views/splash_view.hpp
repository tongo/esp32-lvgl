#pragma once
#include "lvgl.h"
#include "ui_theme.hpp"

class SplashView {
public:
    void build(lv_obj_t* parent);
    void destroy();

private:
    lv_obj_t* _container = nullptr;

    void _buildTitle(lv_obj_t* parent);
    void _buildSubtitle(lv_obj_t* parent);
    void _buildSpinner(lv_obj_t* parent);
};