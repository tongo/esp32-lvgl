idf_component_register(
    SRCS "main.cpp" "splash_view.cpp"
        "font_marce.c" "font_testo.c" "font_h1.c" "font_h2.c"
    PRIV_REQUIRES esp_lcd esp_lvgl_port
    INCLUDE_DIRS "."
)