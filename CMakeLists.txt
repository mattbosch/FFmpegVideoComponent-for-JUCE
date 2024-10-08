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
    # TODO: add the demo project in Source/ dir
endif()

juce_add_module("${CMAKE_CURRENT_LIST_DIR}" ALIAS_NAMESPACE juce_ffmpeg)

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
