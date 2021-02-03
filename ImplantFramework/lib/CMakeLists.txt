include_directories(${PROJECT_SOURCE_DIR}/ImplantFramework/include ${PROJECT_SOURCE_DIR}/ImplantFramework/lib/include)

file(GLOB_RECURSE source_list "*.cpp" "*.hpp")

add_library(Hivemind_lib ${source_list})