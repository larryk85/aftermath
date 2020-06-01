# ##################################################################################################
# Define the benchmarks.
# ##################################################################################################
add_executable( simple_benchmark_errors simple.cpp )
add_executable( simple_benchmark_exceptions simple.cpp )

target_compile_definitions( simple_benchmark_exceptions PRIVATE -DUSE_EXCEPTIONS )

target_link_libraries( simple_benchmark_errors bluegrass_error )
target_link_libraries( simple_benchmark_exceptions bluegrass_error )
