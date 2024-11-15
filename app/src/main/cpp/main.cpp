#include <jni.h>

#include <iostream>

#include <game-activity/GameActivity.cpp>
#include <game-text-input/gametextinput.cpp>

#include "Platform.hpp"
#include "Droidl_Renderer.hpp"

extern "C" {

Droidl_Renderer* renderer = nullptr; //= new Droidl_Renderer(&context);

void handle_cmd(android_app *app, int32_t cmd) {
    switch (cmd) {
        case APP_CMD_INIT_WINDOW:
            // context.window = app->window;
            // renderer = new Droidl_Renderer(&context);
            break;
        case APP_CMD_TERM_WINDOW: break;
        default: break;
    }
}
bool motion_event_filter_func(const GameActivityMotionEvent *motionEvent) {
    auto sourceClass = motionEvent->source & AINPUT_SOURCE_CLASS_MASK;
    return (sourceClass == AINPUT_SOURCE_CLASS_POINTER ||
            sourceClass == AINPUT_SOURCE_CLASS_JOYSTICK);
}

MAIN_ENTRY {
    // Can be removed, useful to ensure your code is running
    LOGI("Welcome to Android main");

    // android_app_set_motion_event_filter(pApp, motion_event_filter_func);

    Platform platform = Platform(pApp);
    platform.createWindow(0, 0);

    /* int events;
    android_poll_source *pSource;
    do {
        // Process all pending events before running game logic.
        if (ALooper_pollAll(0, nullptr, &events, (void **) &pSource) >= 0) {
            if (pSource) {
                pSource->process(pApp, pSource);
            }
        }

        if(renderer != nullptr) {
            renderer->clear();
            renderer->swapBuffers(0.0);
        }

        if (pApp->userData) LOGI("Handling user data");
        // else LOGI("Handling running data");
    } while (!pApp->destroyRequested); */

    while(platform.handleEvents() && !pApp->destroyRequested){
        if(renderer != nullptr) {
            renderer->clear();
            renderer->swapBuffers(0.0);
        }
    }
}

}