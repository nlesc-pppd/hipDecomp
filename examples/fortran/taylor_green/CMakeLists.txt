find_package(hipfort REQUIRED COMPONENTS hipfft)

add_executable(tg_fortran)
target_sources(tg_fortran
  PRIVATE
  tg.f90
)
set_target_properties(tg_fortran
                      PROPERTIES OUTPUT_NAME tg)
target_include_directories(tg_fortran
  PRIVATE
  ${CMAKE_BINARY_DIR}/include
  ${MPI_Fortran_INCLUDE_DIRS}
)
target_link_libraries(tg_fortran PRIVATE MPI::MPI_Fortran)
target_link_libraries(tg_fortran PRIVATE hipfort::hip)
target_link_libraries(tg_fortran PRIVATE hipfort::hipfft)
target_link_libraries(tg_fortran PRIVATE hipdecomp)
target_link_libraries(tg_fortran PRIVATE hipdecomp_fort)
target_compile_options(tg_fortran PRIVATE $<$<COMPILE_LANGUAGE:Fortran>:${FORTRAN_COMPILE_OPTIONS}>)
if(CRAY_ENV)
  target_compile_options(tg_fortran PRIVATE $<$<COMPILE_LANGUAGE:Fortran>:-hacc>)
  target_link_options(tg_fortran PRIVATE $<$<COMPILE_LANGUAGE:Fortran>:-hacc>)
else()
  message(WARNING "OpenACC is not enabled, Fortran tg_fortran example will not give correct results")
endif()

install(
  TARGETS tg_fortran
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/examples/fortran/taylor_green
)
