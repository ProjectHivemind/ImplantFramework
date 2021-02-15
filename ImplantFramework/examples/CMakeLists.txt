include_directories(${PROJECT_SOURCE_DIR}/ImplantFramework/include)
add_executable(Hivemind windows/main.cpp)
target_link_libraries(Hivemind Hivemind_lib)