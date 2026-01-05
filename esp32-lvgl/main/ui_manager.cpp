#include "ui_manager.hpp"

void UiManager::start() {
    _splashView = new SplashView();
    _splashView->build();
    lv_scr_load(_splashView->getScreen());
    lv_timer_create(_onSplashTimerFinished, 5000, this);
}

void UiManager::_onSplashTimerFinished(lv_timer_t* timer) {
    UiManager* manager = static_cast<UiManager*>(lv_timer_get_user_data(timer));
    manager->_transitionToMain();
    lv_timer_delete(timer);
}

void UiManager::_transitionToMain() {
    _mainViewController = new MainViewController();
    _mainViewController->build(); // Questo crea anche la HomeView internamente

    lv_obj_add_event_cb(_mainViewController->getScreen(), [](lv_event_t* e) {
        // Quando il nuovo screen è caricato (animazione finita) libero la memoria del puntatore della _splashView (lo screen e i relativi widget vengono eliminati da LVGL in automatico)
        UiManager::getInstance()._cleanupSplash();
    }, LV_EVENT_SCREEN_LOADED, nullptr);

    lv_scr_load_anim(_mainViewController->getScreen(), LV_SCR_LOAD_ANIM_FADE_ON, 600, 0, true);
}

void UiManager::_cleanupSplash() {
    if (_splashView != nullptr) {
        delete _splashView; // Libera la memoria della classe C++
        _splashView = nullptr;
    }
}