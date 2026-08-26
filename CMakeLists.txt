cmake_minimum_required(VERSION 3.19)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE RelWithDebInfo)
endif()

# User-defined build options
option(HIPDECOMP_BUILD_FORTRAN "Build Fortran bindings" ON)
option(HIPDECOMP_ENABLE_ROCTX "Enable ROCTx ranges" ON)
option(HIPDECOMP_ENABLE_ROCSHMEM "Enable ROCSHMEM" OFF)
option(HIPDECOMP_BUILD_EXTRAS "Build benchmark, examples, and tests" OFF)
option(HIPDECOMP_ENABLE_COVERAGE "Enable code coverage in HIP and C++ sources" OFF)

# Use AMD Clang compilers by default
find_program(CMAKE_CXX_COMPILER "amdclang++" REQUIRED)

if (HIPDECOMP_BUILD_FORTRAN)
  find_program(HIP_Fortran_BIN "amdflang" REQUIRED)
  set(CMAKE_Fortran_COMPILER ${HIP_Fortran_BIN})
endif()

# Locate and use HIP CMake configuration
find_program(HIPCC "hipcc" REQUIRED)
file(REAL_PATH ${HIPCC} HIPCC)
string(REPLACE "bin/hipcc" "lib/cmake" HIP_CMAKE_DIR ${HIPCC})
set(CMAKE_PREFIX_PATH ${HIP_CMAKE_DIR})

# Limit optimization levels of CPU code compilation
set(CMAKE_CXX_FLAGS_RELEASE "-O1 -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O1 -g -DNDEBUG")
set(CMAKE_Fortran_FLAGS_RELEASE "-O1 -DNDEBUG")
set(CMAKE_Fortran_FLAGS_RELWITHDEBINFO "-O1 -g -DNDEBUG")

if (HIPDECOMP_BUILD_FORTRAN)
  set(LANGS CXX HIP Fortran)
else()
  set(LANGS CXX HIP)
endif()

project(HIPDECOMP LANGUAGES ${LANGS})

# Set up HIP compute targets. Must be done before find_package(HIP). Default: native
set(CMAKE_HIP_ARCHITECTURES ${CMAKE_HIP_ARCHITECUTRES} CACHE STRING "List of HIP compute targets")
set(GPU_TARGETS ${CMAKE_HIP_ARCHITECTURES} CACHE STRING "List of HIP compute targets")

# HIP
find_package(HIP REQUIRED)

# Detect if Cray compiler wrappers are available to assess if in Cray environment.
# We do not use the Cray compiler wrappers directly for greater flexibility.
find_program(CRAY_CC_BIN "CC")

if (CRAY_CC_BIN)
  message(STATUS "Found Cray CC wrapper. Compiling for Cray programming environment.")
endif()

# MPI
find_package(MPI REQUIRED)

if (CRAY_CC_BIN)
  # FindMPI does not include Cray GTL (e.g. GPU-aware MPI) libs
  # automatically in Cray environment. Locate it to include in linking.
  string(REPLACE ":" ";" CRAY_LIB_PATHS $ENV{CRAY_LD_LIBRARY_PATH})
  find_library(CRAY_MPI_GTL_HIP_LIBRARY REQUIRED
    NAMES mpi_gtl_hsa
    HINTS ${CRAY_LIB_PATHS}
  )

  message(STATUS "Found Cray GTL library: " ${CRAY_MPI_GTL_HIP_LIBRARY})
endif()

# Get RCCL library
find_package(rccl REQUIRED)

if (HIPDECOMP_ENABLE_ROCSHMEM)
  # Get ROCSHMEM library
  find_package(rocshmem REQUIRED)
endif()

if (HIPDECOMP_ENABLE_ROCTX)
  # Get rocprofiler-sdk-roctx library
  find_package(rocprofiler-sdk-roctx REQUIRED)
endif()

if(HIPDECOMP_ENABLE_COVERAGE)
  add_compile_options($<$<COMPILE_LANGUAGE:CXX,HIP>:-fprofile-instr-generate$<SEMICOLON>-fcoverage-mapping>)
  add_link_options($<$<LINK_LANGUAGE:CXX,HIP>:-fprofile-instr-generate$<SEMICOLON>-fcoverage-mapping>)
endif()

