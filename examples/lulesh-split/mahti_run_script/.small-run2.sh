#!/bin/bash
#SBATCH --job-name=soma-symbiomon
#SBATCH --account=project_2006549
#SBATCH --partition=medium
#SBATCH --time=02:00:00
#SBATCH --nodes=2
#SBATCH --cpus-per-task=1
#SBATCH --output=slurm-lulesh-%j.out
#SBATCH --error=slurm-lulesh-%j.err

set -eu

echo "Setting up spack and modules"
cd /users/sriamesh/SOMA/soma-collector
spack env activate . 
spack load mochi-bedrock
spack load conduit
cd build/examples
cd /users/sriamesh/SOMA/soma-collector/examples/lulesh/mahti_run_script

echo "Starting SOMA Collectors..."
export SOMA_SERVER_ADDR_FILE=`pwd`/server.add
export SOMA_NODE_ADDR_FILE=`pwd`/node.add
export SOMA_NUM_SERVER_INSTANCES=1
export SOMA_NUM_SERVERS_PER_INSTANCE=2

#Make sure number of SOMA servers is SOMA_NUM_SERVER_INSTANCES * SOMA_NUM_SERVERS_PER_INSTANCE
srun -n 2 -N 1 /users/sriamesh/SOMA/soma-collector/build/examples/example-server -a ofi+verbs:// &

sleep 10

export LD_LIBRARY_PATH=`pkg-config --libs-only-L soma-client soma-server soma-admin | sed -e "s/ -L/:/g" | sed -e "s/-L//g" | sed -e "s/ //g"`:`spack location -i conduit`/lib:$LD_LIBRARY_PATH

echo "Starting LULESH"
export TAU_PLUGINS=libTAU-mochi-soma-remote-collector-plugin.so
export PATH=/users/sriamesh/SYMBIOMON/tau2/x86_64/bin:$PATH #Change this line
export TAU_PLUGINS_PATH=/users/sriamesh/SYMBIOMON/tau2/x86_64/lib/shared-mpi #Change this line
export TAU_SOMA_MONITORING_FREQUENCY=10
export SOMA_SERVER_INSTANCE_ID=0

cp ../lulesh2.0 .

srun -n 8 -N 1 tau_exec -T mpi ./lulesh2.0 -i 500 -p
