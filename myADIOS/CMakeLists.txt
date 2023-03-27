cmake_minimum_required(VERSION 3.12)
project (myADIOS C CXX CUDA)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Kokkos 3.7 REQUIRED)

set(CMAKE_CUDA_STANDARD 11)
set(CMAKE_CUDA_STANDARD_REQUIRED TRUE)
if(NOT DEFINED CMAKE_CUDA_ARCHITECTURES)
	if(DEFINED Kokkos_CUDA_ARCHITECTURES)
		set(CMAKE_CUDA_ARCHITECTURES ${Kokkos_CUDA_ARCHITECTURES})
	else()
		# Mininum common non-deprecated architecture
		set(CMAKE_CUDA_ARCHITECTURES 52)
	endif()
endif()

include(GNUInstallDirs)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_library(myADIOS SHARED src/myADIOS.cpp) #src/adiosKokkos.cpp)
configure_file(myADIOS.pc.in myADIOS.pc @ONLY)

#target_link_libraries(myADIOS PRIVATE Kokkos::kokkos)

add_library(myADIOS_kokkos include/adiosKokkos.h src/adiosKokkos.cpp)

set_target_properties(myADIOS_kokkos PROPERTIES
    VISIBILITY_INLINES_HIDDEN ON
)

kokkos_compilation(SOURCE src/adiosKokkos.cpp)
if(Kokkos_ENABLE_CUDA)
	message(STATUS "[debug] ENABLE CUDA ON")
    set_property(SOURCE src/adiosKokkos.cpp PROPERTY LANGUAGE CUDA)
    set_property(SOURCE src/adiosKokkos.cpp APPEND PROPERTY COMPILE_FLAGS "--extended-lambda")
    set_target_properties(myADIOS_kokkos PROPERTIES
      CUDA_VISIBILITY_PRESET hidden
    )
    target_compile_features(myADIOS_kokkos PRIVATE cuda_std_17)
endif()

target_link_libraries(myADIOS_kokkos PRIVATE Kokkos::kokkos)
target_link_libraries(myADIOS PRIVATE myADIOS_kokkos)

install(FILES include/myADIOS.h include/adiosKokkos.h DESTINATION include)

install(TARGETS myADIOS myADIOS_kokkos
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(FILES ${CMAKE_BINARY_DIR}/myADIOS.pc
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)