# Building HIPDECOMP shared lib
add_library(hipdecomp SHARED)
set_target_properties(hipdecomp PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

target_sources(hipdecomp
  PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/src/autotune.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/hipdecomp_kernels.hip
  ${CMAKE_CURRENT_SOURCE_DIR}/src/hipdecomp_kernels_rdc.hip
  ${CMAKE_CURRENT_SOURCE_DIR}/src/hipdecomp.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/graph.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/performance.cc
)

set_source_files_properties(${CMAKE_CURRENT_SOURCE_DIR}/src/hipdecomp_kernels_rdc.hip PROPERTIES COMPILE_FLAGS -fgpu-rdc)

target_include_directories(hipdecomp
  PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${MPI_CXX_INCLUDE_DIRS}
)

target_link_libraries(hipdecomp PUBLIC hip::host hip::device)
target_link_libraries(hipdecomp PUBLIC MPI::MPI_CXX)
target_link_libraries(hipdecomp PRIVATE rccl)
if (HIPDECOMP_ENABLE_ROCTX)
  target_link_libraries(hipdecomp PRIVATE rocprofiler-sdk-roctx)
endif()
if (CRAY_CC_BIN)
  # In Cray environments, add link to GTL lib for GPU-aware MPI support
  target_link_libraries(hipdecomp PRIVATE ${CRAY_MPI_GTL_HIP_LIBRARY})
endif()

# Test for std::filesystem linking
try_compile(
  TEST_STD_FS_RESULT
  ${CMAKE_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake/test_std_fs.cc
)
if (NOT TEST_STD_FS_RESULT)
  message(STATUS "GCC toolchain version does not link std::filesystem symbols by default. Adding explicit -lstdc++fs link.")
  target_link_libraries(HIPDECOMP PRIVATE -lstdc++fs)
endif()

if (HIPDECOMP_ENABLE_ROCTX)
  target_compile_definitions(hipdecomp PRIVATE ENABLE_ROCTX)
endif()

if (HIPDECOMP_ENABLE_ROCSHMEM)
  target_compile_definitions(hipdecomp PRIVATE ENABLE_ROCSHMEM)
  target_link_libraries(hipdecomp PRIVATE roc::rocshmem)
endif()

set_target_properties(hipdecomp PROPERTIES PUBLIC_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/include/hipdecomp.h)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/include/hipdecomp.h ${CMAKE_BINARY_DIR}/include/hipdecomp.h)

install(
  TARGETS hipdecomp
  LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_PREFIX}/include
)

# Building Fortran shared lib and module
if (HIPDECOMP_BUILD_FORTRAN)
  add_library(hipdecomp_fort SHARED)
  set_target_properties(hipdecomp_fort PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
  set_target_properties(hipdecomp_fort PROPERTIES Fortran_MODULE_DIRECTORY ${CMAKE_BINARY_DIR}/include)
  set_target_properties(hipdecomp_fort PROPERTIES LINKER_LANGUAGE Fortran)
  target_compile_options(hipdecomp_fort PRIVATE $<$<COMPILE_LANGUAGE:Fortran>:-cpp>)
  target_sources(
    hipdecomp_fort
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/hipdecomp_m.f90
  )
  set_source_files_properties(${CMAKE_CURRENT_SOURCE_DIR}/src/hipdecomp_m.f90 PROPERTIES LANGUAGE Fortran)

  install(
    TARGETS hipdecomp_fort
    LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
   )
   # Install hipDecomp module
   install(FILES ${CMAKE_BINARY_DIR}/include/hipdecomp.mod DESTINATION ${CMAKE_INSTALL_PREFIX}/include)
endif()

if (HIPDECOMP_BUILD_EXTRAS)
  # add_subdirectory(benchmark)

  add_subdirectory(tests/cc)
  add_subdirectory(examples/cc/basic_usage)
  add_subdirectory(examples/cc/taylor_green)

   if (HIPDECOMP_BUILD_FORTRAN)
     find_package(hipfort REQUIRED COMPONENTS hip)
     add_subdirectory(tests/fortran)
     add_subdirectory(examples/fortran/basic_usage)
     # add_subdirectory(examples/fortran/poisson)
     # add_subdirectory(examples/fortran/taylor_green)
   endif()
endif()
