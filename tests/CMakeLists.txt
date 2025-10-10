cmake_minimum_required(VERSION 3.22)
project(Sofa.Metis_test LANGUAGES CXX)
find_package(Sofa.Testing REQUIRED)

set(SOURCE_FILES
    testMetis.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
sofa_find_package(metis REQUIRED)

if(NOT TARGET metis)
    string(REPLACE "." "_" METIS_VERSION "${Metis_VERSION}")
else ()
    get_target_property(METIS_VERSION metis VERSION )
    string(REPLACE "." "_" METIS_VERSION "${METIS_VERSION}")
endif ()

#TODO NEED TO CHANGE
#set_target_properties(${PROJECT_NAME} PROPERTIES
#        VERSION 5.2.1
#        FRAMEWORK TRUE
#        PUBLIC_HEADER ${CMAKE_CURRENT_BINARY_DIR}/include/metis.h)
#In all METIS CMakeLists files of all branch


target_compile_definitions( ${PROJECT_NAME} PUBLIC METIS_VERSION_${METIS_VERSION})

target_link_libraries(${PROJECT_NAME} Sofa.Testing Sofa.Metis)
target_link_libraries(${PROJECT_NAME} metis)

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

