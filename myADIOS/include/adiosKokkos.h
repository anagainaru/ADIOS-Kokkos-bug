#ifndef ADIOS2_HELPER_ADIOSKOKKOS_H_
#define ADIOS2_HELPER_ADIOSKOKKOS_H_

namespace adios2
{
namespace helper
{
#ifdef _WIN32
#define ADIOS2_EXPORT __declspec(dllexport)
#else
#define ADIOS2_EXPORT __attribute__((visibility("default")))
#endif

ADIOS2_EXPORT void GPUMinMax(size_t size);

} // helper
} // adios2

#endif /* ADIOS2_HELPER_ADIOSKOKKOS_H_ */
