#[[

CMake package configuration file for juce_ffmpeg

This file is loaded by the find_package command to load an installed copy of juce_ffmpeg
and bring it into another CMake build tree.

]]

@PACKAGE_INIT@

check_required_components ("@PROJECT_NAME@")

include (FeatureSummary)
include (FindPackageMessage)

set_package_properties("${CMAKE_FIND_PACKAGE_NAME}" 
                    PROPERTIES 
                    URL "https://github.com/Cle3000/FFmpegVideoComponent-for-JUCE"
                    DESCRIPTION "A ffmpeg wrapper module for JUCE")

list (APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

include (CMakeFindDependencyMacro)

if(PROJECT_IS_TOP_LEVEL)
    message(STATUS "No parent project found, requiring JUCE")
    find_dependency(JUCE)
endif()
find_dependency(ffmpeg)

juce_add_module("${CMAKE_CURRENT_LIST_DIR}"
                 ALIAS_NAMESPACE juce_ffmpeg)

target_compile_definitions(juce_ffmpeg INTERFACE 
                                JUCE_MODAL_LOOPS_PERMITTED=1 
                                JUCE_STRICT_REFCOUNTEDPOINTER=1 
                                JUCE_PLUGINHOST_AU=1 
                                JUCE_PLUGINHOST_VST3=1 
                                JUCE_PLUGINHOST_LADSPA=1)

target_link_libraries(juce_ffmpeg INTERFACE ffmpeg::ffmpeg)

find_package_message("${CMAKE_FIND_PACKAGE_NAME}" 
                      "juce_ffmpeg - local install"
                      "juce_ffmpeg [${CMAKE_CURRENT_LIST_DIR}]")

