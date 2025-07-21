cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    project(juce_ffmpeg 
            VERSION 0.1.0 
            LANGUAGES CXX OBJC C
            DESCRIPTION "A ffmpeg wrapper module for JUCE"
            HOMEPAGE_URL "https://github.com/Cle3000/FFmpegVideoComponent-for-JUCE")
else()
    project(juce_ffmpeg 
            VERSION 0.1.0 
            LANGUAGES CXX C
            DESCRIPTION "A ffmpeg wrapper module for JUCE"
            HOMEPAGE_URL "https://github.com/Cle3000/FFmpegVideoComponent-for-JUCE")
endif()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

if (NOT ffmpeg_FOUND)
    find_package(ffmpeg REQUIRED)
endif()

if(PROJECT_IS_TOP_LEVEL)
    message(STATUS "No parent project found, requiring JUCE")
    find_package(JUCE REQUIRED)
    
    juce_add_gui_app(FFmpegVideoComponent)

    target_sources(FFmpegVideoComponent PRIVATE
        Source/Main.cpp
        Source/MainComponent.cpp
        Source/PlayerComponent.cpp
        Source/TransportComponent.cpp
        juce_ffmpeg.cpp
    )

    target_include_directories(FFmpegVideoComponent PRIVATE ./ JuceLibraryCode)

    target_compile_definitions(FFmpegVideoComponent PRIVATE JUCE_MODAL_LOOPS_PERMITTED=1)

    target_link_libraries(FFmpegVideoComponent PRIVATE 
        ffmpeg::ffmpeg

        # System frameworks for FFmpeg/VideoToolbox
        "-framework VideoToolbox"
        "-framework CoreMedia"
        "-framework CoreVideo"
        "-framework CoreFoundation"
        "-framework Security"
        "iconv"

        # JUCE modules
        juce::juce_core
        juce::juce_events
        juce::juce_graphics
        juce::juce_data_structures
        juce::juce_gui_basics
        juce::juce_gui_extra
        juce::juce_audio_basics
        juce::juce_audio_devices
        juce::juce_audio_formats
        juce::juce_audio_processors
        juce::juce_audio_utils
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
    )

    if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
        if(CMAKE_OSX_ARCHITECTURES MATCHES "arm64")
            add_custom_command(TARGET FFmpegVideoComponent POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E echo "Running post-build script for arm64"
                COMMAND /bin/sh ${CMAKE_SOURCE_DIR}/Scripts/post_build_osx_arm.sh ${CMAKE_BINARY_DIR}/FFmpegVideoComponent_artefacts
                WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/FFmpegVideoComponent_artefacts
            )
        else()
            add_custom_command(TARGET FFmpegVideoComponent POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E echo "Running post-build script for x86_64"
                COMMAND /bin/sh ${CMAKE_SOURCE_DIR}/Scripts/post_build_osx_x86_64.sh ${CMAKE_BINARY_DIR}/FFmpegVideoComponent_artefacts
                WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/FFmpegVideoComponent_artefacts
            )
        endif()
    endif()
endif()

# The rest of this file is for packaging the module, which we can ignore for now
# while we get the application to build.
return()
juce_add_module("${CMAKE_CURRENT_LIST_DIR}")

target_compile_definitions(juce_ffmpeg INTERFACE 
                JUCE_MODAL_LOOPS_PERMITTED=1 
                JUCE_STRICT_REFCOUNTEDPOINTER=1 
                JUCE_PLUGINHOST_AU=1 
                JUCE_PLUGINHOST_VST3=1 
                JUCE_PLUGINHOST_LADSPA=1)

target_link_libraries(juce_ffmpeg INTERFACE ffmpeg::ffmpeg)

set(JF_INSTALL_DEST "${CMAKE_INSTALL_LIBDIR}/cmake/juce_ffmpeg"
        CACHE STRING
        "Directory below INSTALL_PREFIX where the juce_ffmpeg CMake package files will be installed to")

install(DIRECTORY "${CMAKE_CURRENT_LIST_DIR}"
         DESTINATION "${JF_INSTALL_DEST}/.."
         COMPONENT juce_ffmpeg
         PATTERN *.md EXCLUDE
         PATTERN .git/* EXCLUDE
         PATTERN .github/* EXCLUDE
         PATTERN *.json EXCLUDE
         PATTERN CMakeLists.txt EXCLUDE 
         PATTERN "${CMAKE_CURRENT_BINARY_DIR}/" EXCLUDE)

include(CPackComponent)

cpack_add_component(juce_ffmpeg
            GROUP juce_ffmpeg 
            INSTALL_TYPES Developer)

include(CMakePackageConfigHelpers)

write_basic_package_version_file(juce_ffmpeg-config-version.cmake 
                                  VERSION "${PROJECT_VERSION}"
                                  COMPATIBILITY SameMajorVersion
                                  ARCH_INDEPENDENT)

configure_package_config_file(cmake/config.cmake juce_ffmpeg-config.cmake
                               INSTALL_DESTINATION "${JF_INSTALL_DEST}" 
                               NO_SET_AND_CHECK_MACRO)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/juce_ffmpeg-config-version.cmake"
               "${CMAKE_CURRENT_BINARY_DIR}/juce_ffmpeg-config.cmake" 
        DESTINATION "${JF_INSTALL_DEST}"
        COMPONENT juce_ffmpeg)

export(PACKAGE juce_ffmpeg)
