#pragma once
#include "lvgl.h"
#include "ui_theme.hpp"

class SplashView {
public:
    void build(lv_obj_t* parent);
    void destroy();

private:
    lv_obj_t* container = nullptr;

    void buildTitle(lv_obj_t* parent);
    void buildSubtitle(lv_obj_t* parent);
    void buildSpinner(lv_obj_t* parent);
};