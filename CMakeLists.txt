cmake_minimum_required(VERSION 3.22)
project(Sofa.Metis LANGUAGES CXX)

set(SOFAMETIS_SOURCE_DIR "src/sofa/metis")

set(HEADER_FILES
    ${SOFAMETIS_SOURCE_DIR}/config.h.in
    ${SOFAMETIS_SOURCE_DIR}/init.h
)

set(SOURCE_FILES
    ${SOFAMETIS_SOURCE_DIR}/init.cpp
)

find_package(Sofa.Core REQUIRED)

add_library(${PROJECT_NAME} SHARED ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} PUBLIC Sofa.Core)

sofa_create_package_with_targets(
    PACKAGE_NAME ${PROJECT_NAME}
    PACKAGE_VERSION ${Sofa_VERSION}
    TARGETS ${PROJECT_NAME} AUTO_SET_TARGET_PROPERTIES
    INCLUDE_SOURCE_DIR "src"
    INCLUDE_INSTALL_DIR ${PROJECT_NAME}
    EXAMPLE_INSTALL_DIR "examples"
    RELOCATABLE "plugins"
)
