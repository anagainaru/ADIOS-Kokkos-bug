#include <iostream>
#include <vector>
#include <numeric>

#include <Kokkos_Core.hpp>
#include <myADIOS.h>

int main(int argc, char **argv)
{
    Kokkos::initialize(argc, argv);
    {
		Kokkos::DefaultExecutionSpace exe_space;
    	std::cout << "Create View on memory space: " << exe_space.name() << std::endl;
		size_t size = 100;
		using mem_space = Kokkos::DefaultExecutionSpace::memory_space;
		Kokkos::View<float *, mem_space> gpuSimData("simBuffer", size);
		Kokkos::parallel_for("initializeBuffer", size, KOKKOS_LAMBDA(int i){
				gpuSimData(i) = i;
			});

		adios2::ADIOS adios_var;
		adios_var.gpuMinMax(size);
	}

    Kokkos::finalize();
    return 0;
}
