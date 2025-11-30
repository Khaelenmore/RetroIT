//
// Created by silverwing on 11/30/25.
//

#include "DebugOverlay.h"

#if defined(DEBUG) || defined(_DEBUG)
#define SHOW_DBG_OVERLAY true
#else
#define SHOW_DBG_OVERLAY false
#endif

DebugOverlay::DebugOverlay(RenderWindow* window): mWindow(window) {
    mDebugOverlay = OverlayManager::getSingleton().getByName("Core/DebugOverlay");
    mIsVisible = SHOW_DBG_OVERLAY;
    if (mIsVisible) {
        show();
    } else {
        hide();
    }
}

void DebugOverlay::toggle() {
    if (mIsVisible) {
        hide();
    } else {
        show();
    }
}

void DebugOverlay::show() {
    mDebugOverlay->show();
    mIsVisible = true;
}

void DebugOverlay::hide() {
    mDebugOverlay->hide();
    mIsVisible = false;
}

bool DebugOverlay::isVisible() {
    return mIsVisible;
}

void DebugOverlay::setDebugText(std::string value) {
    mDebugText = value;
}

void DebugOverlay::updateStats() {
    if (!mIsVisible) {
        return;
    }

    static String currFps = "Current FPS: ";
    static String avgFps = "Average FPS: ";
    static String bestFps = "Best FPS: ";
    static String worstFps = "Worst FPS: ";
    static String tris = "Triangle Count: ";
    static String batches = "Batch Count: ";

    // update stats when necessary
    try
    {
        OverlayElement* guiAvg = OverlayManager::getSingleton().getOverlayElement(
                "Core/AverageFps");
        OverlayElement* guiCurr = OverlayManager::getSingleton().getOverlayElement(
                "Core/CurrFps");
        OverlayElement* guiBest = OverlayManager::getSingleton().getOverlayElement(
                "Core/BestFps");
        OverlayElement* guiWorst = OverlayManager::getSingleton().getOverlayElement(
                "Core/WorstFps");

        const RenderTarget::FrameStats& stats = mWindow->getStatistics();
        guiAvg->setCaption(avgFps + StringConverter::toString(stats.avgFPS));
        guiCurr->setCaption(currFps + StringConverter::toString(stats.lastFPS));
        guiBest->setCaption(bestFps + StringConverter::toString(stats.bestFPS)
                            + " " + StringConverter::toString(stats.bestFrameTime) + " ms");
        guiWorst->setCaption(worstFps + StringConverter::toString(stats.worstFPS)
                             + " " + StringConverter::toString(stats.worstFrameTime) + " ms");

        OverlayElement* guiTris = OverlayManager::getSingleton().getOverlayElement(
                "Core/NumTris");
        guiTris->setCaption(tris + StringConverter::toString(stats.triangleCount));

        OverlayElement* guiBatches = OverlayManager::getSingleton().getOverlayElement(
                "Core/NumBatches");
        guiBatches->setCaption(batches + StringConverter::toString(
                stats.batchCount));

        OverlayElement* guiDbg = OverlayManager::getSingleton().getOverlayElement(
                "Core/DebugText");
        guiDbg->setCaption(mDebugText);
    }
    catch(...)
    {
        //ignore exceptions
    }
}