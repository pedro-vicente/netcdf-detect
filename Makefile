dir_inc = /usr/include
dir_lib = /usr/lib/
INC = -I$(dir_inc)
LIB = -L$(dir_lib) -lhdf5 -lhdf5_hl -lnetcdf -lz
OBJS = detect_netcdf.o  
CXX = g++
CXX_FLAG = -g

all: detect_netcdf

detect_netcdf: $(OBJS)
	$(CXX) $(OBJS) $(LIB) -o detect_netcdf

detect_netcdf.o : detect_netcdf.cpp 
	$(CXX) $(INC) -c $(CXX_FLAG) detect_netcdf.cpp

clean:
	-rm *.o  detect_netcdf
