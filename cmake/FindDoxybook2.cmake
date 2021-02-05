find_program(DOXYBOOK2_EXECUTABLE
        NAMES doxybook2
        DOC "Path to doxybook2 executable")

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(doxybook2
        "Failed to find doxybook2 executable"
        DOXYBOOK2_EXECUTABLE)