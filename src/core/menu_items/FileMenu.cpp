#include "FileMenu.h"
#include "core/display.h"
#include "core/massStorage.h"
#include "core/sd_functions.h"
#include "core/utils.h"
#include "core/wifi/webInterface.h"
#include "core/connect/file_sharing.h"
#include "core/connect/serial_commands.h"

void FileMenu::optionsMenu() {
    options.clear();
    if (setupSdCard()) options.push_back({"SD Card", [=]() { loopSD(SD); }});
    options.push_back({"LittleFS", [=]() { loopSD(LittleFS); }});
    options.push_back({"WebUI", loopOptionsWebUi});

#if !defined(LITE_VERSION)
    options.push_back({"Connect", [=]() {
        std::vector<Option> connectOpts = {
            {"Send File", [=]() { FileSharing().sendFile(); }        },
            {"Recv File", [=]() { FileSharing().receiveFile(); }     },
            {"Send Cmds", [=]() { EspSerialCmd().sendCommands(); }   },
            {"Recv Cmds", [=]() { EspSerialCmd().receiveCommands(); }},
            {"Back",      [=]() { optionsMenu(); }                   }
        };
        loopOptions(connectOpts, MENU_TYPE_SUBMENU, "Connect");
    }});
#endif

#if defined(SOC_USB_OTG_SUPPORTED)
    options.push_back({"Mass Storage", [=]() { MassStorage(); }});
#endif
    addOptionToMainMenu();

    loopOptions(options, MENU_TYPE_SUBMENU, "Files");
}
void FileMenu::drawIcon(float scale) {
    clearIconArea();
    int iconW = max(1, (int)(scale * 42));
    int iconH = max(1, (int)(scale * 54));
    int iconX = iconCenterX - iconW / 2;
    int iconY = iconCenterY - iconH / 2;
    int foldSize = min(iconW / 3, iconH / 4);
    int right = iconX + iconW;
    int bottom = iconY + iconH;
    uint16_t color = bruceConfig.priColor;

    tft.drawLine(iconX, iconY, right - foldSize, iconY, color);
    tft.drawLine(right - foldSize, iconY, right, iconY + foldSize, color);
    tft.drawLine(right, iconY + foldSize, right, bottom, color);
    tft.drawLine(right, bottom, iconX, bottom, color);
    tft.drawLine(iconX, bottom, iconX, iconY, color);
    tft.drawLine(right - foldSize, iconY, right - foldSize, iconY + foldSize, color);
    tft.drawLine(right - foldSize, iconY + foldSize, right, iconY + foldSize, color);

    int lineStart = iconX + iconW / 5;
    int lineEnd = right - iconW / 5;
    int lineGap = max(1, iconH / 6);
    for (int lineY = iconY + foldSize + lineGap; lineY < bottom - lineGap; lineY += lineGap) {
        tft.drawFastHLine(lineStart, lineY, lineEnd - lineStart, color);
    }
}
