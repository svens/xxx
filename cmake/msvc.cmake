# https://docs.microsoft.com/en-us/cpp/preprocessor/compiler-warnings-that-are-off-by-default
set(max_warning_flags /W4 /WX /w34265 /w34777 /w34946 /w35038)

# TODO: https://gitlab.kitware.com/cmake/cmake/issues/18317
string(REGEX REPLACE "/W3" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
