
include_directories(
  model
)

add_executable(CombinedSegmentor CombinedSegmentor.cpp)
target_link_libraries(CombinedSegmentor ${LIBS})

