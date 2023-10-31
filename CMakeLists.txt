idf_component_register(
    SRCS 
        src/mux_hc4067.cpp
    INCLUDE_DIRS 
        "include/"
    REQUIRES 
        driver
        log
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++20 -Wno-format -Wno-missing-field-initializers -Wno-write-strings")