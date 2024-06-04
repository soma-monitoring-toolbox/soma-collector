# soma-collector
soma-collector is the component exposing the core SOMA measurement API

Built by starting with the Mochi Thallium Template and adding on.
https://github.com/mochi-hpc/thallium-microservice-template

## Installation Instructions

Install spack outside project directory from https://spack-tutorial.readthedocs.io/en/latest/tutorial_basics.html 

Once spack is installed and added to your path, load modules and add them to spack, for example:
```
module load gcc openmpi cmake
spack compiler find
spack external find
```

Clone soma-collector:
```
git clone --recurse-submodules https://github.com/soma-monitoring-toolbox/soma-collector.git
cd soma-collector
```

Install spack packages:
* Rename the spack.yaml.* file that resembles your system to spack.yaml and update any externals so that spack doesn't try to install things that are already on the system. Then run the following commands:
```
spack env activate .
spack install
```

Compile SOMA: 
```
mkdir build && cd build
export SOMA_INSTALL_DIR=<path/to/SOMA>/install
cmake -DENABLE_EXAMPLES=ON -DCMAKE_INSTALL_PREFIX=$SOMA_INSTALL_DIR ..
make install -j
```

