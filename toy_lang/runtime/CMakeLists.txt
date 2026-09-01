add_library(toy_runtime STATIC toy_heap.c toy_ordered.c toy_runtime.c)
set_target_properties(toy_runtime PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
  POSITION_INDEPENDENT_CODE ON
)