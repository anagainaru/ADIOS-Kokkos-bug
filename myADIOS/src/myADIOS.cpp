#include <iostream>

#include "myADIOS.h"
#include "adiosKokkos.h"

namespace adios2
{
	ADIOS::ADIOS() {};
	ADIOS::~ADIOS() {};

	void ADIOS::gpuMinMax(size_t size)
	{
		helper::GPUMinMax(size);
	}
}
