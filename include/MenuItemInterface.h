#ifndef __MENU_ITEM_INTERFACE_H__
#define __MENU_ITEM_INTERFACE_H__

#include "core/display.h"
#include <globals.h>
#if defined(ASTRA_DEVANAGARI_MENU_TITLES)
#include "astra_menu_titles.h"
#endif

class MenuItemInterface {
public:
    virtual ~MenuItemInterface() = default;
    virtual void optionsMenu(void) = 0;
    virtual void drawIcon(float scale = 1) = 0;
    virtual void drawIconImg() {
        drawImg(
            *bruceConfig.themeFS(),
            bruceConfig.getThemeItemImg(themePath()),  // const String& - no heap alloc
            0,
            imgCenterY,
            true,
            bruceConfig.theme.gifDuration,
            false
        );
    }
    virtual bool hasTheme() = 0;
    virtual const String& themePath() = 0;

    bool checkTheme() { return hasTheme() && themePath().length() > 0; }
    String getName() const { return String(_name); }

    void draw(float scale = 1) {
        if (rotation != bruceConfigPins.rotation) resetCoordinates();
        tft.fillRect(0, 27, tftWidth, tftHeight - 27, bruceConfig.bgColor);
        if (!checkTheme()) {
            drawIcon(scale * 0.58f);
            drawArrows(scale * 0.65f);
            drawTitle(scale);
        } else {
            if (bruceConfig.theme.label)
                drawTitle(scale); // If using .GIF, labels are draw after complete, which takes some time
            drawIconImg();
            if (bruceConfig.theme.label) drawTitle(scale); // Makes sure to draw over the image
        }
        drawStatusBar();
    }

    void drawArrows(float scale = 1) {
        tft.fillRect(arrowAreaX, iconAreaY, arrowAreaW, iconAreaH, ASTRA_PANEL_COLOR);
        tft.fillRect(
            tftWidth - arrowAreaX - arrowAreaW, iconAreaY, arrowAreaW, iconAreaH, ASTRA_PANEL_COLOR
        );

        int arrowSize = scale * 10;
        int lineWidth = scale * 3;

        int arrowX = BORDER_PAD_X + 1.5 * arrowSize;
        int arrowY = iconCenterY + 1.5 * arrowSize;

        // Left Arrow
        tft.drawWideLine(
            arrowX,
            arrowY,
            arrowX + arrowSize,
            arrowY + arrowSize,
            lineWidth,
            bruceConfig.priColor,
            ASTRA_PANEL_COLOR
        );
        tft.drawWideLine(
            arrowX,
            arrowY,
            arrowX + arrowSize,
            arrowY - arrowSize,
            lineWidth,
            bruceConfig.priColor,
            ASTRA_PANEL_COLOR
        );

        // Right Arrow
        tft.drawWideLine(
            tftWidth - arrowX,
            arrowY,
            tftWidth - arrowX - arrowSize,
            arrowY + arrowSize,
            lineWidth,
            bruceConfig.priColor,
            ASTRA_PANEL_COLOR
        );
        tft.drawWideLine(
            tftWidth - arrowX,
            arrowY,
            tftWidth - arrowX - arrowSize,
            arrowY - arrowSize,
            lineWidth,
            bruceConfig.priColor,
            ASTRA_PANEL_COLOR
        );
    }

    void drawTitle(float scale = 1) {
#if defined(ARDUINO_M5STACK_CARDPUTER)
        int titleY = tftHeight - LH * FM - 22;
#else
        int titleY = tftHeight - LH * FM - 10;
#endif

#if defined(ASTRA_DEVANAGARI_MENU_TITLES)
        const AstraMenuTitleBitmap *title = astraMenuTitleBitmap(_name);
        if (title) {
            constexpr int sourceInsetX = 1;
            constexpr int sourceInsetY = 1;
            const int sourceHeight = title->height - 2 * sourceInsetY;
            const int sourceWidth = title->width - 2 * sourceInsetX;
            const int bitmapWidth = max(1, (int)(sourceWidth * scale + 0.5f));
            const int bitmapHeight = max(1, (int)(sourceHeight * scale + 0.5f));
            const int titleX = iconCenterX - bitmapWidth / 2;
            const int titleY = 112 - bitmapHeight;
            drawScaledXBitmap(
                *title,
                sourceInsetX,
                sourceInsetY,
                sourceWidth,
                sourceHeight,
                titleX,
                titleY,
                bitmapWidth,
                bitmapHeight,
                bruceConfig.priColor
            );
            const char *label = englishTitle();
            if (label) {
                tft.setTextSize(1);
                tft.setTextColor(bruceConfig.secColor, bruceConfig.bgColor);
                tft.drawCentreString(label, iconCenterX, 116, 1);
            }
            return;
        }
#endif

        tft.setTextSize(FM);
        tft.drawPixel(0, 0, 0);
        tft.fillRect(arrowAreaX, titleY, tftWidth - 2 * arrowAreaX, LH * FM, ASTRA_PANEL_COLOR);
        tft.setTextColor(bruceConfig.priColor, ASTRA_PANEL_COLOR);
        int nchars = (tftWidth - 16) / (LW * FM);
        tft.drawCentreString(getName().substring(0, nchars), iconCenterX, titleY, 1);
        tft.drawFastHLine(iconCenterX - 12, titleY + LH * FM - 1, 24, bruceConfig.priColor);
    }

protected:
    const char *_name = "";
    uint8_t rotation = ROTATION;

