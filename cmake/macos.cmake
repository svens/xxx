#
# MacOS options
#

find_library(core_foundation_lib CoreFoundation)
list(APPEND ${PROJECT_NAME}_DEP_LIBS ${core_foundation_lib})
