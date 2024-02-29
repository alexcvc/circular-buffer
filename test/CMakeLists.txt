enable_testing()

# Set project name
set(TargetName test_circular_buffer)

set(LIBS pthread rt )

# Pre-defines standard install locations on *nix systems.
include(GNUInstallDirs)

add_executable( ${TargetName} )
target_sources(${TargetName} PRIVATE "test_main.cpp" "test_cases.cpp" )
target_link_libraries(${TargetName} PUBLIC ${LIBS} )
target_compile_features(${TargetName} PRIVATE cxx_std_20)

install(TARGETS ${TargetName} DESTINATION bin)