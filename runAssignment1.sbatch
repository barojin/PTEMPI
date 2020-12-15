#!/bin/bash

#SBATCH --job-name=CalculatePi
#SBATCH --output=cpi.out
#SBATCH --ntasks=16
#SBATCH --partition=debug

module purge > /dev/null 2>&1

mpirun -np 16 ./cpi




