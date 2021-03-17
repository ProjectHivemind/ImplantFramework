add_subdirectory(./external/json)

if (MSVC)
    set(BOOSTROOT C:\\boost_1_75_0\\boost_1_75_0)
endif (MSVC)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

FIND_PACKAGE(Boost REQUIRED COMPONENTS thread system chrono timer)

include_directories(${PROJECT_SOURCE_DIR}/ImplantFramework/include
        ${PROJECT_SOURCE_DIR}/ImplantFramework/lib/include
        ${PROJECT_SOURCE_DIR}/ImplantFramework/lib/platform
        ${PROJECT_SOURCE_DIR}/ImplantFramework/lib/external/json/include/nlohmann
        ${Boost_INCLUDE_DIR})

file(GLOB_RECURSE source_list "*.cpp" "*.hpp")
if (MSVC)
    file(GLOB_RECURSE linux_list "linux*.cpp" "linux*.hpp")
    list(REMOVE_ITEM source_list ${linux_list})
elseif (UNIX)
    file(GLOB_RECURSE linux_list "windows*.cpp" "windows*.hpp")
    list(REMOVE_ITEM source_list ${linux_list})
endif ()

add_library(Hivemind_lib ${source_list})

if (MSVC)
    target_link_libraries(Hivemind_lib nlohmann_json::nlohmann_json ${Boost_LIBRARIES} ws2_32 mswsock advapi32 iphlpapi)
endif (MSVC)

if (UNIX)
    target_link_libraries(Hivemind_lib nlohmann_json::nlohmann_json ${Boost_LIBRARIES} rt)
endif (UNIX)
