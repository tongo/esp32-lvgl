#pragma once
#include "lvgl.h"
#include "splash_view.hpp"
#include "home_view.hpp"

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
    HomeView* _homeView = nullptr;

    static void _onSplashTimerFinished(lv_timer_t* timer);
    void _transitionToHome();
    void _cleanupSplash();
};