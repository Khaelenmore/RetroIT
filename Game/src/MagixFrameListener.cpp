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
    DebugOverlay* debugOverlay,
    Magix::InputListener* inputListener
):
    mWindow(win),
    mDebugOverlay(debugOverlay),
    mSceneMgr(sceneMgr),
    mMagixHandler(magixHandler),
    mInputListener(inputListener)
{
    using namespace OIS;

    LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");

    //Set initial mouse clipping size
    windowResized(mWindow);
    showDebugOverlay(SHOW_DBG_OVERLAY);

    //Register as a Window listener
    WindowEventUtilities::addWindowEventListener(mWindow, this);


}


//Adjust mouse clipping area
void MagixFrameListener::windowResized(RenderWindow* rw)
{
    unsigned int width, height, depth;
    int left, top;
    rw->getMetrics(width, height, depth, left, top);

    mInputListener->adjustMouseClipping(width, height);
}


//Unattach OIS before window shutdown (very important under Linux)
void MagixFrameListener::windowClosed(RenderWindow* rw)
{
    //Only close for window that created OIS (the main window in these demos)
    if(rw == mWindow)
    {
        delete mInputListener;
        mInputListener = nullptr;
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
    if(mWindow->isClosed())
    {
        return false;
    }

    if(mMagixHandler->getDebugText() != "")
    {
        mDebugOverlay->setDebugText(mMagixHandler->getDebugText());
    }

    mInputListener->capture();

    bool contFlag = mMagixHandler->update(evt);

    if(mWindow->getViewport(0)->getBackgroundColour() != mSceneMgr->getFogColour())
    {
        mWindow->getViewport(0)->setBackgroundColour(mSceneMgr->getFogColour());
    }

    return contFlag;
}


bool MagixFrameListener::frameEnded(const FrameEvent& evt)
{
    mDebugOverlay->updateStats();
    return true;
}

