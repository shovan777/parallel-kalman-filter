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
```
- run the program
```
./build/parallelkalman
```

Python part

```
pip install matplotlib
pip install pandas
pip insatll numpy

python plotting_code.py
```

Commands to run the Python script that runs C++
```
g++ -fPIC -c src/matops.cpp -o src/matops.o -fopenmp
g++ -fPIC -c src/linearMotion.cpp -o src/linearMotion.o -fopenmp
g++ -fPIC -c src/write.cpp -o src/write.o -fopenmp
g++ -fPIC -c src/timer.cpp -o src/timer.o -fopenmp
g++ -fPIC -c main.cpp -o main.o -fopenmp

g++ -shared -o libhello.so main.o src/matops.o src/linearMotion.o src/write.o -fopenmp

python testrun.py
```


