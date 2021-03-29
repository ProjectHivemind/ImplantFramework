include(FetchContent)

FetchContent_Declare(
        json
        GIT_REPOSITORY https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent.git
        GIT_TAG        master
        SOURCE_DIR     "${PROJECT_SOURCE_DIR}/ImplantFramework/lib/external/json"
)

FetchContent_GetProperties(json)
if(NOT json_POPULATED)
    FetchContent_Populate(json)
    add_subdirectory(./external/json)
endif()


if (MSVC)
    set(BOOSTROOT C:\\boost_1_75_0\\boost_1_75_0)
endif (MSVC)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

FIND_PACKAGE(Boost REQUIRED COMPONENTS thread system chrono timer)

MACRO(GENERATE_HEADER_FILE prefix)
    file(WRITE ${CMAKE_BINARY_DIR}/all_headers.hpp "//Generated headers include\n")
    file(APPEND ${CMAKE_BINARY_DIR}/all_headers.hpp "#ifndef ALL_HEADERS_H_\n#define ALL_HEADERS_H_\n")

    FILE(GLOB_RECURSE children ${prefix}_*.hpp)
    FOREACH(child ${children})
        get_filename_component(temp ${child} NAME)
        file(APPEND ${CMAKE_BINARY_DIR}/all_headers.hpp "#include \"${temp}\"\n")
    ENDFOREACH()
    file(APPEND ${CMAKE_BINARY_DIR}/all_headers.hpp "#endif \n")
ENDMACRO()

file(GLOB_RECURSE source_list "*.cpp" "*.hpp")
set(all_headers "")
if (MSVC)
    file(GLOB_RECURSE linux_list "linux*.cpp" "linux*.hpp")
    list(REMOVE_ITEM source_list ${linux_list})
    GENERATE_HEADER_FILE("windows")
elseif (UNIX)
    file(GLOB_RECURSE windows_list "windows*.cpp" "windows*.hpp")
    list(REMOVE_ITEM source_list ${windows_list})
    GENERATE_HEADER_FILE("linux")
endif ()

include_directories(${PROJECT_SOURCE_DIR}/ImplantFramework/include
        ${PROJECT_SOURCE_DIR}/ImplantFramework/lib/include
        ${PROJECT_SOURCE_DIR}/ImplantFramework/lib/source/modules
        ${PROJECT_SOURCE_DIR}/ImplantFramework/lib/source/transports
        ${PROJECT_SOURCE_DIR}/ImplantFramework/lib/platform
        ${PROJECT_SOURCE_DIR}/ImplantFramework/lib/external/json/include/nlohmann
        ${Boost_INCLUDE_DIR}
        ${CMAKE_BINARY_DIR})

add_library(Hivemind_lib ${source_list})

if (MSVC)
    target_link_libraries(Hivemind_lib nlohmann_json::nlohmann_json ${Boost_LIBRARIES} ws2_32 mswsock advapi32 iphlpapi)
endif (MSVC)

if (UNIX)
    target_link_libraries(Hivemind_lib nlohmann_json::nlohmann_json ${Boost_LIBRARIES} rt)
endif (UNIX)
