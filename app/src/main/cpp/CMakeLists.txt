cmake_minimum_required(VERSION 3.18.1)
project(Droidl)

# set(Topl_Source_Path "C:/AntonDocs/Codex/Ao-Project/Topl/master" CACHE PATH "Topl source directory" FORCE)
# include(build_targets.cmake)

# Droidl Build Script

# build native_app_glue as a static lib
set(${CMAKE_C_FLAGS}, "${CMAKE_C_FLAGS}")
add_library(native_app_glue STATIC
    ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c
)

# now build app's shared lib
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -Wall -Werror")

# Export ANativeActivity_onCreate(),
# Refer to: https://github.com/android-ndk/ndk/issues/381.
# set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate")

find_package(game-activity REQUIRED CONFIG)
set(CMAKE_SHARED_LINKER_FLAGS
    "${CMAKE_SHARED_LINKER_FLAGS} -u \
    JavDroidl_com_google_androidgamesdk_GameActivity_initializeNativeCode"
)

add_library(Droidl SHARED
        Droidl_Renderer.cpp
        # Droidl_Pipeline.cpp
        main.cpp
)

target_include_directories(Droidl
    PRIVATE
    ${ANDROID_NDK}/sources/android/native_app_glue
)

if (${ANDROID_PLATFORM_LEVEL} LESS 18)
set(OPENGL_LIB GLESv2)
else ()
set(OPENGL_LIB GLESv3)
endif()

# add lib dependencies
target_link_libraries(Droidl
    android
    # native_app_glue
    game-activity::game-activity_static
    vulkan
    EGL
    GLESv3 # ${OPENGL_LIB}
    # GLESv1_CM
    log
)

set(Topl_Src_Path "/home/antonos/Documents/Codex/Topl_New" CACHE PATH "Topl source directory" FORCE)
set(Topl_Install_Path "/home/antonos/Documents/Codex/Topl_New/BUILD_UNIX/INSTALL" CACHE PATH "Topl install directory" FORCE)
set(Topl_DIR "/home/antonos/Documents/Codex/Topl_New/BUILD_UNIX/INSTALL/lib/Topl")
if(SUPPORT_TEXTURES)
    set(Rasteron_Install_Path "/home/antonos/Documents/Codex/Rasteron_New/BUILD_UNIX/INSTALL/include/Rasteron")
    target_include_directories(Droidl
        PUBLIC
        ${Rasteron_Install_Path}
    )
endif()

# find_package(Topl REQUIRED PATHS "${Topl_Install_Path}/lib/Topl" NO_DEFAULT_PATH)
if(TRUE) # Topl_FOUND)
    message(STATUS "Topl loading success")
    # set(Topl_Found_Status TRUE CACHE BOOL FORCE)

    target_include_directories(Droidl
        PUBLIC
        ${Topl_Src_Path}/core
        ${Topl_Src_Path}/geometry
        ${Topl_Src_Path}/support
        ${Topl_Src_Path}/shaders
    )

    include(build_targets.cmake)
else()
    message(SEND_ERROR "Topl loading failure")
    # set(Topl_Found_Status FALSE CACHE BOOL FORCE)
endif()

