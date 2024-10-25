file(GLOB_RECURSE support_src ${Topl_Src_Path}/support/*.cpp)
file(GLOB core_src
        ${Topl_Src_Path}/core/*.cpp
        ${Topl_Src_Path}/core/program/*.cpp
        ${Topl_Src_Path}/core/renderer/*.cpp
)

add_library(Droidl_CORELIB ${support_src} ${core_src}) # Core Library
target_include_directories(Droidl_CORELIB PUBLIC ${CMAKE_BINARY_DIR} ${ANDROID_NDK}/sources/android/native_app_glue)
target_include_directories(Droidl_CORELIB PRIVATE ${Topl_Src_Path}/core ${Topl_Src_Path}/support ${Topl_Src_Path}/geometry ${Topl_Src_Path}/shaders "${CMAKE_INSTALL_PREFIX}/include")
set_target_properties(Droidl_CORELIB PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED ON CXX_EXTENSIONS ON)
# target_include_directories(CORELIB
#    INTERFACE
#    $<BUILD_INTERFACE:${interfaceHeaders}>
#    $<INSTALL_INTERFACE:include/Topl>
# )

add_library(Droidl_GL4_ENGINE
        ${Topl_Src_Path}/core/renderer/opengl/Topl_Pipeline_GL4.cpp
        ${Topl_Src_Path}/core/renderer/opengl/Topl_Renderer_GL4.cpp
)
target_include_directories(Droidl_GL4_ENGINE PRIVATE ${Topl_Src_Path}/core ${Topl_Src_Path}/support ${Topl_Src_Path}/geometry)
# target_include_directories(GL4_ENGINE INTERFACE
#        $<BUILD_INTERFACE:${interfaceHeaders}>
#        $<INSTALL_INTERFACE:include/Topl>
# )

file(GLOB_RECURSE geometry_src ${Topl_Src_Path}/geometry/*.cpp)
if(NOT SUPPORT_MODELS)
    list(REMOVE_ITEM geometry_src ${Topl_Src_Path}/geometry/meshes/Geo_Node.cpp)
endif()

add_library(Droidl_GEOLIB ${geometry_src}) # Geometry Library
target_include_directories(Droidl_GEOLIB PRIVATE ${Topl_Src_Path}/core ${Topl_Src_Path}/support ${Topl_Src_Path}/geometry)

target_link_libraries(droidl
        Droidl_CORELIB # CORELIB
        Droidl_GEOLIB # GEOLIB
        Droidl_GL4_ENGINE # GL4_ENGINE
)