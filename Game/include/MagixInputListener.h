//
// Created by silverwing on 11/30/25.
//

#ifndef IMPRESSIVETITLE_MAGIXINPUTLISTENER_H
#define IMPRESSIVETITLE_MAGIXINPUTLISTENER_H

#define OIS_DYNAMIC_LIB
#include <OIS.h>
#include "MagixHandler.h"
#include "DebugOverlay.h"

namespace Magix {
    class InputListener: public OIS::MouseListener, public OIS::KeyListener {
    public:
        InputListener (
            MagixHandler* magixHandler,
            RenderWindow* window,
            DebugOverlay* debugOverlay,
            bool bufferedKeys,
            bool bufferedMouse
        );

        void adjustMouseClipping(int width, int height);

        // MouseListener
        bool mouseMoved(const OIS::MouseEvent &e) override;
        bool mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id) override;
        bool mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id) override;

        // KeyListener
        bool keyPressed(const OIS::KeyEvent &e) override;
        bool keyReleased(const OIS::KeyEvent &e) override;

        void capture();

        ~InputListener();
    private:
        MagixHandler* mMagixHandler;
        DebugOverlay* mDebugOverlay;
        RenderWindow* mWindow;
        OIS::Mouse* mMouse;
        OIS::Keyboard* mKeyboard;
        OIS::InputManager* mInputManager;
    };
}

#endif //IMPRESSIVETITLE_MAGIXINPUTLISTENER_H
