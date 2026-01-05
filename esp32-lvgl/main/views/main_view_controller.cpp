#include "main_view_controller.hpp"
#include "ui_theme.hpp"
#include "home_view.hpp"
#include "info_view.hpp"

MainViewController::~MainViewController() {
    if (_screen) {
        lv_obj_del(_screen);
        _screen = nullptr;
    }
}

void MainViewController::build() {
    _screen = lv_obj_create(nullptr);
    lv_obj_set_size(_screen, LV_PCT(100), LV_PCT(100));
    
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

    _buildFooter();

    this->goToPage(PageIndex::HOME);
    
    // Timer per testare il cambio pagina
    lv_timer_create([](lv_timer_t* timer) {
        MainViewController* controller = static_cast<MainViewController*>(lv_timer_get_user_data(timer));
        controller->goToPage(PageIndex::INFO); // O l'indice della tua seconda View
        lv_timer_delete(timer); // Eliminiamo il timer dopo il primo colpo
    }, 5000, this);
}

void MainViewController::_buildHeader() {
    _header = new HeaderView();
    _header->build(_screen);
}

void MainViewController::_buildFooter() {
    _footer = new FooterView();
    _footer->build(_screen);
}

void MainViewController::goToPage(PageIndex index) {
    lv_obj_t* newPageObj = nullptr;

    // 1. Istanziamo la View passando _contentArea
    switch (index) {
        case PageIndex::HOME: {
            HomeView view;
            view.build(_contentArea);
            newPageObj = view.getContainer();
            break;
        }
        case PageIndex::INFO: {
            InfoView view;
            view.build(_contentArea);
            newPageObj = view.getContainer();
            break;
        }
        case PageIndex::SETTINGS: {
            break;
        }
        case PageIndex::SHUTDOWN: {
            break;
        }
    }

    if (!newPageObj) return;

    // 2. Setup per l'animazione
    lv_obj_update_layout(_contentArea);
    lv_coord_t width = lv_obj_get_width(_contentArea);
    _footer->setActivePage(static_cast<uint8_t>(index));

    if (_currentPage == nullptr) {
        // È la prima pagina: niente animazione
        _currentPage = newPageObj;
        lv_obj_set_pos(newPageObj, 0, 0);
    } else {
        // È un cambio pagina: esegui lo slide
        _animateSlide(newPageObj, width);
    }
}

void MainViewController::_animateSlide(lv_obj_t* newPage, lv_coord_t width) {
    lv_obj_t* oldPage = _currentPage;
    _currentPage = newPage;

    // Posiziona la nuova pagina a destra
    lv_obj_set_x(newPage, width);

    // Animazione In
    lv_anim_t inAnimation;
    lv_anim_init(&inAnimation);
    lv_anim_set_var(&inAnimation, newPage);
    lv_anim_set_values(&inAnimation, width, 0);
    lv_anim_set_duration(&inAnimation, 500);
    lv_anim_set_exec_cb(&inAnimation, [](void* var, int32_t v) { lv_obj_set_x((lv_obj_t*)var, v); });
    lv_anim_start(&inAnimation);

    // Animazione Out
    lv_anim_t outAnimation;
    lv_anim_init(&outAnimation);
    lv_anim_set_var(&outAnimation, oldPage);
    lv_anim_set_values(&outAnimation, 0, -width);
    lv_anim_set_duration(&outAnimation, 500);
    lv_anim_set_exec_cb(&outAnimation, [](void* var, int32_t v) { lv_obj_set_x((lv_obj_t*)var, v); });
    lv_anim_set_ready_cb(&outAnimation, [](lv_anim_t* animation) { lv_obj_del((lv_obj_t*)animation->var); });
    lv_anim_start(&outAnimation);
}