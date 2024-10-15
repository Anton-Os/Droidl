#include <jni.h>

#include <iostream>

#include <game-activity/GameActivity.cpp>
#include <game-text-input/gametextinput.cpp>
#include <game-activity/native_app_glue/android_native_app_glue.c>

#include "Platform.hpp"
#include "Droidl_Renderer.hpp"

extern "C" {

void handle_cmd(android_app *app, int32_t cmd) {
    switch (cmd) {
        case APP_CMD_INIT_WINDOW: break;
        case APP_CMD_TERM_WINDOW: break;
        default: break;
    }
}
bool motion_event_filter_func(const GameActivityMotionEvent *motionEvent) {
    auto sourceClass = motionEvent->source & AINPUT_SOURCE_CLASS_MASK;
    return (sourceClass == AINPUT_SOURCE_CLASS_POINTER ||
            sourceClass == AINPUT_SOURCE_CLASS_JOYSTICK);
}

void android_main(struct android_app *pApp) {
    // Can be removed, useful to ensure your code is running
    LOGI("welcome to Android main");

    pApp->onAppCmd = handle_cmd;

    android_app_set_motion_event_filter(pApp, motion_event_filter_func);

    // TODO: Platform should be created here
    NATIVE_PLATFORM_CONTEXT context;
    context.window = pApp->window;
    context.eglCtx = eglGetCurrentContext();
    Droidl_Renderer* renderer = new Droidl_Renderer(&context);

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

        renderer->clear();

        if (pApp->userData) LOGI("Handling user data");
        // else LOGI("Handling running data");
    } while (!pApp->destroyRequested);
}
}