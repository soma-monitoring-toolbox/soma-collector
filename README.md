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

Compile soma-collector: 
```
mkdir build && cd build
export SOMA_INSTALL_DIR=<path/to/SOMA>/install
cmake -DENABLE_EXAMPLES=ON -DCMAKE_INSTALL_PREFIX=$SOMA_INSTALL_DIR ..
make install -j
```

## Install TAU with SOMA plugins enabled
Load the same modules:
```
module load gcc openmpi
```

Clone the TAU repository:
```
git clone https://github.com/dyokelson/tau2.git
```

Set up Spack and load dependencies:
```
. </path/to/spack/>share/spack/setup-env.sh
spack env activate <path/to/>soma-collector
spack load mochi-thallium cereal mochi-margo mercury argobots json-c uuid conduit
```

Export paths for TAU:
```
export PKG_CONFIG_PATH=</path/to/>soma-collector/install/lib/pkgconfig:$PKG_CONFIG_PATH
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH=</path/to/>soma-collector/install/lib
```

Find the Conduit install:
* In your spack directory /opt/spack/<arch>/<compiler> you should find a conduit install and can copy that absolute path

Configure TAU:
```
cd tau2
Best MAHTI: ./configure -mpi -bfd=download -mochi -useropt=#-g#-O2#-I</path/to/>soma-collector/install/include#-I</path/to/conduit/>include#-std=c++17
```

Build TAU:
```
export PATH=</path/to/>tau2/<arch>/bin:$PATH
make -j install
```

