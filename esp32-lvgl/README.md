# RTC Example

## Esporre la porta USB via rete (sul Mac):

```
esp_rfc2217_server -v -p 4000 /dev/cu.usbserial-0001
```

## Lanciare i comandi dal Docker:

Build: usare il bottone di VSCode


Monitor
```
idf.py --port 'rfc2217://host.docker.internal:4000?ign_set_control' monitor
```

Flash
```
idf.py --port 'rfc2217://host.docker.internal:4000?ign_set_control' flash
```

## Creazione Font LVGL
```
lv_font_conv --bpp 4 --size 180 --no-compress --font ./fonts/SairaStencilOne-Regular.ttf --symbols N123456 --format lvgl -o ./main/font_marce.c
```

Il file così creato non compila, sere eliminare gli include iniziali e sostituire con un semplice:
```
#include "lvgl.h"
```