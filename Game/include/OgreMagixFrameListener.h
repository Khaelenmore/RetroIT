#pragma once

#include "MagixFrameListener.h"
#include "MagixHandler.h"


class ogremagixFrameListener : public MagixFrameListener
{
public:
    ogremagixFrameListener(MagixHandler *magixHandler, SceneManager *sceneMgr, 
        RenderWindow* win, Camera* cam);

    // MouseListener
    bool mouseMoved(const OIS::MouseEvent &e);
    bool mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id);
    bool mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id);

    // KeyListener
    bool keyPressed(const OIS::KeyEvent &e);
    bool keyReleased(const OIS::KeyEvent &e);
};
