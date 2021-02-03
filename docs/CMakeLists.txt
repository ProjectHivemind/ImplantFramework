find_package(Doxygen REQUIRED)

# Find all the public headers
get_target_property(IMPLANTFRAMEWORK_PUBLIC_HEADER_DIR Hivemind_lib INTERFACE_INCLUDE_DIRECTORIES)
file(GLOB_RECURSE IMPLANTFRAMEWORK_PUBLIC_HEADERS ${IMPLANTFRAMEWORK_PUBLIC_HEADER_DIR}/*.h)

set(DOXYGEN_INPUT_DIR ${PROJECT_SOURCE_DIR}/ImplantFramework)
set(DOXYGEN_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/docs/doxygen)
set(DOXYGEN_INDEX_FILE ${DOXYGEN_OUTPUT_DIR}/xml/index.xml)
set(DOXYFILE_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
set(DOXYFILE_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
set(DOXYGEN_MCSS_BINARY ${PROJECT_SOURCE_DIR}/docs/m.css/documentation/doxygen.py)
set(DOXYGEN_MCSS_FILE ${PROJECT_SOURCE_DIR}/docs/Doxyfile-mcss)

#Replace variables inside @@ with the current values
configure_file(${DOXYFILE_IN} ${DOXYFILE_OUT} @ONLY)

file(MAKE_DIRECTORY ${DOXYGEN_OUTPUT_DIR}) #Doxygen won't create this for us

add_custom_command(OUTPUT ${DOXYGEN_INDEX_FILE}
                   DEPENDS ${IMPLANTFRAMEWORK_PUBLIC_HEADERS}
                   COMMAND ${CMAKE_COMMAND} -E copy ${DOXYGEN_MCSS_FILE} Doxyfile-mcss
                   COMMAND ${DOXYGEN_MCSS_BINARY} Doxyfile-mcss
                   MAIN_DEPENDENCY ${DOXYFILE_OUT} ${DOXYFILE_IN}
                   COMMENT "Generating docs"
                   VERBATIM)

add_custom_target(Doxygen ALL DEPENDS ${DOXYGEN_INDEX_FILE})