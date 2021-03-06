# P4aig

# create the parser library
add_library(libparser
        p4parser/p4parser.cpp
        p4parser/handlers.cpp)

target_include_directories(libparser
    PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${RAPIDJSON_INCLUDES}
    )

target_compile_options(libparser PRIVATE -Wall -Werror)
target_compile_features(libparser PRIVATE cxx_std_11)

# create the circuits library
add_library(libcircuits
    circuits/circuits.cpp)

target_include_directories(libcircuits
    PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${RAPIDJSON_INCLUDES}
    )

target_compile_options(libcircuits PRIVATE -Wall -Werror)
target_compile_features(libcircuits PRIVATE cxx_std_11)

# create the main library
add_library(libp4aig
    p4aig/p4aig.cpp)

target_include_directories(libp4aig
    PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${RAPIDJSON_INCLUDES}
    )

target_compile_options(libp4aig PRIVATE -Wall -Werror)
target_compile_features(libp4aig PRIVATE cxx_std_11)

target_link_libraries(libp4aig PUBLIC libparser)