    int iconAreaH =
        ((tftHeight - 2 * BORDER_PAD_Y) % 2 == 0 ? tftHeight - 2 * BORDER_PAD_Y
                                                 : tftHeight - 2 * BORDER_PAD_Y + 1);
    int iconAreaW = iconAreaH;

    int iconCenterX = tftWidth / 2;
    int iconCenterY = tftHeight / 2 - 7;
    int imgCenterY = 13;

    int iconAreaX = iconCenterX - iconAreaW / 2;
    int iconAreaY = iconCenterY - iconAreaH / 2;

    int arrowAreaX = BORDER_PAD_X;
    int arrowAreaW = iconAreaX - arrowAreaX;

    MenuItemInterface(const char *name) : _name(name) {}

    void clearIconArea(void) {
        tft.fillRect(iconAreaX, iconAreaY, iconAreaW, iconAreaH, ASTRA_PANEL_COLOR);
    }
    void clearImgArea(void) { tft.fillRect(7, 27, tftWidth - 14, tftHeight - 34, ASTRA_PANEL_COLOR); }

#if defined(ASTRA_DEVANAGARI_MENU_TITLES)
    void drawScaledXBitmap(
        const AstraMenuTitleBitmap &title, int sourceX, int sourceY, int sourceWidth, int sourceHeight,
        int x, int y, int width, int height, uint16_t color
    ) {
        const int rowBytes = (title.width + 7) / 8;
        for (int destY = 0; destY < height; destY++) {
            const int bitmapY = sourceY + sourceHeight - 1 - destY * sourceHeight / height;
            int runStart = -1;
            for (int destX = 0; destX <= width; destX++) {
                bool set = false;
                if (destX < width) {
                    const int bitmapX = sourceX + destX * sourceWidth / width;
                    const uint8_t bits = pgm_read_byte(title.bitmap + bitmapY * rowBytes + bitmapX / 8);
                    set = (bits & (1 << (bitmapX & 7))) != 0;
                }
                if (set && runStart < 0) runStart = destX;
                if (!set && runStart >= 0) {
                    tft.drawFastHLine(x + runStart, y + destY, destX - runStart, color);
                    runStart = -1;
                }
            }
        }
    }
#endif

    void resetCoordinates(void) {
        // Recalculate Center and ared due to portrait/landscape changings
        if (tftWidth > tftHeight) {
            iconAreaH =
                ((tftHeight - 2 * BORDER_PAD_Y) % 2 == 0 ? tftHeight - 2 * BORDER_PAD_Y
                                                         : tftHeight - 2 * BORDER_PAD_Y + 1);
        } else {
            iconAreaH =
                ((tftWidth - 2 * BORDER_PAD_Y) % 2 == 0 ? tftWidth - 2 * BORDER_PAD_Y
                                                        : tftWidth - 2 * BORDER_PAD_Y + 1);
        }

        iconAreaW = iconAreaH;

        iconCenterX = tftWidth / 2;
        iconCenterY = tftHeight / 2 - 7;

        iconAreaX = iconCenterX - iconAreaW / 2;
        iconAreaY = iconCenterY - iconAreaH / 2;

        arrowAreaX = BORDER_PAD_X;
        arrowAreaW = iconAreaX - arrowAreaX;

        rotation = bruceConfigPins.rotation;
    }

private:
#if defined(ASTRA_DEVANAGARI_MENU_TITLES)
    const char *englishTitle() const {
        if (strcmp(_name, "Suraksha / Wi-Fi") == 0) return "Wi-Fi";
        if (strcmp(_name, "Sandesh / BLE") == 0) return "Bluetooth";
        if (strcmp(_name, "Radio / RF") == 0) return "Sub-GHz Radio";
        if (strcmp(_name, "NRF24") == 0) return "NRF24";
        if (strcmp(_name, "LoRa") == 0) return "LoRa";
        if (strcmp(_name, "FM") == 0) return "FM Radio";
        if (strcmp(_name, "Infrared / IR") == 0) return "Infrared";
        if (strcmp(_name, "Ethernet") == 0) return "Ethernet";
        if (strcmp(_name, "Disha / GPS") == 0) return "GPS";
        if (strcmp(_name, "NFC / RFID") == 0) return "NFC / RFID";
        if (strcmp(_name, "Faelein / Files") == 0) return "Files";
        if (strcmp(_name, "Script") == 0) return "Scripts";
        if (strcmp(_name, "Samay / Clock") == 0) return "Clock";
        if (strcmp(_name, "Sangeet / Music") == 0) return "Music";
        if (strcmp(_name, "Anya / Others") == 0) return "More";
        if (strcmp(_name, "Vyavastha / Settings") == 0) return "Settings";
        return nullptr;
    }
#endif
};

#endif // __MENU_ITEM_INTERFACE_H__
