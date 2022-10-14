cmake_minimum_required(VERSION 3.10.2)

### INCLUDE YOUR PATH HERE ###
# set(Topl_Install_Path "C:/AntonDocs/Codex/Ao-Project/Topl/MSVC_BUILD_2/INSTALL/" CACHE PATH "Topl install directory" FORCE)

# find_package(Topl PATHS ${Topl_Install_Path}/lib/Topl)
if(Topl_FOUND)
    message(STATUS "Topl loading success")
    # set(Topl_Found_Status TRUE CACHE BOOL FORCE)
else()
    message(STATUS "Topl loading failure")
    # set(Topl_Found_Status FALSE CACHE BOOL FORCE) # Uncomment for error
endif()

### INCLUDE YOUR PATH HERE ###
set(Topl_Source_Path "C:/AntonDocs/Codex/Ao-Project/Topl/master" CACHE PATH "Topl source directory" FORCE)
include(build_from_src.cmake)

# Droidl Build Script

# build native_app_glue as a static lib
set(${CMAKE_C_FLAGS}, "${CMAKE_C_FLAGS}")
add_library(native_app_glue STATIC
    ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c)

# now build app's shared lib
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -Wall -Werror")

# Export ANativeActivity_onCreate(),
# Refer to: https://github.com/android-ndk/ndk/issues/381.
set(CMAKE_SHARED_LINKER_FLAGS
    "${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate")

add_library(droidl-activity SHARED main.cpp)

target_include_directories(droidl-activity PRIVATE
    ${ANDROID_NDK}/sources/android/native_app_glue)

# add lib dependencies
target_link_libraries(droidl-activity
    android
    native_app_glue
    EGL
    GLESv1_CM
    log

    # CORELIB
    # GEOLIB
)
