#include "MagixFrameListener.h"

#if defined(DEBUG) || defined(_DEBUG)
#define SHOW_DBG_OVERLAY true
#else
#define SHOW_DBG_OVERLAY false
#endif


//Frame Listener Functions
//================================================================================

// Constructor takes a RenderWindow because it uses that to determine input context
MagixFrameListener::MagixFrameListener(
    MagixHandler *magixHandler,
    SceneManager *sceneMgr,
    RenderWindow* win,
    Camera* cam,
    DebugOverlay* debugOverlay,
    bool bufferedKeys,
    bool bufferedMouse
):
    mWindow(win),
    mDebugOverlay(debugOverlay),
    mInputManager(0),
    mMouse(0),
    mKeyboard(0),
    mSceneMgr(sceneMgr),
    mMagixHandler(magixHandler)
{
    using namespace OIS;

    LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
    ParamList pl;
    size_t windowHnd = 0;
    std::ostringstream windowHndStr;

    win->getCustomAttribute("WINDOW", &windowHnd);
    windowHndStr << windowHnd;
    pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

    bool useWindowsCursor = false;
    std::ifstream inFile("useWindowsCursor.dat");

    if(inFile.good())
    {
        useWindowsCursor = true;
    }

    inFile.close();

    if(useWindowsCursor)
    {
        #if defined OIS_WIN32_PLATFORM
        pl.insert(std::make_pair(std::string("w32_mouse"),
            std::string("DISCL_FOREGROUND")));
        pl.insert(std::make_pair(std::string("w32_mouse"),
            std::string("DISCL_NONEXCLUSIVE")));
        //pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_FOREGROUND")));
        //pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_NONEXCLUSIVE")));
       #elif defined OIS_LINUX_PLATFORM
        pl.insert(std::make_pair(std::string("x11_mouse_grab"),
            std::string("false")));
        pl.insert(std::make_pair(std::string("x11_mouse_hide"),
            std::string("true")));
        pl.insert(std::make_pair(std::string("x11_keyboard_grab"), 
            std::string("true")));
        //pl.insert(std::make_pair(std::string("XAutoRepeatOn"), std::string("true")));
        #endif
        
        #ifdef __WIN32__
        if(ShowCursor(false) < -1)
        {
            ShowCursor(true);
        }
        #endif
    }

    mInputManager = InputManager::createInputSystem(pl);

    //Create all devices (We only catch joystick exceptions here, as, most people have Key/Mouse)
    mKeyboard = static_cast<Keyboard*>(mInputManager->createInputObject(
        OISKeyboard, bufferedKeys));
    mMouse = static_cast<Mouse*>(mInputManager->createInputObject(OISMouse,
        bufferedMouse));

    //See if can be untied from frameListener
    mInputListener = new Magix::InputListener(magixHandler, win, mMouse, mKeyboard, mDebugOverlay);

    //Set initial mouse clipping size
    windowResized(mWindow);
    showDebugOverlay(SHOW_DBG_OVERLAY);

    //Register as a Window listener
    WindowEventUtilities::addWindowEventListener(mWindow, this);

    mMouse->setEventCallback(mInputListener);
    mKeyboard->setEventCallback(mInputListener);
    mKeyboard->setTextTranslation(OIS::Keyboard::Unicode);
}


//Adjust mouse clipping area
void MagixFrameListener::windowResized(RenderWindow* rw)
{
    unsigned int width, height, depth;
    int left, top;
    rw->getMetrics(width, height, depth, left, top);

    const OIS::MouseState &ms = mMouse->getMouseState();
    ms.width = width;
    ms.height = height;
}


//Unattach OIS before window shutdown (very important under Linux)
void MagixFrameListener::windowClosed(RenderWindow* rw)
{
    //Only close for window that created OIS (the main window in these demos)
    if(rw == mWindow)
    {
        if(mInputManager)
        {
            mInputManager->destroyInputObject(mMouse);
            mInputManager->destroyInputObject(mKeyboard);

            OIS::InputManager::destroyInputSystem(mInputManager);
            mInputManager = 0;
        }
    }
}


MagixFrameListener::~MagixFrameListener()
{
    //Remove ourself as a Window listener
    WindowEventUtilities::removeWindowEventListener(mWindow, this);
    windowClosed(mWindow);
}


void MagixFrameListener::showDebugOverlay(bool show)
{
    if (show) mDebugOverlay->show();
    else mDebugOverlay->hide();
}


// Override frameStarted event to process that (don't care about frameEnded)
bool MagixFrameListener::frameStarted(const FrameEvent& evt)
{
    using namespace OIS;

    if(mWindow->isClosed())
    {
        return false;
    }

    if(mMagixHandler->getDebugText() != "")
    {
        mDebugOverlay->setDebugText(mMagixHandler->getDebugText());
    }

    //Need to capture/update each device
    mKeyboard->capture();
    mMouse->capture();

    bool contFlag = mMagixHandler->update(evt);

    if(mWindow->getViewport(0)->getBackgroundColour() != mSceneMgr->getFogColour())
    {
        mWindow->getViewport(0)->setBackgroundColour(mSceneMgr->getFogColour());
    }

    //if(!contFlag)mMagixHandler->shutdown();

    return contFlag;
}


bool MagixFrameListener::frameEnded(const FrameEvent& evt)
{
    mDebugOverlay->updateStats();
    return true;
}

