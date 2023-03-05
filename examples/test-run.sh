#!/bin/bash
#SBATCH --job-name=soma-conduit
#SBATCH --account=project_2006549
#SBATCH --partition=medium
#SBATCH --time=02:00:00
#SBATCH --nodes=2
##SBATCH --cpus-per-task=1
#SBATCH --output=slurm-lulesh-%j.out
#SBATCH --error=slurm-lulesh-%j.err

set -eu

echo "Setting up spack and modules"
source /projappl/project_2006549/spack/share/spack/setup-env.sh
cd /users/dewiy/soma-collector
spack env activate . 
spack load mochi-bedrock
spack load conduit
cd build/examples
cd /users/dewiy/soma-collector/examples

echo "Starting SOMA Servers..."
export SOMA_SERVER_ADDR_FILE=`pwd`/server.add
export SOMA_NODE_ADDR_FILE=`pwd`/node.add
export SOMA_NUM_SERVER_INSTANCES=1
export SOMA_NUM_SERVERS_PER_INSTANCE=2

#Make sure number of SOMA servers is SOMA_NUM_SERVER_INSTANCES * SOMA_NUM_SERVERS_PER_INSTANCE
srun -n 2 -N 1 /users/dewiy/soma-collector/build/examples/example-server -a ofi+verbs:// &

sleep 10

export LD_LIBRARY_PATH=`pkg-config --libs-only-L soma-client soma-server soma-admin | sed -e "s/ -L/:/g" | sed -e "s/-L//g" | sed -e "s/ //g"`:`spack location -i conduit`/lib:$LD_LIBRARY_PATH

echo "Starting SOMA Client"
export SOMA_SERVER_INSTANCE_ID=0

srun -n 2 -N 1 /users/dewiy/soma-collector/build/examples/example-client -p -a ofi+verbs://10.141.1.250:42927
