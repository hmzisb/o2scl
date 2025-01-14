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
#ifndef O2SCL_MM_FUNCT_H
#define O2SCL_MM_FUNCT_H

/** \file mm_funct.h
    \brief Function object classes for multi-dimensional functions
*/

#include <string>

#include <boost/numeric/ublas/vector.hpp>

#include <o2scl/calc_utf8.h>
#include <o2scl/lib_settings.h>

#ifdef O2SCL_PYTHON
#include <Python.h>
#endif

namespace o2scl {

  /// Array of multi-dimensional functions typedef in src/base/mm_funct.h
  typedef std::function<
    int(size_t,const boost::numeric::ublas::vector<double> &,
	boost::numeric::ublas::vector<double> &) > mm_funct;

  /** \brief Array of multi-dimensional functions in an array of strings
   */
  class mm_funct_strings {

  public:
      
    /** \brief Specify the strings
     */
    template<class vec_string_t=std::vector<std::string> >
      mm_funct_strings(int nv, vec_string_t &exprs,
			 vec_string_t &var_arr) {

      st_nv=nv;
      st_forms.resize(nv);
      st_vars.resize(nv);
      calc.resize(nv);
      for (int i=0;i<nv;i++) {
	calc[i].compile(exprs[i].c_str(),&vars);
	st_vars[i]=var_arr[i];
	st_forms[i]=exprs[i];
      }
    }
      
    virtual ~mm_funct_strings() {
    };
      
    /** \brief Set the values of the auxilliary parameters that were
	specified in 'parms' in the constructor
    */
    int set_parm(std::string name, double val) {
      vars[name]=val;
      return 0;
    }
      
    /** \brief Compute \c nv functions, \c y, of \c nv variables
	stored in \c x with parameter \c pa.
    */
    template<class vec_t=boost::numeric::ublas::vector<double> >
      int operator()(size_t nv, const vec_t &x, vec_t &y) {

      for(size_t i=0;i<nv;i++) {
	vars[st_vars[i]]=x[i];
      }
      for(size_t i=0;i<nv;i++) {
	y[i]=calc[i].eval(&vars);
      }
      return 0;
    }
      
    /// Set the functions
    template<class vec_string_t=std::vector<std::string> >
      void set_function(int nv, vec_string_t &exprs,
			vec_string_t &var_arr) {

      st_nv=nv;
      st_forms.resize(nv);
      st_vars.resize(nv);
      calc.resize(nv);
      for (int i=0;i<nv;i++) {
	calc[i].compile(exprs[i],&vars);
	st_vars[i]=var_arr[i];
	st_forms[i]=exprs[i];
      }

      return;
    }
      
#ifndef DOXYGEN_INTERNAL
      
  protected:
      
    /// The function parsers
    std::vector<calc_utf8<> > calc;
      
    /// External variables to include in the function parsing
    std::map<std::string,double> vars;
      
    /// The expressions
    std::vector<std::string> st_forms;
      
    /// The variables
    std::vector<std::string> st_vars;
      
    /// The number of variables
    int st_nv;
      
    mm_funct_strings() {};
      
  private:
      
    mm_funct_strings(const mm_funct_strings &);
    mm_funct_strings& operator=(const mm_funct_strings&);
      
#endif
      
  };

#ifdef O2SCL_PYTHON
  
  /** \brief One-dimensional function from a python function
   */
  template<class vec_t=boost::numeric::ublas::vector<double> >
  class mm_funct_python {
    
  protected:

    /// Python unicode object containing function name
    PyObject *pName;
    
    /// Python module containing function
    PyObject *pModule;
    
    /// Function arguments
    PyObject *pArgs;

    /// Python function
    PyObject *pFunc;

    /// Verbosity parameter
    int verbose;
    
  public:
    
    /** \brief Specify the python and the parameters
     */
    mm_funct_python(std::string module, std::string func, int v=0) {
      verbose=v;
      
      if (o2scl_settings.py_initialized==false) {
        if (verbose>0) {
          std::cout << "Running py_init()." << std::endl;
        }
        o2scl_settings.py_init();
      }
      set_function(module,func);
    }      
    
    virtual ~mm_funct_python() {
      if (verbose>0) {
        std::cout << "Decref func." << std::endl;
      }
      Py_DECREF(pFunc);
      if (verbose>0) {
        std::cout << "Decref args." << std::endl;
      }
      Py_DECREF(pArgs);
      if (verbose>0) {
        std::cout << "Decref module." << std::endl;
      }
      Py_DECREF(pModule);
      if (verbose>0) {
        std::cout << "Decref name." << std::endl;
      }
      Py_DECREF(pName);
      if (verbose>0) {
        std::cout << "Done in mm_funct_python destructor." << std::endl;
      }
    }      
  
