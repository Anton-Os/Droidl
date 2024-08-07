cmake_minimum_required(VERSION 3.18.1)
project(Droidl)

set(Topl_Src_Path "/home/antonos/Documents/Codex/Topl" CACHE PATH "Topl source directory" FORCE)
set(Topl_Install_Path "/home/antonos/Documents/Codex/Topl/BUILD_UNIX/INSTALL" CACHE PATH "Topl install directory" FORCE)
set(Topl_DIR "/home/antonos/Documents/Codex/Topl/BUILD_UNIX/INSTALL/lib/Topl")

find_package(Topl REQUIRED PATHS "${Topl_Install_Path}/lib/Topl" NO_DEFAULT_PATH)
if(Topl_FOUND)
    message(STATUS "Topl loading success")
    # set(Topl_Found_Status TRUE CACHE BOOL FORCE)
else()
    message(STATUS "Topl loading failure")
    # set(Topl_Found_Status FALSE CACHE BOOL FORCE) # Uncomment for error
endif()

# set(Topl_Source_Path "C:/AntonDocs/Codex/Ao-Project/Topl/master" CACHE PATH "Topl source directory" FORCE)
# include(build_parent.cmake)

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
    Java_com_google_androidgamesdk_GameActivity_initializeNativeCode"
)

add_library(droidl SHARED main.cpp)

target_include_directories(droidl
    PRIVATE
    ${ANDROID_NDK}/sources/android/native_app_glue
)

if(Topl_Found)
    file(GLOB_RECURSE parentHeaders
        ${Topl_Src_Path}/core/*.hpp
        ${Topl_Src_Path}/support/*.hpp
        ${Topl_Src_Path}/geometry/*.hpp
        ${Topl_Src_Path}/shaders/*.hpp
    )

    message(STATUS "Parent headers are ${parentHeaders}")

    target_include_directories(droidl
        PUBLIC
        ${Topl_Src_Path}/core
        ${Topl_Src_Path}/geometry
        ${Topl_Src_Path}/support
        ${Topl_Src_Path}/shaders
    )
endif()

# add lib dependencies
target_link_libraries(droidl
    android
    # native_app_glue
    game-activity::game-activity_static
    vulkan
    EGL
    GLESv1_CM
    log
)

if(Topl_Found)
    target_link_libraries(droidl
        CORELIB
        GEOLIB
    )

    # target_link_libraries(droidl GL4_ENGINE)
    # target_link_libraries(droidl Vulkan_ENGINE)
endif()


