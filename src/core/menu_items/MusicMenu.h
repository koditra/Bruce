#ifndef __MUSIC_MENU_H__
#define __MUSIC_MENU_H__

#include <MenuItemInterface.h>

class MusicMenu : public MenuItemInterface {
public:
    MusicMenu() : MenuItemInterface("Sangeet / Music") {}
    void optionsMenu(void);
    void drawIcon(float scale);
    bool hasTheme() { return false; }
    const String& themePath() override { return bruceConfig.theme.paths.files; }
};

#endif
