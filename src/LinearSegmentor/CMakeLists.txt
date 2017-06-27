
include_directories(
  model
)

add_executable(LinearSegmentor LinearSegmentor.cpp)
target_link_libraries(LinearSegmentor ${LIBS})

