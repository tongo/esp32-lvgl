#pragma once
#include "lvgl.h"
#include "base_view.hpp"

class ShutdownView : public BaseView {
public:
    void _buildContent() override;
};