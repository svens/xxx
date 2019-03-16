list(APPEND xxx_api_sources
  xxx/__bits/build.hpp
  xxx/error.hpp
)

list(APPEND xxx_impl_sources
  xxx/__bits/platform_sdk.hpp
  xxx/error.cpp
)

list(APPEND xxx_unittests_sources
  xxx/common.test.hpp
  xxx/common.test.cpp
  xxx/error.test.cpp
)
