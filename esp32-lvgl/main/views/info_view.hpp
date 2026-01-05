#pragma once
#include "lvgl.h"
#include "ui_theme.hpp"
#include "base_view.hpp"

class InfoView : public BaseView {
public:
    void _buildContent() override;
};