# Shared library using Kokkos

**myADIOS** is a shared library that simulates in a minimal version of the ADIOS2 library that links to Kokkos.
It contains two source files: 
- `adiosKokkos.cpp` that implements the Kokkos code that just creates a View and populates it.
- `myADIOS.cpp` is a simple interface that forwards the code to the Kokkos functions

Linking Kokkos mimics ADIOS2 in the following way (`adiosKokkos` is the only files that links Kokkos, the rest are compiled as CXX files):

```cmake
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
```


**The application** `kokkosHelloWorld.cpp` links to myADIOS and Kokkos.
It simply creates a View and calls the myADIOS function that executes the Kokkos code.

```cmake
target_link_libraries(KokkosHello PRIVATE Kokkos::kokkos ${ADIOS_LIB})
```

**Buid**

There is a script in the root of this repo that can be used to build the myADIOS library and the application.

```bash
# for the library
cmake -DKokkos_ROOT=${Kokkos_ROOT} -DCMAKE_CXX_COMPILER=g++ -DCMAKE_C_COMPILER=gcc -DCMAKE_INSTALL_PREFIX=${myADIOS_HOME}/install ..

# for the application
cmake -DKokkos_ROOT=${Kokkos_ROOT} -D CMAKE_CXX_STANDARD=17 -D CMAKE_CXX_EXTENSIONS=OFF -DCMAKE_CXX_COMPILER=${Kokkos_HOME}/bin/nvcc_wrapper -DCMAKE_PREFIX_PATH=${myADIOS_HOME}/install ..
export CPLUS_INCLUDE_PATH=/ccs/home/againaru/adios/code_example_shared_lib/myADIOS/install/include
```

**Running the code**

When build with Kokkos 3.7 (https://github.com/kokkos/kokkos/releases/tag/3.7.00)
```
$ ./build/KokkosHello
Create View on memory space: Cuda
Create View inside ADIOS on memory space: Cuda
```

With the latest develop the code seg faults.
```
[againaru@login5.summit code_example_shared_lib]$ ./build/KokkosHello
Create View on memory space: Cuda
Create View inside ADIOS on memory space: Cuda
Segmentation fault (core dumped)
```

If these two lines:
```
    set_property(SOURCE src/adiosKokkos.cpp PROPERTY LANGUAGE CUDA)
    set_property(SOURCE src/adiosKokkos.cpp APPEND PROPERTY COMPILE_FLAGS "--extended-lambda")
```
are removed from the `myADIOS/CMakeLists.txt` the code runs correctly.
