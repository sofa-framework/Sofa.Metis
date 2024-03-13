cmake_minimum_required(VERSION 3.22)
project(Sofa.Metis_test LANGUAGES CXX)
find_package(Sofa.Testing REQUIRED)

set(SOURCE_FILES
    testMetis.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} Sofa.Testing Sofa.Metis)
target_link_libraries(${PROJECT_NAME} metis)

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

