#include <jni.h>

#include <iostream>

#include <game-activity/GameActivity.cpp>
#include <game-text-input/gametextinput.cpp>

#include <game-activity/native_app_glue/android_native_app_glue.c>

#include "Platform.hpp"
#include "Droidl_Renderer.hpp"

extern "C" {

NATIVE_PLATFORM_CONTEXT context;
Droidl_Renderer* renderer = nullptr; //= new Droidl_Renderer(&context);

void handle_cmd(android_app *app, int32_t cmd) {
    switch (cmd) {
        case APP_CMD_INIT_WINDOW:
            context.window = app->window;
            renderer = new Droidl_Renderer(&context);
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
    LOGI("welcome to Android main");

    pApp->onAppCmd = handle_cmd;

    android_app_set_motion_event_filter(pApp, motion_event_filter_func);

    // This sets up a typical game/event loop. It  will run until the app is destroyed.
    int events;
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
    } while (!pApp->destroyRequested);
}
}