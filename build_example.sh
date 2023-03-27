set +x

module load gcc/10.2
module load ninja/1.10
module load cuda/11.5
module load cmake/3.23
module refresh

#Kokkos_HOME=/ccs/home/againaru/kokkos/3.7/kokkos-3.7.00
Kokkos_HOME=/ccs/home/againaru/kokkos/kokkos
Kokkos_ROOT=${Kokkos_HOME}/../install
application_HOME=`pwd`
myADIOS_HOME=${application_HOME}/myADIOS

rm -r ${application_HOME}/build/* ${application_HOME}/myADIOS/build/* ${application_HOME}/myADIOS/install/*

mkdir -p ${application_HOME}/build
mkdir -p ${application_HOME}/myADIOS/build
mkdir -p ${application_HOME}/myADIOS/install

cd ${myADIOS_HOME}/build
cmake -DKokkos_ROOT=${Kokkos_ROOT} -DCMAKE_CXX_COMPILER=g++ -DCMAKE_C_COMPILER=gcc -DCMAKE_INSTALL_PREFIX=${myADIOS_HOME}/install ..
make -j4
make -j4 install

cd ${application_HOME}/build
cmake -DKokkos_ROOT=${Kokkos_ROOT} -D CMAKE_CXX_STANDARD=17 -D CMAKE_CXX_EXTENSIONS=OFF -DCMAKE_CXX_COMPILER=${Kokkos_HOME}/bin/nvcc_wrapper -DCMAKE_PREFIX_PATH=${myADIOS_HOME}/install ..
export CPLUS_INCLUDE_PATH=${myADIOS_HOME}/install/include
make -j4

set -x
