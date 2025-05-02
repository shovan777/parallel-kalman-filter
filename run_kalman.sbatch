#!/bin/bash
#SBATCH --job-name=kalman_build_run
#SBATCH --output=output_%j.txt
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=4
#SBATCH --time=00:01:00
#SBATCH --partition=smp
#SBATCH --account=ece2166_2025s



# Load modules (uncomment if your environment needs these)
module purge
module load gcc/
module load cmake

# Move to your project directory
cd /ihome/ece2166_2025s/gas291/PCA_2025/parallel-kalman-filter

rm -rf build
mkdir build
cd build
cmake .. -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++
make

# Run the binary (assuming already built)



# Run the binary
./parallelkalman

