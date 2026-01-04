#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/spi_master.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_vendor.h" // Qui si trova esp_lcd_new_panel_st7789
#include "esp_lcd_panel_ops.h"
#include "esp_lvgl_port.h"
#include "ui_theme.hpp"
#include "splash_view.hpp"
#include "home_view.hpp"

// Definizione GPIO per HSPI (SPI2 su ESP32)
#define LCD_HOST         SPI2_HOST
#define PIN_NUM_MOSI     13
#define PIN_NUM_CLK      14
#define PIN_NUM_CS       15
#define PIN_NUM_DC       25
#define PIN_NUM_RST      26

// Risoluzione specifica del tuo display
#define LCD_H_RES        172
#define LCD_V_RES        320


// static lv_obj_t * mainLabel;
// static const char* valori[] = {"N", "1", "2", "3", "4", "5", "6"};
// static int indiceValore = 0;


// // Callback per il lampeggio: alterna giallo e bianco basandosi sul valore dell'animazione
// static void animColorCb(void * var, int32_t v) {
//     lv_obj_t * obj = (lv_obj_t *)var;
//     // Se v è pari (0, 2, 4...) -> Giallo, se dispari (1, 3, 5...) -> Bianco
//     if (v % 2 == 0) {
//         lv_obj_set_style_text_color(obj, lv_palette_main(LV_PALETTE_YELLOW), 0);
//     } else {
//         lv_obj_set_style_text_color(obj, lv_color_white(), 0);
//     }
// }

// // Funzione chiamata ogni 5 secondi
// static void updateLabelTimerCb(lv_timer_t * timer) {
//     // 1. Aggiorna il valore della label
//     indiceValore = (indiceValore + 1) % 7; // Cicla tra 0 e 6
//     lv_label_set_text(mainLabel, valori[indiceValore]);

//     // 2. Configura l'animazione di lampeggio (Yellow-White ogni 100ms per 1s)
//     lv_anim_t a;
//     lv_anim_init(&a);
//     lv_anim_set_var(&a, mainLabel);
    
//     // Eseguiamo 10 scatti (100ms * 10 = 1000ms)
//     // I valori passati alla callback andranno da 0 a 10
//     lv_anim_set_values(&a, 0, 10); 
//     lv_anim_set_duration(&a, 1000); // Totale 1 secondo
//     lv_anim_set_exec_cb(&a, animColorCb);
    
//     // Al termine, assicuriamoci che torni Giallo fisso
//     lv_anim_set_completed_cb(&a, [](lv_anim_t * anim) {
//         lv_obj_set_style_text_color((lv_obj_t *)anim->var, lv_palette_main(LV_PALETTE_YELLOW), 0);
//     });

//     lv_anim_start(&a);
// }

extern "C" void app_main(void) {
    // 1. Configurazione del Bus SPI
    spi_bus_config_t buscfg = {};
    buscfg.mosi_io_num = PIN_NUM_MOSI;
    buscfg.miso_io_num = -1;
    buscfg.sclk_io_num = PIN_NUM_CLK;
    buscfg.quadwp_io_num = -1;
    buscfg.quadhd_io_num = -1;
    // Dimensione massima del buffer di trasferimento
    buscfg.max_transfer_sz = LCD_H_RES * 40 * sizeof(uint16_t);
    ESP_ERROR_CHECK(spi_bus_initialize(LCD_HOST, &buscfg, SPI_DMA_CH_AUTO));

    // 2. Pannello IO: Definisce come inviare i comandi (SPI)
    esp_lcd_panel_io_handle_t io_handle = NULL;
    esp_lcd_panel_io_spi_config_t io_config = {};
    io_config.dc_gpio_num = PIN_NUM_DC;
    io_config.cs_gpio_num = PIN_NUM_CS;
    io_config.pclk_hz = 40 * 1000 * 1000; // 40MHz
    io_config.lcd_cmd_bits = 8;
    io_config.lcd_param_bits = 8;
    io_config.spi_mode = 0;
    io_config.trans_queue_depth = 10;
    ESP_ERROR_CHECK(esp_lcd_new_panel_io_spi(LCD_HOST, &io_config, &io_handle));

    // 3. Pannello Driver: Inizializza il controller ST7789 specifico
    esp_lcd_panel_handle_t panel_handle = NULL;
    esp_lcd_panel_dev_config_t panel_config = {};
    panel_config.reset_gpio_num = PIN_NUM_RST;
    panel_config.rgb_ele_order = LCD_RGB_ELEMENT_ORDER_RGB;
    panel_config.bits_per_pixel = 16;
    
    // Funzione nativa di esp_lcd inclusa in IDF 5.5
    ESP_ERROR_CHECK(esp_lcd_new_panel_st7789(io_handle, &panel_config, &panel_handle));
    
    ESP_ERROR_CHECK(esp_lcd_panel_reset(panel_handle));
    ESP_ERROR_CHECK(esp_lcd_panel_init(panel_handle));

    // Per un 172x320, l'offset X tipico è (240 - 172) / 2 = 34 pixel.
    ESP_ERROR_CHECK(esp_lcd_panel_set_gap(panel_handle, 34, 0));
    
    // Nota: l'ordine dei pixel e l'inversione colore dipendono dal modulo specifico
    ESP_ERROR_CHECK(esp_lcd_panel_invert_color(panel_handle, true)); 
    ESP_ERROR_CHECK(esp_lcd_panel_disp_on_off(panel_handle, true));

    // 4. Inizializzazione LVGL Port
    const lvgl_port_cfg_t lvgl_cfg = ESP_LVGL_PORT_INIT_CONFIG();
    ESP_ERROR_CHECK(lvgl_port_init(&lvgl_cfg));

    const lvgl_port_display_cfg_t disp_cfg = {
        .io_handle = io_handle,
        .panel_handle = panel_handle,
        .buffer_size = LCD_H_RES * 40,
        .double_buffer = false,
        .hres = LCD_H_RES,
        .vres = LCD_V_RES,
        .monochrome = false,
        .rotation = {
            .swap_xy = false,
            .mirror_x = true,
            .mirror_y = true,
        },
        .flags = {
            .buff_dma = true,
            .swap_bytes = true
        }
    };
    
    lv_display_t *disp = lvgl_port_add_disp(&disp_cfg);

    // Config. tema default
    lv_theme_t * th = lv_theme_default_init(disp, UiTheme::textColor, UiTheme::accentYellowColor, true, UiTheme::fontTesto);
    lv_display_set_theme(disp, th);

    // 5. Creazione della UI "Hello World"
    // lvgl_port_lock garantisce che l'operazione sia thread-safe
    if (lvgl_port_lock(0)) {
        lv_obj_set_style_bg_color(lv_screen_active(), UiTheme::bgColor, 0);
        
        // SplashView* splashView = new SplashView();
        // splashView->build(lv_screen_active());

        HomeView* homeView = new HomeView();
        homeView->build(lv_screen_active());

        lvgl_port_unlock();
    }
}