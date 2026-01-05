#pragma once
#include "lvgl.h"
#include "ui_theme.hpp"
#include "base_view.hpp"

class HomeView : public BaseView {
public:
    void _buildContent() override;
    void setGear(uint8_t gear);
    
private:
    lv_obj_t* _recordStatusIcon = nullptr;
    lv_obj_t* _canStatus = nullptr;
    static inline const char* _gears[] = {"N", "1", "2", "3", "4", "5", "6"};
    lv_obj_t* _gearIndicator = nullptr;
    lv_obj_t* _gasIndicator;
    lv_obj_t* _brakeIndicator;

    void _buildGearIndicator(lv_obj_t* parent);
    void _buidGasIndicator(lv_obj_t* parent);
    void _buidBrakeIndicator(lv_obj_t* parent);
    lv_obj_t* _buidVerticalBar(lv_obj_t* parent, lv_color_t color);

    void _buildActionSection(lv_obj_t* parent);
};