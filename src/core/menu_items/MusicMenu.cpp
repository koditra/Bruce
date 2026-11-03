#include "MusicMenu.h"

#include "core/display.h"
#include "core/sd_functions.h"
#include "core/utils.h"
#include "modules/others/audio_player.h"

void MusicMenu::optionsMenu() {
    if (!LittleFS.exists("/music")) {
        displayError("No bundled music found", true);
        return;
    }

    if (LittleFS.exists("/music/Teri_Mitti.mp3")) {
        musicPlayerUI(&LittleFS, "/music/Teri_Mitti.mp3");
        return;
    }

    loopSD(LittleFS, false, ".mp3", "/music");
}

void MusicMenu::drawIcon(float scale) {
    clearIconArea();
    int cx = iconCenterX;
    int cy = iconCenterY;
    int r = max(3, (int)(4 * scale));

    tft.fillCircle(cx - 8 * scale, cy + 9 * scale, r, bruceConfig.priColor);
    tft.fillCircle(cx + 9 * scale, cy + 5 * scale, r, bruceConfig.priColor);
    tft.drawFastVLine(cx - 8 * scale + r, cy - 14 * scale, 23 * scale, bruceConfig.priColor);
    tft.drawFastVLine(cx + 9 * scale + r, cy - 18 * scale, 23 * scale, bruceConfig.priColor);
    tft.drawFastHLine(cx - 8 * scale + r, cy - 14 * scale, 17 * scale + r, bruceConfig.priColor);
    tft.drawFastHLine(cx - 8 * scale + r, cy - 10 * scale, 17 * scale + r, bruceConfig.priColor);
}
