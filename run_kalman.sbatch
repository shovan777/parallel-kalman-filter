#!/bin/bash
#SBATCH --job-name=kalman_build_run
#SBATCH --output=output_%j.txt
#SBATCH --error=error_%j.txt
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=8
#SBATCH --time=00:10:00
#SBATCH --partition=short
#SBATCH --mem=2G

# Load modules (uncomment if your environment needs these)
module purge
module load gcc
module load cmake

# Move to your project directory
cd /home/ece2166_2025/gas291/PCA_2025/parallel-kalman-filter

# Clean and rebuild
rm -rf build
mkdir build
cd build

# Configure and build the project with Make
cmake .. -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++
make

# Run the binary
./parallelkalman

