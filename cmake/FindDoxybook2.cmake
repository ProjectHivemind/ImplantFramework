find_program(DOXYBOOK2_EXECUTABLE
        NAMES Doxybook2
        DOC "Path to doxybook2 executable")

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(Doxybook2
        "Failed to find doxybook2 executable"
        DOXYBOOK2_EXECUTABLE)