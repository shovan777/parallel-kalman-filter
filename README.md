# parallel-kalman-filter
Aims to develop a parallel implementation of kalman filter algorithm.


## install 
- install g++
```
sudo apt install g++
sudo dnf install gcc-c++
```
- install cmake
- install ninja-build
- build with cmake
```
mkdir  build
cd build
cmake -G Ninja ..
ninja
```
or do this
```
CC=/ihome/crc/install/gcc/12.2.0/bin/gcc CXX=/ihome/crc/install/gcc/12.2.0/bin/g++ cmake CC=gcc -G Ninja ..
``
- run the program
```
./build/parallelkalman
```