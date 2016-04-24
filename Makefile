# List of .o files that EXENAME depends on

OBJS = detect_netcdf.o  

# Macros defining the C/C++ compiler and linker.

CC = g++
CCOPTS = -g
LINK = g++
INCLUDES = -I/usr/include 
LIBS = -L/usr/lib/ -lhdf5 -lhdf5_hl -lnetcdf -lz

# Rules for building EXENAME from OBJS and OBJS from source.

all: detect_netcdf

detect_netcdf: $(OBJS)
	$(LINK) $(OBJS) $(LIBS) -o detect_netcdf

detect_netcdf.o : detect_netcdf.cpp 
	$(CC) $(INCLUDES) -c $(CCOPTS) detect_netcdf.cpp

clean:
	-rm *.o  detect_netcdf
