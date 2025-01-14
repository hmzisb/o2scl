/*
  -------------------------------------------------------------------
  
  Copyright (C) 2006-2022, Andrew W. Steiner
  
  This file is part of O2scl.
  
  O2scl is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 3 of the License, or
  (at your option) any later version.
  
  O2scl is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with O2scl. If not, see <http://www.gnu.org/licenses/>.

  -------------------------------------------------------------------
*/
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef O2SCL_PYTHON
#include <Python.h>
#endif

#include <o2scl/funct.h>

using namespace std;
using namespace o2scl;

#ifdef O2SCL_PYTHON

funct_python::funct_python(std::string module, std::string func,
                           int v) {

  verbose=v;
  
  if (o2scl_settings.py_initialized==false) {
    if (verbose>0) {
      cout << "Running py_init()." << endl;
    }
    o2scl_settings.py_init();
  }
  set_function(module,func);
}

funct_python::~funct_python() {
  if (verbose>0) {
    cout << "Decref func." << endl;
  }
  Py_DECREF(pFunc);
  if (verbose>0) {
    cout << "Decref args." << endl;
  }
  Py_DECREF(pArgs);
  if (verbose>0) {
    cout << "Decref module." << endl;
  }
  Py_DECREF(pModule);
  if (verbose>0) {
    cout << "Decref name." << endl;
  }
  Py_DECREF(pName);
  if (verbose>0) {
    cout << "Done in funct_python destructor." << endl;
  }
}

int funct_python::set_function(std::string module, std::string func) {
    
  // Get the Unicode name of the user-specified module
  if (verbose>0) {
    cout << "Getting unicode for module name()." << endl;
  }
  pName=PyUnicode_FromString(module.c_str());
  if (pName==0) {
    O2SCL_ERR2("Create module name failed in ",
              "funct_python::set_function().",o2scl::exc_efailed);
  }

  // Import the user-specified module
  if (verbose>0) {
    cout << "Importing module." << endl;
  }
  pModule=PyImport_Import(pName);
  if (pModule==0) {
    O2SCL_ERR2("Load module failed in ",
              "funct_python::set_function().",o2scl::exc_efailed);
  }

  // Setup the arguments to the python function
  if (verbose>0) {
    cout << "Getting arguments for python function." << endl;
  }
  pArgs=PyTuple_New(1);
  if (pArgs==0) {
    O2SCL_ERR2("Create arg tuple failed in ",
               "funct_python::set_function().",o2scl::exc_efailed);
  }

  // Load the python function
  if (verbose>0) {
    cout << "Loading python function." << endl;
  }
  pFunc=PyObject_GetAttrString(pModule,func.c_str());
  if (pFunc==0) {
    O2SCL_ERR2("Get function failed in ",
               "funct_python::set_function().",o2scl::exc_efailed);
  }
  
  return 0;
}

double funct_python::operator()(double x) const {

  // Create a python object from the value
  if (verbose>0) {
    cout << "Creating python object from double." << endl;
  }
  PyObject *pValue=PyFloat_FromDouble(x);
  if (pValue==0) {
    O2SCL_ERR2("Value creation failed in ",
               "funct_python::operator().",o2scl::exc_efailed);
  }

  // Set the python function arguments
  if (verbose>0) {
    cout << "Setting item in tuple." << endl;
  }
  int ret=PyTuple_SetItem(pArgs,0,pValue);
  if (ret!=0) {
    O2SCL_ERR2("Tuple set failed in ",
               "funct_python::operator().",o2scl::exc_efailed);
  }

  // Call the python function
  if (verbose>0) {
    cout << "Call python function." << endl;
  }
  PyObject *result=PyObject_CallObject(pFunc,pArgs);
  if (result==0) {
    O2SCL_ERR2("Function call failed in ",
               "funct_python::operator().",o2scl::exc_efailed);
  }

  double y=PyFloat_AsDouble(result);

  if (verbose>0) {
    cout << "Decref value and result." << endl;
  }
  Py_DECREF(pValue);
  Py_DECREF(result);
  
  if (verbose>0) {
    cout << "Done in funct_python::operator()." << endl;
  }
    
  return y;
}

#endif
