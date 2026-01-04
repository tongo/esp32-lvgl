file(GLOB_RECURSE SOURCES "*.cpp" "*.c")

idf_component_register(
    SRCS ${SOURCES}
    PRIV_REQUIRES
        esp_lcd esp_lvgl_port
    INCLUDE_DIRS
        "."
        "views"
)