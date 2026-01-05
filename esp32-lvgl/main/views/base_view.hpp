#pragma once
#include "lvgl.h"

class BaseView {
public:
    virtual ~BaseView() = default;

    lv_obj_t* build(lv_obj_t* parent);
    lv_obj_t* getContainer() { return _container; }
    void startLongPressAnimation(uint32_t duration);
    void stopLongPressAnimation();
    void destroy();
protected:
    lv_obj_t* _container = nullptr;
    lv_obj_t* _actionBar;

    virtual void _buildContent() = 0;
    void _buildActionSection(lv_obj_t* parent, const char *actionLabel);
    
};