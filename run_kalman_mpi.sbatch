#!/bin/bash
#SBATCH --job-name=kalman_mpi_shs
#SBATCH --nodes=2
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=48
#SBATCH --cluster=mpi
#SBATCH --partition=mpi
#SBATCH --time=00:10:00
#SBATCH --output=kalman_mpi_shs.out
#SBATCH --account=ece2166_2025s




# Load modules (uncomment if your environment needs these)
module purge
module load gcc/5.4.0
module load openmpi/3.0.0
module load cmake

echo "SLURM_NTASKS = " $SLURM_NTASKS

# Give Details of CPU Running Program
echo -n "Running on:  "
cat /proc/cpuinfo | grep "model name" | head -n 1 | cut -c 13-

# # Move to your project directory
# cd /ihome/ece2166_2025s/gas291/PCA_2025/parallel-kalman-filter

rm -rf build
mkdir build
cd build
# make with MPI
cmake .. -DCMAKE_C_COMPILER=mpicc -DCMAKE_CXX_COMPILER=g++
make

echo -n "Number of MPI tasks = "
echo $SLURM_NTASKS
echo -n "Number of OpenMP threads = "
echo $SLURM_CPUS_PER_TASK

mpirun -n $SLURM_NTASKS ./parallelkalman --mca opal_warn_on_missing_libcuda 0 --mca btl_openib_allow_ib 1


# Run the binary
# ./parallelkalman

