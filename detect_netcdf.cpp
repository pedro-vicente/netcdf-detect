//Copyright (C) 2016 Pedro Vicente
//Licensed under the Apache License, Version 2.0, described in the attached LICENSE file 
#include <iostream>
#include <string>
#include <string.h>
#include "netcdf.h"
#include "hdf5.h"

//functions part of is_netcdf() utility
int is_netcdf(const char * file_name);
int find_attribute(hid_t loc_id, const char* attr_name);
herr_t iterate_cb(hid_t loc_id, const char *name, void *op_data);
herr_t find_attr_cb(hid_t loc_id, const char *name, const H5A_info_t *ainfo, void *op_data);

//test functions
int save_netcdf_1(const char * file_name);
int save_netcdf_2(const char * file_name);
int save_netcdf_3(const char * file_name);

/////////////////////////////////////////////////////////////////////////////////////////////////////
//main
/////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
  if(save_netcdf_1("test1.nc") != NC_NOERR)
  {

  }

  if(save_netcdf_2("test2.nc") != NC_NOERR)
  {

  }

  if(save_netcdf_3("test3.nc") != NC_NOERR)
  {

  }

  if(is_netcdf("test1.nc"))
  {

  }

  if(is_netcdf("test2.nc"))
  {

  }

  if(is_netcdf("test3.nc"))
  {

  }

  return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//is_netcdf()
//utility function to detect if an HDF5 file was saved by the netCDF API
//the netCDF API writes, if variables and dimensions are present in the file:
//1) an attribute named "_Netcdf4Dimid" (in some cases)
//2) an attribute named "NAME", (always), saved by the HDF5 Dimension Scales API,
//that contains the string "This is a netCDF dimension but not a netCDF variable."
//This utility tries to detect both attributes, if either case is found
//it returns a value of 1
//for clarity, return error values are ignored
/////////////////////////////////////////////////////////////////////////////////////////////////////

