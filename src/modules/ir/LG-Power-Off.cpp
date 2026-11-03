#include "LG-Power-Off.h"
#include "TV-B-Gone.h"
#include "core/display.h"
#include "core/sd_functions.h"
#include "core/settings.h"
#include "custom_ir.h"

namespace {
constexpr char LG_POWER_CODES_FILE[] = "/infrared/LG_Power_Off/LG_TV_Power.ir";
}

void StartLGPowerOff() {
    checkIrTxPin();
    if (!setupLittleFS()) {
        displayError("LittleFS unavailable.", true);
        return;
    }

    bool startScan = false;
    std::vector<Option> startOptions = {
        {"Send LG power-off codes", [&]() { startScan = true; }},
        {"Cancel",                 []() {}                     },
    };
    loopOptions(startOptions, MENU_TYPE_SUBMENU, "LG power keys toggle power");
    if (!startScan) return;

    displayTextLine("Use only on authorized LG TVs");
    delay(800);

    const uint8_t configuredRepeats = bruceConfigPins.irTxRepeats;
    bruceConfigPins.irTxRepeats = 0;
    const bool completed = txIrFile(&LittleFS, LG_POWER_CODES_FILE);
    bruceConfigPins.irTxRepeats = configuredRepeats;

    displayTextLine(completed ? "LG power codes sent" : "LG scan stopped");
    delay(1500);
}
