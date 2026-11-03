#ifndef __ID_MENU_H__
#define __ID_MENU_H__

#include <MenuItemInterface.h>

class IDMenu : public MenuItemInterface {
public:
    IDMenu() : MenuItemInterface("ID") {}

    void optionsMenu(void);
    void drawIcon(float scale);
    bool hasTheme() { return false; }
    const String& themePath() override { return bruceConfig.theme.paths.files; }
};

#endif
