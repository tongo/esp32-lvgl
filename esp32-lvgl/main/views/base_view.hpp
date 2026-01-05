#pragma once
#include "lvgl.h"

class BaseView {
public:
    virtual ~BaseView() = default;

    lv_obj_t* build(lv_obj_t* parent) {
        _container = lv_obj_create(parent);
        lv_obj_set_size(_container, LV_PCT(100), LV_PCT(100));
        lv_obj_set_style_bg_color(_container, UiTheme::bgColor, 0);
        lv_obj_set_style_border_width(_container, 0, 0);
        lv_obj_set_style_pad_all(_container, 0, 0);
        lv_obj_set_scrollbar_mode(_container, LV_SCROLLBAR_MODE_OFF);
        lv_obj_set_style_radius(_container, 0, 0);

        _buildContent();
        return _container;
    }
    lv_obj_t* getContainer() { return _container; }
    void destroy() {
        if (_container != nullptr) {
            lv_obj_del(_container);
            _container = nullptr;
        }
    }

protected:
    lv_obj_t* _container = nullptr;
    
    virtual void _buildContent() = 0;
};