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
#ifndef O2SCL_FUNCT_H
#define O2SCL_FUNCT_H

/** \file funct.h
    \brief Function object classes for one-dimensional functions
*/

#include <string>
#include <functional>

#include <gsl/gsl_math.h>

#include <boost/numeric/ublas/vector.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>
#ifdef O2SCL_MPFR
#include <boost/multiprecision/mpfr.hpp>
#endif

#include <o2scl/err_hnd.h>
#include <o2scl/calc_utf8.h>
#include <o2scl/lib_settings.h>

#ifdef O2SCL_PYTHON
#include <Python.h>
#endif

namespace o2scl {

  /// One-dimensional function typedef in src/base/funct.h
  typedef std::function<double(double)> funct;

  /// One-dimensional function typedef in src/base/funct.h
  typedef std::function<long double(long double)> funct_ld;

  /** \brief One-dimensional function typedef in src/base/funct.h
   */
  typedef std::function<boost::multiprecision::number<
                          boost::multiprecision::cpp_dec_float<25> >
			(boost::multiprecision::number<
                         boost::multiprecision::cpp_dec_float<25> > )>
  funct_cdf25;
  
  /** \brief One-dimensional function typedef in src/base/funct.h
   */
  typedef std::function<boost::multiprecision::number<
                          boost::multiprecision::cpp_dec_float<35> >
			(boost::multiprecision::number<
                         boost::multiprecision::cpp_dec_float<35> > )>
  funct_cdf35;
  
  /** \brief One-dimensional function typedef in src/base/funct.h
   */
  typedef std::function<boost::multiprecision::cpp_dec_float_50
			(boost::multiprecision::cpp_dec_float_50)>
  funct_cdf50;

#ifdef O2SCL_MPFR
  
  /** \brief One-dimensional function typedef in src/base/funct.h
      
      This typedef is only present if O2SCL_MPFR is
      defined during compilation.
   */
  typedef std::function<boost::multiprecision::mpfr_float_50
			(boost::multiprecision::mpfr_float_50)>
  funct_mp50;
  
#endif
  
  /** \brief One-dimensional function typedef in src/base/funct.h
   */
  typedef std::function<boost::multiprecision::cpp_dec_float_100
			(boost::multiprecision::cpp_dec_float_100)>
  funct_cdf100;
  
  /** \brief One-dimensional function from a string
      
      For example,
      \code
      funct_string f("pi*r^2","r");
      f.set_parm("pi",o2scl_const::pi);
      for(double r=1.0;r<=2.0;r+=0.1) {
        cout << f(x) << endl;
      }
      \endcode
      will print out the area of circles having radii between 1 and 2.
  */
  class funct_string {
    
  public:
    
    /** \brief Specify the string and the parameters
     */
    funct_string(std::string expr, std::string var) {
      calc.compile(expr.c_str(),&vars);
      st_form=expr;
      st_var=var;
    }

    virtual ~funct_string() {
    };

  
    /** \brief Specify the string and the parameters
     */
    int set_function(std::string expr, std::string var) {
      calc.compile(expr.c_str(),&vars);
      st_form=expr;
      st_var=var;
      return 0;
    }

    /** \brief Set the values of the auxilliary parameters that were
	specified in \c parms in the constructor
    */
    int set_parm(std::string name, double val) {
      if (name==st_var) {
	O2SCL_ERR2("A parameter cannot have the same name as ",
		   "the variable in funct_string::set_parm().",
		   o2scl::exc_einval);
      }
      vars[name]=val;
      return 0;
    }
    
    /** \brief Compute the function at point \c x and return the result
     */
    virtual double operator()(double x) const {
      vars[st_var]=x;
      return calc.eval(&vars);
    }

#ifndef DOXYGEN_INTERNAL

  protected:

    /// The object for evaluating strings
    mutable o2scl::calc_utf8<> calc;

    /// Parameter map
    mutable std::map<std::string,double> vars;
    
    /// The expr
    std::string st_form;
    /// The variable
    std::string st_var;

    funct_string() {};

#endif

  private:

    funct_string(const funct_string &);
    funct_string& operator=(const funct_string&);

  };

  /** \brief A wrapper to specify \ref o2scl::funct objects 
      to GSL
   */
  class funct_gsl : public gsl_function {

  protected:
    
    /// The function wrapper
    static double funct_wrap(double x, void *params) {
      funct *fp=(funct *)params;
      return (*fp)(x);
    }

  public:

    /// Create an object based on the specified function, \c f
    funct_gsl(funct &f) {
      function=&funct_wrap;
      params=&f;
    }
    
  };

  /** \brief Two-dimensional function from a string
  */
  class funct2_string {
    
  public:
    
    /** \brief Specify the string and the parameters
     */
    funct2_string(std::string expr, std::string var1, std::string var2) {
      calc.compile(expr.c_str(),&vars);
      st_form=expr;
      st_var1=var1;
      st_var2=var2;
    }

    virtual ~funct2_string() {
    };

  
    /** \brief Specify the string and the parameters
     */
    int set_function(std::string expr, std::string var1,
		     std::string var2) {
      calc.compile(expr.c_str(),&vars);
      st_form=expr;
      st_var1=var1;
      st_var2=var2;
      return 0;
    }

    /** \brief Set the values of the auxilliary parameters that were
	specified in \c parms in the constructor
    */
    int set_parm(std::string name, double val) {
      if (name==st_var1 || name==st_var2) {
	O2SCL_ERR2("A parameter cannot have the same name as ",
		   "a variable in funct_string::set_parm().",
		   o2scl::exc_einval);
      }
      vars[name]=val;
      return 0;
    }
    
    /** \brief Compute the function at point \c x and return the result
     */
    virtual double operator()(double x, double y) const {
      vars[st_var1]=x;
      vars[st_var2]=y;
      return calc.eval(&vars);
    }

#ifndef DOXYGEN_INTERNAL

  protected:

    /// The object for evaluating strings
    mutable o2scl::calc_utf8<> calc;

    /// Parameter map
    mutable std::map<std::string,double> vars;
    
    /// The expr
    std::string st_form;
    /// The variable
    std::string st_var1;
    /// The variable
    std::string st_var2;

    funct2_string() {};

#endif

  private:

    funct2_string(const funct2_string &);
    funct2_string& operator=(const funct2_string&);

  };

#ifdef O2SCL_PYTHON
  
  /** \brief One-dimensional function from a python function
  */
  class funct_python {

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
    funct_python(std::string module, std::string func, int v=0);
    
    virtual ~funct_python();
  
    /** \brief Specify the python and the parameters

        This function is called by the constructor and thus
        cannot be virtual.
     */
    int set_function(std::string module, std::string func);
    
    /** \brief Compute the function at point \c x and return the result
     */
    virtual double operator()(double x) const;

#ifndef DOXYGEN_INTERNAL

  protected:

    funct_python() {};

#endif

  private:

    funct_python(const funct_python &);
    funct_python& operator=(const funct_python&);

  };

#endif

}

#endif
