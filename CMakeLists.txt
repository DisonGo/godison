cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# add_definitions(-DGODISON_QT_MODULE)
set(LIB_NAME godison)
AUX_SOURCE_DIRECTORY(./src GODISON_SRCS)
file(GLOB_RECURSE GODISON_HEADERS
    includes/*.h
)
add_library(${LIB_NAME} STATIC
${GODISON_SRCS}
${GODISON_HEADERS}
)
get_directory_property(MYDEFS COMPILE_DEFINITIONS)
target_include_directories(${LIB_NAME} PUBLIC includes)

add_executable(godison_main main.cc)
target_link_libraries(godison_main PRIVATE ${LIB_NAME})
if(MYDEFS MATCHES "GODISON_QT_MODULE")
    find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Gui)
    find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Gui)
    target_link_libraries(${LIB_NAME} PUBLIC Qt${QT_VERSION_MAJOR}::Gui)
    target_link_libraries(godison_main PUBLIC Qt${QT_VERSION_MAJOR}::Gui)
endif()