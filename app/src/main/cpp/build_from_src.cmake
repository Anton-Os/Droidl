

if(EXISTS ${Topl_Source_Path}/CmakeLists.txt)
    message("Building Topl...")

    # Core Library
    list(APPEND helper_src
        ${Topl_Source_Path}/helper/IO.cpp
        ${Topl_Source_Path}/helper/Controls.cpp
        ${Topl_Source_Path}/helper/Timer.cpp
        ${Topl_Source_Path}/helper/Platform.cpp
        ${Topl_Source_Path}/helper/ValueGen.cpp
    )

    list(APPEND core_src
        # core/Topl_App.cpp
        # core/Topl_Factory.cpp
        ${Topl_Source_Path}/core/Topl_Renderer.cpp

        ${Topl_Source_Path}/core/Topl_Scene_Statics.cpp
        ${Topl_Source_Path}/core/Topl_Scene_Dynamics.cpp
    )

    add_library(CORELIB
        ${helper_src}
        ${core_src}
    )

    target_include_directories(CORELIB PUBLIC core helper geometry)
    set_target_properties(CORELIB PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED ON CXX_EXTENSIONS ON)

    # Geometry Library

    file(GLOB_RECURSE geometry_src ${Topl_Source_Path}/geometry/*.cpp)

    add_library(GEOLIB ${geometry_src})
    target_include_directories(GEOLIB PUBLIC core helper geometry)
else()
    message("Please route Topl_Source_Path to root of Topl project")
    message("Checkout latest version at https://github.com/Anton-Os/Topl")
endif()