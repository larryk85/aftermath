# ##################################################################################################
# Define the main test executable.
# ##################################################################################################
include(CTest)
enable_testing()
add_executable( unit_tests main.cpp
                           error_type_tests.cpp
                           result_tests.cpp
              )

target_link_libraries( unit_tests bluegrass_error Catch2::Catch2 )
catch_discover_tests( unit_tests )
