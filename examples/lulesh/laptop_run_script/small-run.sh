#!/bin/bash
set -eu

echo "Setting up spack and modules"
spack load mochi-symbiomon@develop+aggregator+reducer

echo "Starting Aggregator.."
mpirun -np 2 sdskv-aggr-service na+sm:// foo:map -f sdskv.add &

spack unload --all
spack load mochi-reducer@develop+symbiomon+aggregator
export AGGREGATOR_ADDRESS_FILE=`pwd`/sdskv.add
sleep 5

echo "Starting Reducer.."
mpirun -np 1 server na+sm:// &
sleep 5

spack unload --all
spack load mochi-symbiomon@develop+aggregator+reducer
echo "Starting LULESH"
export TAU_PLUGINS=libTAU-mochi-symbiomon-plugin.so
export PATH=/home/sramesh/MOCHI/TAU_INSTALL/craycnl/bin:$PATH #Change this line
export TAU_PLUGINS_PATH=/home/sramesh/MOCHI/TAU_INSTALL/craycnl/lib/shared-gnu-mpi/ #Change this line
export TAU_SYMBIOMON_REDUCTION_FREQUENCY=15
export AGGREGATOR_ADDRESS_FILE=`pwd`/sdskv.add
export REDUCER_ADDRESS_FILE=`pwd`/reducer.add
cp ../lulesh2.0 .

mpirun -np 8 tau_exec -T mpi ./lulesh2.0 -i 500 -p

