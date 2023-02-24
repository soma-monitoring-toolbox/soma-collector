#!/bin/bash
#SBATCH --job-name=soma-lulesh
#SBATCH --account=project_2006549
#SBATCH --partition=medium
#SBATCH --time=01:00:00
#SBATCH --nodes=1
#SBATCH --cpus-per-task=1

set -eu

echo "Setting up spack and modules"
source ./sourceme.sh

#ulimit -c unlimited

#Unfortunately, Spack does not change my env anymore while loading modules, so this sort of stupid ****in hack is required
#export LD_LIBRARY_PATH=`pkg-config --libs-only-L sdskv-client sdskv-server symbiomon-client symbiomon-server reducer-client | sed -e "s/ -L/:/g" | sed -e "s/-L//g" | sed -e "s/ //g"`:$LD_LIBRARY_PATH

echo "Starting LULESH + SOMA"
#export TAU_PLUGINS=libTAU-mochi-symbiomon-local-aggr-plugin.so
#export PATH=/users/sriamesh/SYMBIOMON/tau2/x86_64/bin:$PATH #Change this line
#export TAU_PLUGINS_PATH=/users/sriamesh/SYMBIOMON/tau2/x86_64/lib/shared-mpi #Change this line
#export TAU_SYMBIOMON_REDUCTION_FREQUENCY=15
#export TAU_NUM_SOMA_RANKS=2
#export AGGREGATOR_ADDRESS_FILE=`pwd`/sdskv.add
cp ../lulesh2.0 .

#NUM_RANKS=10 #Change this, depending on TAU_NUM_SOMA_RANKS (8+2 = 10)
#srun -n $NUM_RANKS -N 1 tau_exec -T mpi ./lulesh2.0 -i 500 -p
srun -n 1 -N 1 ./lulesh2.0 -i 50 -p
