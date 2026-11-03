#include "IDMenu.h"

#include "core/utils.h"

namespace {
constexpr char CODE39_START_STOP[] = "nwnnwnwnn";
constexpr char CODE39_DIGITS[][10] = {
    "nnnwwnwnn", "wnnwnnnnw", "nnwwnnnnw", "wnwwnnnnn", "nnnwwnnnw",
    "wnnwwnnnn", "nnwwwnnnn", "nnnwnnwnw", "wnnwnnwnn", "nnwwnnwnn"
};
constexpr char ID_VALUE[] = "569257";

void drawBarcode() {
    constexpr int quietZoneModules = 10;
    constexpr int wideBarRatio = 3;
    constexpr int characters = sizeof(ID_VALUE) - 1 + 2;
    constexpr int modulesPerCharacter = 6 + 3 * wideBarRatio;
    constexpr int interCharacterGapModules = 1;
    constexpr int totalModules =
        2 * quietZoneModules + characters * modulesPerCharacter + (characters - 1) * interCharacterGapModules;
    const int margin = max(4, tftWidth / 24);
    const int moduleWidth = max(1, (tftWidth - 2 * margin) / totalModules);
    const int barcodeWidth = totalModules * moduleWidth;
    const int barcodeX = (tftWidth - barcodeWidth) / 2;
    const int barcodeY = max(25, tftHeight / 5);
    const int barcodeHeight = max(24, tftHeight * 3 / 5);
    int x = barcodeX + quietZoneModules * moduleWidth;

    tft.fillScreen(TFT_WHITE);
    tft.setTextColor(TFT_BLACK, TFT_WHITE);
    tft.setTextSize(1);
    tft.drawCentreString("ID", tftWidth / 2, 6, 1);

    for (size_t character = 0; character < characters; ++character) {
        const char *pattern = character == 0 || character == characters - 1
                                  ? CODE39_START_STOP
                                  : CODE39_DIGITS[ID_VALUE[character - 1] - '0'];
        for (size_t element = 0; element < 9; ++element) {
            const int width = (pattern[element] == 'w' ? wideBarRatio : 1) * moduleWidth;
            if (element % 2 == 0) tft.fillRect(x, barcodeY, width, barcodeHeight, TFT_BLACK);
            x += width;
        }
        if (character + 1 < characters) x += interCharacterGapModules * moduleWidth;
    }

    const int labelY = min(tftHeight - 22, barcodeY + barcodeHeight + 4);
    tft.setTextSize(2);
    tft.drawCentreString(ID_VALUE, tftWidth / 2, labelY, 1);
    tft.setTextSize(1);
    tft.drawCentreString("Code 39", tftWidth / 2, tftHeight - 10, 1);
}
}

void IDMenu::optionsMenu() {
    drawBarcode();
    delay(300);
    while (!check(EscPress) && !check(SelPress)) delay(100);
    tft.fillScreen(bruceConfig.bgColor);
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
