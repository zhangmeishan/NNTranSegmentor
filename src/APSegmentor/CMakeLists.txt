
include_directories(
  model
)

add_executable(APSegmentor APSegmentor.cpp)
target_link_libraries(APSegmentor ${LIBS})

