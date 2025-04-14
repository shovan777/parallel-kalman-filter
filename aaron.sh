#!/bin/bash

g++ -fPIC -c src/matops.cpp -o src/matops.o -fopenmp
g++ -fPIC -c src/linearMotion.cpp -o src/linearMotion.o -fopenmp
g++ -fPIC -c src/write.cpp -o src/write.o -fopenmp
g++ -fPIC -c src/timer.cpp -o src/timer.o -fopenmp
g++ -fPIC -c main.cpp -o main.o -fopenmp

g++ -shared -o libhello.so main.o src/matops.o src/linearMotion.o src/write.o -fopenmp

# python testrun.py

srun python testrun.py