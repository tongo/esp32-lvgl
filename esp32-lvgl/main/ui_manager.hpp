#pragma once
#include "lvgl.h"
#include "splash_view.hpp"
#include "main_view_controller.hpp"

class UiManager {
public:
    static UiManager& getInstance() {
        static UiManager instance;
        return instance;
    }
    void start();

private:
    UiManager() = default;
    
    SplashView* _splashView = nullptr;
    MainViewController* _mainViewController = nullptr;

    static void _onSplashTimerFinished(lv_timer_t* timer);
    void _transitionToMain();
    void _cleanupSplash();
};