idf_component_register(
    SRCS "main.cpp" "saira_stancil.c"
    PRIV_REQUIRES esp_lcd esp_lvgl_port
    INCLUDE_DIRS "."
)