#include "Projector-B-Gone.h"
#include "TV-B-Gone.h"
#include "core/display.h"
#include "core/sd_functions.h"
#include "core/settings.h"
#include "custom_ir.h"

namespace {
constexpr char PROJECTOR_CODES_FILE[] = "/infrared/Projector_B_Gone/Projectors.ir";
}

void StartProjectorBGone() {
    checkIrTxPin();
    if (!setupLittleFS()) {
        displayError("LittleFS unavailable.", true);
        return;
    }

    displayTextLine("Sending projector codes...");

    const uint8_t configuredRepeats = bruceConfigPins.irTxRepeats;
    bruceConfigPins.irTxRepeats = 0;
    const bool completed = txIrFile(&LittleFS, PROJECTOR_CODES_FILE, false, 205);
    bruceConfigPins.irTxRepeats = configuredRepeats;

    displayTextLine(completed ? "Projector scan complete" : "Projector scan stopped");
    delay(1500);
}
