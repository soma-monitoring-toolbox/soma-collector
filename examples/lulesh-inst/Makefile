#default build suggestion of MPI + OPENMP with gcc on Livermore machines you might have to change the compiler name

SHELL = /bin/sh
.SUFFIXES: .cc .o

CC = mpicxx
LULESH_EXEC = lulesh2.0

MPI_INC = /appl/spack/v017/install-tree/gcc-9.4.0/openmpi-4.1.2-cgr4nz/include #Change this
MPI_LIB = /appl/spack/v017/install-tree/gcc-9.4.0/openmpi-4.1.2-cgr4nz/lib #Change this

SERCXX = $(CC) -DUSE_MPI=0 #Change this
MPICXX = $(CC) -DUSE_MPI=1 #Change this
CXX = $(MPICXX)

SOURCES2.0 = \
	lulesh.cc \
	lulesh-comm.cc \
	lulesh-viz.cc \
	lulesh-util.cc \
	lulesh-init.cc
OBJECTS2.0 = $(SOURCES2.0:.cc=.o)

SOMADEPS := $(shell pkg-config --cflags-only-I soma-client soma-server soma-admin nlohmann_json)
SOMALIBDEPS := $(shell pkg-config --libs soma-client soma-server)
CONDUITDEPS := $(shell spack location -i conduit)
UUIDDEPS := $(shell spack location -i uuid)
SOMAINCLUDES = $(SOMADEPS) -I$(CONDUITDEPS)/include
#Default build suggestions with OpenMP for g++
CXXFLAGS = -g -O3 -I. -Wall -D_SOMAPLUGIN $(SOMAINCLUDES)
LDFLAGS = -g -O3  $(SOMALIBDEPS) -L$(CONDUITDEPS)/lib -lconduit -L$(UUIDDEPS)/lib -luuid

#Below are reasonable default flags for a serial build
#CXXFLAGS = -g -O3 -I. -Wall
#LDFLAGS = -g -O3 

#common places you might find silo on the Livermore machines.
#SILO_INCDIR = /opt/local/include
#SILO_LIBDIR = /opt/local/lib
#SILO_INCDIR = ./silo/4.9/1.8.10.1/include
#SILO_LIBDIR = ./silo/4.9/1.8.10.1/lib

#If you do not have silo and visit you can get them at:
#silo:  https://wci.llnl.gov/codes/silo/downloads.html
#visit: https://wci.llnl.gov/codes/visit/download.html

#below is and example of how to make with silo, hdf5 to get vizulization by default all this is turned off.  All paths are Livermore specific.
#CXXFLAGS = -g -DVIZ_MESH -I${SILO_INCDIR} -Wall -Wno-pragmas
#LDFLAGS = -g -L${SILO_LIBDIR} -Wl,-rpath -Wl,${SILO_LIBDIR} -lsiloh5 -lhdf5

.cc.o: lulesh.h
	@echo "Building $<"
	$(CXX) -c $(CXXFLAGS) -o $@  $<

all: $(LULESH_EXEC)

$(LULESH_EXEC): $(OBJECTS2.0)
	@echo "Linking"
	$(CXX) $(OBJECTS2.0) $(LDFLAGS) -lm -o $@

clean:
	/bin/rm -f *.o *~ $(OBJECTS) $(LULESH_EXEC)
	/bin/rm -rf *.dSYM

tar: clean
	cd .. ; tar cvf lulesh-2.0.tar LULESH-2.0 ; mv lulesh-2.0.tar LULESH-2.0

