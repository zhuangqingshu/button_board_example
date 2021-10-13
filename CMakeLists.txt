# The following lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.5)

include($ENV{SMART_SCHOOL_PATH}/component.cmake)
include($ENV{MDF_PATH}/project.cmake)

#if(CONFIG_SWITCH_CHANNEL_4)
#	project(switch_4)
#elseif(CONFIG_SWITCH_CHANNEL_3)
#	project(switch_3)
#elseif(CONFIG_SWITCH_CHANNEL_2)
#	project(switch_2)
#elseif(CONFIG_SWITCH_CHANNEL_1)
#	project(switch_1)
#endif()

project(switch)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
