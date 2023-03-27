#ifndef ADIOS2_CORE_ADIOS_H_
#define ADIOS2_CORE_ADIOS_H_

namespace adios2
{

class ADIOS
{
	public:
		ADIOS();
  		~ADIOS();

		void gpuMinMax(size_t size);
};

}


#endif /* ADIOS2_ADIOS_H_ */
