#ifndef ADIOS2_HELPER_ADIOSKokkos_CPP_
#define ADIOS2_HELPER_ADIOSKokkos_CPP_

#include "adiosKokkos.h"

#include <Kokkos_Core.hpp>

void adios2::helper::GPUMinMax(size_t size)
{
    Kokkos::DefaultExecutionSpace exe_space;
    std::cout << "Create View inside ADIOS on memory space: " << exe_space.name() << std::endl;
	using mem_space = Kokkos::DefaultExecutionSpace::memory_space;
	Kokkos::View<float *, mem_space> gpuSimData("simBuffer", size);
	Kokkos::parallel_for("initializeBuffer", size, KOKKOS_LAMBDA(int i){
			gpuSimData(i) = i;
		});
}

#endif /* ADIOS2_HELPER_ADIOSKokkos_CPP_ */
