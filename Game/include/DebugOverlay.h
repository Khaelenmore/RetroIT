//
// Created by silverwing on 11/30/25.
//

#ifndef IMPRESSIVETITLE_DEBUGOVERLAY_H
#define IMPRESSIVETITLE_DEBUGOVERLAY_H

#include "Ogre.h"

using namespace Ogre;

class DebugOverlay {
public:
    DebugOverlay(RenderWindow* window);
    void toggle();
    void show();
    void hide();
    bool isVisible();
    void updateStats();
    void setDebugText(std::string value);
private:
    RenderWindow* mWindow;
    Overlay* mDebugOverlay;
    bool mIsVisible;
    std::string mDebugText;
};

#endif //IMPRESSIVETITLE_DEBUGOVERLAY_H
