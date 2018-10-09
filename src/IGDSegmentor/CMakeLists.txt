
include_directories(
  model
)

add_executable(IGDSegmentor IGDSegmentor.cpp)
target_link_libraries(GDSegmentor ${LIBS})
