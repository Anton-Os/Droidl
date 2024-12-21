#include <jni.h>

#include <iostream>

#include <game-activity/GameActivity.cpp>
#include <game-text-input/gametextinput.cpp>

#include "Platform.hpp"
#include "Droidl_Renderer.hpp"

#include "Idle_Shader.hpp"

extern "C" {

Idle_VertexShader_GL4 vertexShader;
Idle_PixelShader_GL4 pixelShader;
GL4::Pipeline pipeline;

MAIN_ENTRY {
    // Can be removed, useful to ensure your code is running
    LOGI("Welcome to Android main");

    Platform platform = Platform(pApp);
    Droidl_Renderer* renderer = nullptr;

    while(platform.handleEvents() && !pApp->destroyRequested){
        if(platform.getParentWindow() == nullptr) { // await window to be created
            platform.awaitWindow();
            if(platform.getParentWindow() != nullptr){
                renderer = new Droidl_Renderer(platform.getContext());
                // renderer->genPipeline(&pipeline, &vertexShader, &pixelShader);
            }
        } else if(renderer != nullptr) {
            renderer->clear();
            renderer->swapBuffers(0.0);
        }
    }

    delete(renderer);
}

}