int is_netcdf(const char * file_name)
{
  hid_t fid;
  int found = 0;

  std::cout << "file: " << file_name << std::endl;

  if((fid = H5Fopen(file_name, H5F_ACC_RDONLY, H5P_DEFAULT)) < 0)
  {
    return -1;
  }

  if(iterate_cb(fid, "/", &found) < 0)
  {

  }

  if(H5Fclose(fid) < 0)
  {

  }

  if(found)
  {
    std::cout << "file is netcdf" << std::endl;
  }
  else
  {
    std::cout << "file is not netcdf" << std::endl;
  }

  return found;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//recursive callback function to traverse HDF5 file
//callback function with signature of type H5G_iterate_t (typedef for H5Giterate() callbacks)
/////////////////////////////////////////////////////////////////////////////////////////////////////

herr_t iterate_cb(hid_t loc_id, const char *name, void *op_data)
{
  //string to find in netCDF attribute named "NAME"
  const std::string attr_str("This is a netCDF dimension but not a netCDF variable.");
  H5G_stat_t statbuf;
  hid_t did;
  hid_t aid;
  hid_t tid;
  char buf[255];

  if(H5Gget_objinfo(loc_id, name, 0, &statbuf) < 0)
  {

  }

  switch(statbuf.type)
  {

  case H5G_GROUP:

    std::cout << " group: " << name << std::endl;

    if(H5Giterate(loc_id, name, 0, iterate_cb, op_data) < 0)
    {

    }

    break;

  case H5G_DATASET:

    std::cout << " dataset: " << name << std::endl;

    if((did = H5Dopen2(loc_id, name, H5P_DEFAULT))<0)
    {

    }

    if(find_attribute(did, "_Netcdf4Dimid"))
    {
      *(int *)op_data = 1;

      std::cout << "  found attribute '_Netcdf4Dimid'" << std::endl;
    }

    if(find_attribute(did, "NAME"))
    {
      if((aid = H5Aopen(did, "NAME", H5P_DEFAULT)) < 0)
      {

      }

      if((tid = H5Aget_type(aid)) < 0)
      {

      }

      if(H5Aread(aid, tid, buf) < 0)
      {

      }

      if(H5Tclose(tid) < 0)
      {

      }

      if(H5Aclose(aid) < 0)
      {

      }

      std::string str(buf);
      size_t found = str.find(attr_str);
      if(found != std::string::npos)
      {
        *(int *)op_data = 1;

        std::cout << "  found attribute 'NAME' with string: " << str << std::endl;
      }

    }

    if(H5Dclose(did)<0)
    {

    }

    break;
  }

  return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//find_attribute
//utility to find an attribute named 'attr_name' in location ID 'loc_id'
/////////////////////////////////////////////////////////////////////////////////////////////////////

int find_attribute(hid_t loc_id, const char* attr_name)
{
  return H5Aiterate2(loc_id, H5_INDEX_NAME, H5_ITER_INC, NULL, find_attr_cb, (void *)attr_name);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//find_attr_cb
//callback function with signature of type H5A_operator2_t (typedef for H5Aiterate2() callbacks)
/////////////////////////////////////////////////////////////////////////////////////////////////////

herr_t find_attr_cb(hid_t, const char *name, const H5A_info_t *, void *op_data)
{
  int ret = H5_ITER_CONT;

  //Define a positive value for return value if the attribute was found. This will
  //cause the iterator to immediately return that positive value, indicating short-circuit success

  if(strcmp(name, (char *)op_data) == 0)
  {
    ret = H5_ITER_STOP;
  }

  return ret;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//save_netcdf_1
//save a netCDF test file with a variable in a group and 2 dimensions
//this case writes an attribute named "NAME", saved by the HDF5 Dimension Scales API,
//that contains the string "This is a netCDF dimension but not a netCDF variable."
/////////////////////////////////////////////////////////////////////////////////////////////////////

int save_netcdf_1(const char * file_name)
{
  int nc_id;
  int var_id;
  int grp_id;
  int dmn_id[2];
  float buf[6] ={1, 2, 3, 4, 5, 6};

  if(nc_create(file_name, NC_NETCDF4|NC_CLOBBER, &nc_id) != NC_NOERR)
  {
    return NC2_ERR;
  }

  if(nc_def_dim(nc_id, "lat", 2, &dmn_id[0]) != NC_NOERR)
  {

  }

  if(nc_def_dim(nc_id, "lon", 3, &dmn_id[1]) != NC_NOERR)
  {

  }

  if(nc_def_grp(nc_id, "grp", &grp_id) != NC_NOERR)
  {

  }

  if(nc_def_var(grp_id, "var", NC_FLOAT, 2, dmn_id, &var_id) != NC_NOERR)
  {

  }

  if(nc_enddef(nc_id) != NC_NOERR)
  {

  }

  if(nc_put_var_float(grp_id, var_id, buf) != NC_NOERR)
  {

  }

  if(nc_close(nc_id) != NC_NOERR)
  {

  }

  return NC_NOERR;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////
//save_netcdf_2
//save a netCDF test file with a variable and a dimension with the same name
//this case writes an attribute named "_Netcdf4Dimid" 
/////////////////////////////////////////////////////////////////////////////////////////////////////

int save_netcdf_2(const char * file_name)
{
  int nc_id;
  int dmn_id;
  int var_id;

  if(nc_create(file_name, NC_NETCDF4|NC_CLOBBER, &nc_id) != NC_NOERR)
  {
    return NC2_ERR;
  }

  if(nc_def_dim(nc_id, "dim_var", 3, &dmn_id) != NC_NOERR)
  {

  }

  if(nc_def_var(nc_id, "dim_var", NC_FLOAT, 1, &dmn_id, &var_id) != NC_NOERR)
  {

  }

  if(nc_enddef(nc_id) != NC_NOERR)
  {

  }

  if(nc_close(nc_id) != NC_NOERR)
  {

  }

  return NC_NOERR;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//save_netcdf_3
//save a netCDF test file without variables and dimensions 
/////////////////////////////////////////////////////////////////////////////////////////////////////

int save_netcdf_3(const char * file_name)
{
  int nc_id;

  if(nc_create(file_name, NC_NETCDF4|NC_CLOBBER, &nc_id) != NC_NOERR)
  {
    return NC2_ERR;
  }

  if(nc_close(nc_id) != NC_NOERR)
  {

  }

  return NC_NOERR;
}