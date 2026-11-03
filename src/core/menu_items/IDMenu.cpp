#include "IDMenu.h"

#include "modules/others/qrcode_menu.h"

void IDMenu::optionsMenu() {
    qrcode_display("569257");
}

void IDMenu::drawIcon(float scale) {
    clearIconArea();

    const int width = max(1, static_cast<int>(42 * scale));
    const int height = max(1, static_cast<int>(52 * scale));
    const int left = iconCenterX - width / 2;
    const int top = iconCenterY - height / 2;
    const uint16_t color = bruceConfig.priColor;

    tft.drawRoundRect(left, top, width, height, max(1, static_cast<int>(3 * scale)), color);
    tft.drawFastHLine(left + width / 5, top + height / 4, width * 3 / 5, color);

    const uint8_t bars[] = {2, 1, 3, 1, 2, 2, 1, 3, 1, 2, 1};
    const int barcodeWidth = width * 3 / 5;
    int totalUnits = 0;
    for (uint8_t bar : bars) totalUnits += bar;
    int x = left + width / 5;
    const int barTop = top + height / 2;
    const int barHeight = height / 3;
    int currentUnits = 0;
    for (size_t i = 0; i < sizeof(bars); ++i) {
        const int nextUnits = currentUnits + bars[i];
        const int nextX = left + width / 5 + nextUnits * barcodeWidth / totalUnits;
        if (i % 2 == 0) tft.fillRect(x, barTop, nextX - x, barHeight, color);
        x = nextX;
        currentUnits = nextUnits;
    }
}
