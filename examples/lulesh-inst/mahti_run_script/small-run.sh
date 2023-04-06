#!/bin/bash
#SBATCH --job-name=soma-lulesh
#SBATCH --account=project_2006549
#SBATCH --partition=medium
#SBATCH --time=00:20:00
#SBATCH --nodes=2
#SBATCH --cpus-per-task=1
#SBATCH --output=slurm-lulesh-%j.out
#SBATCH --error=slurm-lulesh-%j.err

set -eu

#echo "Setting up spack and modules"
#source /users/sriamesh/spack/share/spack/setup-env.sh
#cd /users/sriamesh/SOMA/soma-collector
#spack env activate . 
#spack load mochi-bedrock
#spack load conduit
#cd build/examples
#cd /users/sriamesh/SOMA/soma-collector/examples/lulesh-inst/mahti_run_script

module load gcc/9.4.0 openmpi/4.1.2-cuda cmake

echo "Starting SOMA Collectors..."
export SOMA_SERVER_ADDR_FILE=`pwd`/server.add
export SOMA_NODE_ADDR_FILE=`pwd`/node.add
export SOMA_NUM_SERVER_INSTANCES=1
export SOMA_NUM_SERVERS_PER_INSTANCE=1
export SOMA_SERVER_INSTANCE_ID=0

#Make sure number of SOMA servers is SOMA_NUM_SERVER_INSTANCES * SOMA_NUM_SERVERS_PER_INSTANCE
srun -n 1 -N 1 /users/dewiy/soma-collector/build/examples/example-server -a ofi+verbs:// &

sleep 10

#export LD_LIBRARY_PATH=`pkg-config --libs-only-L soma-client soma-server soma-admin | sed -e "s/ -L/:/g" | sed -e "s/-L//g" | sed -e "s/ //g"`:`spack location -i conduit`/lib:$LD_LIBRARY_PATH

echo "Starting LULESH"

srun -n 8 -N 1 /users/dewiy/soma-collector/build/examples/lulesh-inst/lulesh2.0 -i 500 -p
