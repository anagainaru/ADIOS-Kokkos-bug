cmake_minimum_required(VERSION 3.12)
project(adiosKokkos CXX CUDA)

find_library(ADIOS_LIB libmyADIOS.so)
message(STATUS ${ADIOS_LIB})

find_package(Kokkos REQUIRED)

add_executable(KokkosHello kokkosHelloWorld.cpp)
target_link_libraries(KokkosHello PRIVATE Kokkos::kokkos ${ADIOS_LIB})
