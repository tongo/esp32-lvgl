#include "main_view_controller.hpp"
#include "ui_theme.hpp"
#include "home_view.hpp"
#include "info_view.hpp"
#include "settings_view.hpp"
#include "shutdown_view.hpp"
#include "driver/gpio.h"

#define BUTTON_GPIO GPIO_NUM_27
#define LONG_PRESS_DURATION 3000
#define SHORT_PRESS_MAX_DURATION 400

MainViewController::~MainViewController() {
    if (_screen) {
        lv_obj_del(_screen);
        _screen = nullptr;
    }
}

void MainViewController::build() {
    _screen = lv_obj_create(nullptr);
    lv_obj_set_size(_screen, LV_PCT(100), LV_PCT(100));
    
    _setupInputDevice();

    // Layout verticale (Header -> Content -> Footer)
    lv_obj_set_flex_flow(_screen, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_style_pad_all(_screen, 0, 0);
    lv_obj_set_style_pad_row(_screen, 0, 0);

    _buildHeader();

    // Area di navigazione centrale
    _contentArea = lv_obj_create(_screen);
    lv_obj_set_width(_contentArea, LV_PCT(100));
    lv_obj_set_flex_grow(_contentArea, 1); 
    lv_obj_set_style_border_width(_contentArea, 0, 0);
    lv_obj_set_style_pad_all(_contentArea, 0, 0);
    lv_obj_set_style_bg_opa(_contentArea, 0, 0);
    lv_obj_set_style_clip_corner(_contentArea, true, 0);
    lv_obj_set_style_radius(_contentArea, 0, 0);
    lv_obj_set_scrollbar_mode(_contentArea, LV_SCROLLBAR_MODE_OFF);

    _buildFooter();
    _currentPageIndex = PageIndex::HOME;
    this->goToPage(_currentPageIndex);
}

void MainViewController::_setupInputDevice() {
    // TODO spostare in un HwManager
    gpio_config_t io_conf = {};
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pin_bit_mask = (1ULL << 27);
    io_conf.pull_down_en = GPIO_PULLDOWN_ENABLE; // Assicura che sia a 0 se non premuto
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    gpio_config(&io_conf);
    
    lv_indev_t * indev = lv_indev_create(); 
    lv_indev_set_type(indev, LV_INDEV_TYPE_BUTTON);
    lv_indev_set_user_data(indev, this);
    lv_indev_set_long_press_time(indev, LONG_PRESS_DURATION);

    // Impostiamo la funzione di lettura
    lv_indev_set_read_cb(indev, [](lv_indev_t * indev, lv_indev_data_t * data) {
        bool pressed = (gpio_get_level(BUTTON_GPIO) == 1);
        data->state = pressed ? LV_INDEV_STATE_PRESSED : LV_INDEV_STATE_RELEASED;
    });

    static lv_point_t points[1] = {{10, 10}}; 
    lv_indev_set_button_points(indev, points);

    lv_indev_add_event_cb(indev, [](lv_event_t * e) {
        lv_event_code_t code = lv_event_get_code(e);
        auto* controller = static_cast<MainViewController*>(lv_event_get_user_data(e));
        lv_indev_t* indev = lv_event_get_indev(e);

        if (code == LV_EVENT_PRESSED) {
            controller->_pressStartTime = lv_tick_get();
            if(controller->_currentPage) controller->_currentPage->startLongPressAnimation(LONG_PRESS_DURATION);
        }
        else if (code == LV_EVENT_RELEASED) {
            uint32_t duration = lv_tick_elaps(controller->_pressStartTime);
            if(controller->_currentPage) controller->_currentPage->stopLongPressAnimation();

            if (duration < SHORT_PRESS_MAX_DURATION) {
                printf("Short Click: Next\n");
                controller->goToNextPage();
            } else if (duration < LONG_PRESS_DURATION) {
                printf("Zona Morta: Nessuna azione (%ld ms)\n", duration);
            }
        }
        else if (code == LV_EVENT_LONG_PRESSED) {
            if(controller->_currentPage) controller->_currentPage->stopLongPressAnimation();
            // TODO Handle Long press action
            printf("LONG PRESS\n");
        }
    }, LV_EVENT_ALL, this);
}

void MainViewController::_buildHeader() {
    _header = new HeaderView();
    _header->build(_screen);
}

void MainViewController::_buildFooter() {
    _footer = new FooterView();
    _footer->build(_screen);
}

void MainViewController::goToNextPage() {
    uint8_t nextPageId = static_cast<int>(_currentPageIndex) + 1;
    nextPageId = (nextPageId >= 4) ? 0 : nextPageId;
    PageIndex nextPage = static_cast<PageIndex>(nextPageId);
    goToPage(nextPage);
}

void MainViewController::goToPage(PageIndex index) {
    BaseView* newPageView = nullptr;

    switch (index) {
        case PageIndex::HOME: {
            newPageView = new HomeView();
            break;
        }
        case PageIndex::INFO: {
            newPageView = new InfoView();
            break;
        }
        case PageIndex::SETTINGS: {
            newPageView = new SettingsView();
            break;
        }
        case PageIndex::SHUTDOWN: {
            newPageView = new ShutdownView();
            break;
        }
    }

    if (!newPageView) return;

    newPageView->build(_contentArea);
    _currentPageIndex = index;

    lv_obj_update_layout(_contentArea);
    lv_coord_t width = lv_obj_get_width(_contentArea);
    _footer->setActivePage(static_cast<uint8_t>(index));

    if (_currentPage == nullptr) {
        // È la prima pagina: niente animazione
        _currentPage = newPageView;
        lv_obj_set_pos(newPageView->getContainer(), 0, 0);
    } else {
        // È un cambio pagina: esegui lo slide
        _animateSlide(newPageView, width);
    }
}

void MainViewController::_animateSlide(BaseView* newPage, lv_coord_t width) {
    lv_obj_t* oldPageContainer = _currentPage->getContainer();
    lv_obj_t* newPageContainer = newPage->getContainer();
    _currentPage = newPage;
    
    // Posiziona la nuova pagina a destra
    lv_obj_set_x(newPageContainer, width);

    // Animazione IN
    lv_anim_t inAnimation;
    lv_anim_init(&inAnimation);
    lv_anim_set_var(&inAnimation, newPageContainer);
    lv_anim_set_values(&inAnimation, width, 0);
    lv_anim_set_duration(&inAnimation, 500);
    lv_anim_set_exec_cb(&inAnimation, [](void* var, int32_t v) { lv_obj_set_x((lv_obj_t*)var, v); });
    lv_anim_start(&inAnimation);

    // Animazione OUT
    lv_anim_t outAnimation;
    lv_anim_init(&outAnimation);
    lv_anim_set_var(&outAnimation, oldPageContainer);
    lv_anim_set_values(&outAnimation, 0, -width);
    lv_anim_set_duration(&outAnimation, 500);
    lv_anim_set_exec_cb(&outAnimation, [](void* var, int32_t v) { lv_obj_set_x((lv_obj_t*)var, v); });
    lv_anim_set_ready_cb(&outAnimation, [](lv_anim_t* animation) { lv_obj_del((lv_obj_t*)animation->var); });
    lv_anim_start(&outAnimation);
}