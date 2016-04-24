# netcdf-detect
Utility function that detects if an HDF5 file was saved by the netCDF API

Dependencies
------------

[netCDF](http://www.unidata.ucar.edu/software/netcdf)
netCDF is a set of software libraries and self-describing, 
machine-independent data formats that support the creation, 
access, and sharing of array-oriented scientific data.
<br /> 

Building from source
------------

Install dependency packages (Ubuntu):
<pre>
sudo apt-get install build-essential
sudo apt-get install libnetcdf-dev netcdf-bin netcdf-doc
</pre>

Get source:
<pre>
git clone https://github.com/pedro-vicente/netcdf-detect.git
</pre>

Build with:
<pre>
make
</pre>

