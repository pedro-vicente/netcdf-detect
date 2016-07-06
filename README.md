# netcdf-detect
Utility function that detects if an HDF5 file was saved by the netCDF API

Rationale
------------
The netCDF API does not distinguish between a HDF5 file saved by the HDF5 API
or by the netCDF API. This tool provides a means to do that, by using
the HDF5 API to traverse a file and look for metadata.

The netCDF API writes, if variables and dimensions are present in the file:
1) an attribute named "_Netcdf4Dimid" (in some cases)
2) an attribute named "NAME", (always), saved by the HDF5 Dimension Scales API,
that contains the string "This is a netCDF dimension but not a netCDF variable."

This utility tries to detect both attributes, if either case is found it returns a value of 1.
For clarity, return error values are ignored

Dependencies
------------

[netCDF](http://www.unidata.ucar.edu/software/netcdf)
netCDF is a set of software libraries and self-describing, 
machine-independent data formats that support the creation, 
access, and sharing of array-oriented scientific data.
<br /> 

Building from source
------------

Install dependency packages: Debian-based systems (like Ubuntu)
<pre>
sudo apt-get install build-essential
sudo apt-get install libnetcdf-dev netcdf-bin netcdf-doc
</pre>

Install dependency packages: For RPM-based systems (like Fedora and CentOS)
<pre>
yum install zlib-devel
yum install netcdf netcdf-devel
</pre>

Get source:
<pre>
git clone https://github.com/pedro-vicente/netcdf-detect.git
</pre>

Build with:
<pre>
make
</pre>

