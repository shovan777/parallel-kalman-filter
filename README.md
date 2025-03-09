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
cmake -G Ninja -B build
ninja -C build
```
- run the program
```
./build/parallelkalman
```