    /** \brief Specify the python and the parameters

        This function is called by the constructor and thus
        cannot be virtual.
    */
    int set_function(std::string module, std::string func) {
      
      // Get the Unicode name of the user-specified module
      if (verbose>0) {
        std::cout << "Getting unicode for module name()." << std::endl;
      }
      pName=PyUnicode_FromString(module.c_str());
      if (pName==0) {
        O2SCL_ERR2("Create module name failed in ",
                   "mm_funct_python::set_function().",o2scl::exc_efailed);
      }
      
      // Import the user-specified module
      if (verbose>0) {
        std::cout << "Importing module." << std::endl;
      }
      pModule=PyImport_Import(pName);
      if (pModule==0) {
        O2SCL_ERR2("Load module failed in ",
                   "mm_funct_python::set_function().",o2scl::exc_efailed);
      }

      // Setup the arguments to the python function
      if (verbose>0) {
        std::cout << "Getting arguments for python function." << std::endl;
      }
      pArgs=PyTuple_New(1);
      if (pArgs==0) {
        O2SCL_ERR2("Create arg tuple failed in ",
                   "mm_funct_python::set_function().",o2scl::exc_efailed);
      }
      
      // Load the python function
      if (verbose>0) {
        std::cout << "Loading python function." << std::endl;
      }
      pFunc=PyObject_GetAttrString(pModule,func.c_str());
      if (pFunc==0) {
        O2SCL_ERR2("Get function failed in ",
                   "mm_funct_python::set_function().",o2scl::exc_efailed);
      }
      
      return 0;
    }
    
    /** \brief Compute the function at point \c x and return the result
     */
    virtual int operator()(size_t n, const vec_t &v,
                           vec_t &y) const {
      
      // Create the list object
      PyObject *pList_x=PyList_New(n);
      if (pList_x==0) {
        O2SCL_ERR2("List creation for x failed in ",
                   "mm_funct_python::operator().",o2scl::exc_efailed);
      }

      // Create a python object from the vector
      std::vector<PyObject *> pValues(n);
      if (verbose>0) {
        std::cout << "Creating python object from vector." << std::endl;
      }
      
      for(size_t i=0;i<n;i++) {
        pValues[i]=PyFloat_FromDouble(v[i]);
        if (pValues[i]==0) {
          O2SCL_ERR2("Value creation failed in ",
                     "mm_funct_python::operator().",o2scl::exc_efailed);
        }
        
        // Set the python function arguments
        int iret=PyList_SetItem(pList_x,i,pValues[i]);
        if (iret!=0) {
          O2SCL_ERR2("Item set failed in ",
                     "mm_funct_python::operator().",o2scl::exc_efailed);
        }
      }
      
      int ret=PyTuple_SetItem(pArgs,0,pList_x);
      if (ret!=0) {
        O2SCL_ERR2("Tuple set failed in ",
                   "mm_funct_python::operator().",o2scl::exc_efailed);
      }

      // Call the python function
      if (verbose>0) {
        std::cout << "Call python function." << std::endl;
      }
      PyObject *result=PyObject_CallObject(pFunc,pArgs);
      if (result==0) {
        O2SCL_ERR2("Function call failed in ",
                   "mm_funct_python::operator().",o2scl::exc_efailed);
      }

      for(size_t i=0;i<n;i++) {
        PyObject *yval=PyList_GetItem(result,i);
        if (yval==0) {
          O2SCL_ERR2("Failed to get y list value in ",
                     "mm_funct_python::operator().",o2scl::exc_efailed);
        }
        y[i]=PyFloat_AsDouble(yval);
        if (verbose>0) {
          std::cout << "Decref yval " << i << " of " << pValues.size()
                    << std::endl;
        }
        Py_DECREF(yval);
      }
      
      for(size_t i=0;i<pValues.size();i++) {
        if (verbose>0) {
          std::cout << "Decref value " << i << " of " << pValues.size()
                    << std::endl;
        }
        Py_DECREF(pValues[i]);
      }
      if (verbose>0) {
        std::cout << "Decref list." << std::endl;
      }
      Py_DECREF(pList_x);
      
      if (verbose>0) {
        std::cout << "Decref result." << std::endl;
      }
      Py_DECREF(result);
  
      if (verbose>0) {
        std::cout << "Done in mm_funct_python::operator()." << std::endl;
      }

      return 0;
    }      

  protected:

    mm_funct_python() {};

  private:

    mm_funct_python(const mm_funct_python &);
    mm_funct_python& operator=(const mm_funct_python&);

  };

#endif
  
#ifdef O2SCL_NEVER_DEFINED
  /** \brief A wrapper to specify \ref o2scl::mm_funct-like objects 
      to GSL
  */
  template<class vec_t>
    class mm_funct_gsl : public gsl_multiroot_function {
    
  public:
    
    typedef std::function<int(size_t,const vec_t &, vec_t &)> func_t;

  protected:
    
    /// The function wrapper
    static int funct_wrap(const gsl_vector *x, void *params,
			  gsl_vector *f) {
      func_t *fp=(func_t *)params;
      vec_t x2(x->size), f2(x->size);
      o2scl::vector_copy<double *,vec_t>(x->size,x.data,x2);
      int ret=(*fp)(x->size,x2,f2);
      o2scl::vector_copy<vec_t,double *>(x->size,f2,f.data);
      return ret;
    }

  public:

    /// Create an object based on the specified function, \c f
    funct_gsl(func_t &f) {
      function=&funct_wrap;
      params=&f;
    }
    
  };
#endif

}

#endif
