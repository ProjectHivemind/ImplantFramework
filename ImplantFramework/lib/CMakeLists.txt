include_directories(${PROJECT_SOURCE_DIR}/ImplantFramework/include ${PROJECT_SOURCE_DIR}/ImplantFramework/lib/include ${PROJECT_SOURCE_DIR}/ImplantFramework/lib/platform)

file(GLOB_RECURSE source_list "*.cpp" "*.hpp")

add_library(Hivemind_lib ${source_list})

if (MSVC)
    target_link_libraries(Hivemind_lib ws2_32 mswsock advapi32)
endif (MSVC)