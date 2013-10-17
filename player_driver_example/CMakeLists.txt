CMAKE_MINIMUM_REQUIRED (VERSION 2.4 FATAL_ERROR)
PROJECT (playerplugin_3bot)

# Include this CMake module to get most of the settings needed to build
SET (CMAKE_MODULE_PATH "/usr/share/cmake/Modules")
INCLUDE (UsePlayerPlugin)

PLAYER_ADD_PLUGIN_DRIVER (3botdriver SOURCES 3botdriver.cc)
