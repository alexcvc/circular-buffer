find_package(Threads REQUIRED)

# add options and dependencies
file(GLOB SOURCE_FILES *.cpp)

foreach (SOURCE_PATH ${SOURCE_FILES})

  get_filename_component(TARGET_NAME ${SOURCE_PATH} NAME_WE)
  add_executable(${TARGET_NAME} ${SOURCE_PATH})

  ## link with library
  target_link_libraries(${TARGET_NAME} Threads::Threads)
  target_include_directories(${TARGET_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../include" )

  add_test(NAME ${TARGET_NAME} COMMAND ${TARGET_NAME})

endforeach (SOURCE_PATH ${SOURCE_FILES})