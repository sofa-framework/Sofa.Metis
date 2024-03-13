cmake_minimum_required(VERSION 3.22)
project(Sofa.Metis LANGUAGES CXX)

set(SOFAMETIS_SOURCE_DIR "src/sofa/metis")

set(HEADER_FILES
    ${SOFAMETIS_SOURCE_DIR}/config.h.in
    ${SOFAMETIS_SOURCE_DIR}/init.h

    ${SOFAMETIS_SOURCE_DIR}/MetisOrderingMethod.h
)

set(SOURCE_FILES
    ${SOFAMETIS_SOURCE_DIR}/init.cpp

    ${SOFAMETIS_SOURCE_DIR}/MetisOrderingMethod.cpp
)

find_package(Sofa.Core REQUIRED)

find_package(metis 5.1.0 EXACT QUIET)
if(NOT metis_FOUND AND SOFA_ALLOW_FETCH_DEPENDENCIES)
    message("Sofa.Metis: DEPENDENCY metis NOT FOUND. SOFA_ALLOW_FETCH_DEPENDENCIES is ON, fetching metis...")
    include(FetchContent)
    FetchContent_Declare(metis
            GIT_REPOSITORY https://github.com/sofa-framework/METIS
            GIT_TAG v5.1.0-ModernInstall
    )
    FetchContent_MakeAvailable(metis)
elseif (NOT metis_FOUND)
    message(FATAL_ERROR "Sofa.Metis: DEPENDENCY metis NOT FOUND. SOFA_ALLOW_FETCH_DEPENDENCIES is OFF and thus cannot be fetched. Install metis (version=5.1.0), or enable SOFA_ALLOW_FETCH_DEPENDENCIES to fix this issue.")
endif()

add_library(${PROJECT_NAME} SHARED ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} PUBLIC Sofa.Core)
target_link_libraries(${PROJECT_NAME} PRIVATE metis)

sofa_create_package_with_targets(
    PACKAGE_NAME ${PROJECT_NAME}
    PACKAGE_VERSION ${Sofa_VERSION}
    TARGETS ${PROJECT_NAME} AUTO_SET_TARGET_PROPERTIES
    INCLUDE_SOURCE_DIR "src"
    INCLUDE_INSTALL_DIR ${PROJECT_NAME}
    EXAMPLE_INSTALL_DIR "examples"
    RELOCATABLE "plugins"
)
