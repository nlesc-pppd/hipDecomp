find_package(hipfort REQUIRED COMPONENTS hipfft)

add_executable(poisson)
target_sources(poisson
  PRIVATE
  poisson.f90
)

target_include_directories(poisson
  PRIVATE
  ${CMAKE_BINARY_DIR}/include
  ${MPI_Fortran_INCLUDE_DIRS}
)
target_link_libraries(poisson PRIVATE MPI::MPI_Fortran)
target_link_libraries(poisson PRIVATE hipfort::hip)
target_link_libraries(poisson PRIVATE hipfort::hipfft)
target_link_libraries(poisson PRIVATE hipdecomp)
target_link_libraries(poisson PRIVATE hipdecomp_fort)
target_compile_options(poisson PRIVATE $<$<COMPILE_LANGUAGE:Fortran>:${FORTRAN_COMPILE_OPTIONS}>)
if(HIPDECOMP_USE_CUDECOMP_NAMES)
  target_compile_definitions(poisson PRIVATE USE_CUDECOMP_NAMES)
endif()

install(
  TARGETS poisson
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/examples/fortran/poisson
)
