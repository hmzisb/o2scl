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
#ifndef O2SCL_MISC_H
#define O2SCL_MISC_H
/** \file misc.h
    \brief Miscellaneous functions
*/

#include <cstdlib>
#include <iostream>
#include <string>

// For stringstream for count_words()
#include <sstream>
#include <vector>

// For std::isinf and std::isnan in C++11
#include <cmath>

// For the vec_index class below
#include <map>
#ifndef O2SCL_OLDER_COMPILER
#include <initializer_list>
#endif

#include <boost/multiprecision/number.hpp>
#include <boost/multiprecision/cpp_bin_float.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>

#include <o2scl/err_hnd.h>

namespace o2scl {

  /*
    AWS 10/10/19: A new abs() function is probably overkill, but I am
    concerned that a user who includes math.h before an o2scl header
    file might get the wrong abs() function. (see
    https://stackoverflow.com/questions/21392627/
    abs-vs-stdabs-what-does-the-reference-say ). The usual recommendation
    is just to use std::abs, but I have had problems with that working
    on Ubuntu. 
  */
  
  /// \name New compability functions
  //@{
  /** \brief Absolute value for single precision numbers
   */
  float o2abs(const float x);
  
  /** \brief Absolute value for double precision numbers
   */
  double o2abs(const double x);

  /** \brief Absolute value for long double
   */
  long double o2abs(const long double x);

  /** \brief Absolute value for cpp_dec_float_35
   */
  boost::multiprecision::number<boost::multiprecision::cpp_dec_float<35> >
    o2abs(const boost::multiprecision::number<boost::multiprecision::cpp_dec_float<35> > x);
  
  /** \brief Absolute value for cpp_dec_float_50
   */
  boost::multiprecision::cpp_dec_float_50
    o2abs(const boost::multiprecision::cpp_dec_float_50 x);
  
  /** \brief Absolute value for cpp_dec_float_100
   */
  boost::multiprecision::cpp_dec_float_100
    o2abs(const boost::multiprecision::cpp_dec_float_100 x);
  
  /** \brief Absolute value for cpp_bin_float_50
   */
  boost::multiprecision::cpp_bin_float_50
    o2abs(const boost::multiprecision::cpp_bin_float_50 x);
  
  /** \brief Absolute value for cpp_bin_float_100
   */
  boost::multiprecision::cpp_bin_float_100
    o2abs(const boost::multiprecision::cpp_bin_float_100 x);
  
  /** \brief Exponential for single precision numbers
   */
  float o2exp(const float x);
  
  /** \brief Exponential for double precision numbers
   */
  double o2exp(const double x);

  /** \brief Exponential for long double
   */
  long double o2exp(const long double x);

  /** \brief Exponential for cpp_dec_float_35
   */
  boost::multiprecision::number<boost::multiprecision::cpp_dec_float<35> >
    o2exp(const boost::multiprecision::number<boost::multiprecision::cpp_dec_float<35> > x);
  
  /** \brief Exponential for cpp_dec_float_50
   */
  boost::multiprecision::cpp_dec_float_50
    o2exp(const boost::multiprecision::cpp_dec_float_50 x);
  
  /** \brief Exponential for cpp_dec_float_100
   */
  boost::multiprecision::cpp_dec_float_100
    o2exp(const boost::multiprecision::cpp_dec_float_100 x);
  
  /** \brief Logarithm for single precision numbers
   */
  float o2log(const float x);
  
  /** \brief Logarithm for double precision numbers
   */
  double o2log(const double x);

  /** \brief Logarithm for long double
   */
  long double o2log(const long double x);

  /** \brief Logarithm for cpp_dec_float_35
   */
  boost::multiprecision::number<boost::multiprecision::cpp_dec_float<35> >
    o2log(const boost::multiprecision::number<boost::multiprecision::cpp_dec_float<35> > x);
  
  /** \brief Logarithm for cpp_dec_float_50
   */
  boost::multiprecision::cpp_dec_float_50
    o2log(const boost::multiprecision::cpp_dec_float_50 x);
  
  /** \brief Logarithm for cpp_dec_float_100
   */
  boost::multiprecision::cpp_dec_float_100
    o2log(const boost::multiprecision::cpp_dec_float_100 x);
  
  /** \brief Square root for single precision numbers
   */
  float o2sqrt(const float x);
  
  /** \brief Square root for double precision numbers
   */
  double o2sqrt(const double x);

  /** \brief Square root for long double
   */
  long double o2sqrt(const long double x);

  /** \brief Square root for cpp_dec_float_35
   */
  boost::multiprecision::number<boost::multiprecision::cpp_dec_float<35> >
    o2sqrt(const boost::multiprecision::number<boost::multiprecision::cpp_dec_float<35> > x);
  
  /** \brief Square root for cpp_dec_float_50
   */
  boost::multiprecision::cpp_dec_float_50
    o2sqrt(const boost::multiprecision::cpp_dec_float_50 x);
  
  /** \brief Square root for cpp_dec_float_100
   */
  boost::multiprecision::cpp_dec_float_100
    o2sqrt(const boost::multiprecision::cpp_dec_float_100 x);
  
  /** \brief Square root for cpp_bin_float_50
   */
  boost::multiprecision::cpp_bin_float_50
    o2sqrt(const boost::multiprecision::cpp_bin_float_50 x);
  
  /** \brief Square root for cpp_bin_float_100
   */
  boost::multiprecision::cpp_bin_float_100
    o2sqrt(const boost::multiprecision::cpp_bin_float_100 x);
  
  /** \brief Exponential for single precision numbers
   */
  float o2pow(const float x, const float y);
  
  /** \brief Exponential for double precision numbers
   */
  double o2pow(const double x, const double y);

  /** \brief Exponential for long double
   */
  long double o2pow(const long double x, const long double y);

  /** \brief Exponential for cpp_dec_float_35
   */
  boost::multiprecision::number<boost::multiprecision::cpp_dec_float<35> >
  o2pow(const boost::multiprecision::number<boost::multiprecision::cpp_dec_float<35> > x,
        const boost::multiprecision::number<boost::multiprecision::cpp_dec_float<35> > y);
  
  /** \brief Exponential for cpp_dec_float_50
   */
  boost::multiprecision::cpp_dec_float_50
  o2pow(const boost::multiprecision::cpp_dec_float_50 x,
        const boost::multiprecision::cpp_dec_float_50 y);
  
  /** \brief Exponential for cpp_dec_float_100
   */
  boost::multiprecision::cpp_dec_float_100
  o2pow(const boost::multiprecision::cpp_dec_float_100 x,
        const boost::multiprecision::cpp_dec_float_100 y);
  
  /** \brief Exponential for cpp_bin_float_50
   */
  boost::multiprecision::cpp_bin_float_50
  o2pow(const boost::multiprecision::cpp_bin_float_50 x,
        const boost::multiprecision::cpp_bin_float_50 y);
  
  /** \brief Exponential for cpp_bin_float_100
   */
  boost::multiprecision::cpp_bin_float_100
  o2pow(const boost::multiprecision::cpp_bin_float_100 x,
        const boost::multiprecision::cpp_bin_float_100 y);
  
  /** \brief Compatbility function for isfinite()

      AWS, 11/11/19: Older compilers seem to require std::isfinite(),
      but then this causes problems making generic code which can use
      boost multiprecision arithmetic, so this function attempts
      to solve those problems.
  */
  bool o2isfinite(const double x);

  /** \brief Compatbility function for isfinite()
   */
  bool o2isfinite(const boost::multiprecision::number<boost::multiprecision::cpp_dec_float<35> > x);
  
  bool o2isfinite(const boost::multiprecision::number<boost::multiprecision::cpp_dec_float<25> > x);

  /** \brief Compatbility function for isfinite()
   */
  bool o2isfinite(const boost::multiprecision::cpp_dec_float_50 x);

  /** \brief Compatbility function for isfinite()
   */
  bool o2isfinite(const boost::multiprecision::cpp_dec_float_100 x);

  /** \brief Compatbility function for isfinite()
   */
  bool o2isfinite(const boost::multiprecision::cpp_bin_float_50 x);

  /** \brief Compatbility function for isfinite()
   */
  bool o2isfinite(const boost::multiprecision::cpp_bin_float_100 x);

  /** \brief Compatbility function for hypot()
  */
  float o2hypot(const float x, const float y);
  
  /** \brief Compatbility function for hypot()
  */
  double o2hypot(const double x, const double y);
  
  /** \brief Compatbility function for hypot()
  */
  long double o2hypot(const long double x, const long double y);

  /** \brief Compatbility function for hypot()
   */
  boost::multiprecision::number<boost::multiprecision::cpp_dec_float<35> >
  o2hypot(const boost::multiprecision::number<boost::multiprecision::cpp_dec_float<35> > x,
	  const boost::multiprecision::number<boost::multiprecision::cpp_dec_float<35> > y);

  /** \brief Compatbility function for hypot()
   */
  boost::multiprecision::cpp_dec_float_50
    o2hypot(const boost::multiprecision::cpp_dec_float_50 x,
	    const boost::multiprecision::cpp_dec_float_50 y);

  /** \brief Compatbility function for hypot()
   */
  boost::multiprecision::cpp_dec_float_100
    o2hypot(const boost::multiprecision::cpp_dec_float_100 x,
	    const boost::multiprecision::cpp_dec_float_100 y);
  
  //@}
  
  /// \name Functions from src/base/misc.h
  //@{
  /** \brief Calculate a Fermi-Dirac distribution function safely
      
      \f$ \left[1+\exp\left(E/T-\mu/T\right)\right]^{-1} \f$ 
      
      This calculates a Fermi-Dirac distribution function guaranteeing
      that numbers larger than \f$ \exp(\mathrm{limit}) \f$ and
      smaller than \f$ \exp(-\mathrm{limit}) \f$ will be avoided. The
      default value of <tt>limit=40</tt> ensures accuracy to within 1
      part in \f$ 10^{17} \f$ compared to the maximum of the
      distribution (which is unity).
      
      Note that this function may return Inf or NAN if \c limit is too 
      large, depending on the machine precision.
  */
  double fermi_function(double E, double mu, double T, double limit=40.0);
  
  /** \brief Calculate a Bose-Einstein distribution function safely

      \f$ \left[\exp\left(E/T-\mu/T\right)-1\right]^{-1} \f$ 

      This function computes a Bose-Einstein distribution function
      using an expansion to ensure accurate results when 
      \f$ (E-\mu)/T \f$ is near zero. 

      \note This function may return Inf or NAN if \c limit is too 
      large, depending on the machine precision.
      
      This function is used in the <tt>o2scl::boson_rel</tt> class
      in \o2p . 
  */
  double bose_function(double E, double mu, double T, double limit=40.0);

  /** \brief Store the first line from the output of the shell
      command \c cmd up to \c nmax characters in \c result
      
      \note This function uses popen() and may not work properly on
      some systems. If HAVE_POPEN was not defined during O2scl's
      compilation, then this function will throw an exception (or if
      \c err_on_fail is false, it will return a nonzero value).

      \note The result string may contain a carriage return at
      the end.
  */
  int pipe_cmd_string(std::string cmd, std::string &result,
		      bool err_on_fail=true, int nmax=80);

  /** \brief Execute a python command and return the resulting string
      
      \verbatim
      python_cmd_string("\"print(3+5)\"",result);
      \endverbatim
  */
  int python_cmd_string(std::string cmd, std::string &result,
		      bool err_on_fail=true, int nmax=80);
  
  /** \brief Return the first line from the output of the shell
      command \c cmd up to \c nmax characters

      This function always throws exceptions if it fails.

      \note The result string may contain a carriage return at
      the end.
  */
  std::string pipe_cmd_string(std::string cmd, int nmax=80);

  /** \brief Return true if file named \c fname exists
   */
  bool file_exists(std::string fname);

  /** \brief Count the number of words in the string \c str 
   
      Words are defined as groups of characters separated by
      whitespace, where whitespace is any combination of adjacent
      spaces, tabs, carriage returns, etc. On most systems, whitespace
      is usually defined as any character corresponding to the
      integers 9 (horizontal tab), 10 (line feed), 11 (vertical tab),
      12 (form feed), 13 (carriage return), and 32 (space bar). The
      test program \c misc_ts enumerates the characters between 0 and
      255 (inclusive) that count as whitespace for this purpose.

      \future Make consistent with split_string().
  */
  size_t count_words(std::string str);
  
  /** \brief Remove all whitespace from the string \c s

      This function removes all characters in \c s which correspond to
      the integer values 9, 10, 11, 12, 13, or 32.
  */
  void remove_whitespace(std::string &s);

  /** \brief Remove all whitespace, punctuation, parenthesis, and slashes 
      from the string \c s

      \warning Experimental.
  */
  void remove_ws_punct(std::string &s);

  /** \brief Take a string of binary quads and compress them to 
      hexadecimal digits

      This function proceeds from left to right, ignoring parts of the
      string that do not consist of squences of four '1's or '0's.
  */
  std::string binary_to_hex(std::string s);

  /** \brief Convert RGB to HSV color
      
      Taken from Nathan Schaller's webpage at
      http://www.cs.rit.edu/~ncs/color/t_convert.html 
      
      The inputs should be in the ranges \f$ h \in [0,360] \f$, \f$ s
      \in [0,1] \f$, and \f$ v \in [0,1] \f$. The output values \c r,
      \c g, and \c b are \f$ \in [0,1] \f$.
      
      If s == 0, then h = -1 (undefined)
  */
  void RGBtoHSV(double r, double g, double b, 
		double &h, double &s, double &v);
  
  /** \brief Convert RGB to HSV color
      
      Taken from Nathan Schaller's webpage at
      http://www.cs.rit.edu/~ncs/color/t_convert.html 
      
      The inputs should be in the ranges \f$ h \in [0,360] \f$, \f$ s
      \in [0,1] \f$, and \f$ v \in [0,1] \f$. The output values \c r,
      \c g, and \c b are \f$ \in [0,1] \f$.
      
      If s == 0, then h = -1 (undefined)
  */
  void HSVtoRGB(double h, double s, double v, 
		double &r, double &g, double &b);
  //@}
  
  /** \brief Generate number sequence for testing
      
      This class is used to generate combinations of coefficients for
      testing the polynomial solvers.

      For example, the first 15 numbers generated with
      the default radix are
      \verbatim
      1.000000e+00
      0.000000e+00
      -1.000000e+00
      5.000000e-01
      -5.000000e-01
      7.500000e-01
      -7.500000e-01
      1.500000e+00
      -1.500000e+00
      2.000000e+00
      -2.000000e+00
      2.500000e-01
      -2.500000e-01
      8.750000e-01
      -8.750000e-01
      1.250000e+00
      -1.250000e+00
      4.000000e+00
      -4.000000e+00
      1.250000e-01
      -1.250000e-01
      9.375000e-01
      -9.375000e-01
      1.125000e+00
      -1.125000e+00
      8.000000e+00
      -8.000000e+00
      6.250000e-02
      -6.250000e-02
      \endverbatim

      This function is used in <tt>src/other/poly_ts.cpp</tt> which
      tests the polynomial solvers.

      \note With the default radix and double precision, this only
      gives about 400 unique values before some repetition is 
      encountered. Smaller radices enable more unique values.

      \verbatim embed:rst
      .. todo:: 

         In class gen_test_number, need to test this class somehow.

      \endverbatim

  */
  template<class fp_t=double> class gen_test_number {

#ifndef DOXYGEN_INTERNAL

  protected:

    /// Count number of numbers generated so far
    int n;

    /// The radix for the nuber generation (default 2.0)
    fp_t radix;

#endif

  public:

    gen_test_number() {
      n=0;
      radix=2;
    }
    
    /** \brief Reset to the first number in the sequence
     */
    void reset() {
      n=0;
      return;
    }

    /** \brief The base for the number generation sequences

        Only numbers greater than 1.0 are allowed
     */
    void set_radix(fp_t r) {
      if (r<=1) {
        O2SCL_ERR("Invalid radix in gen_test_number().",
                  o2scl::exc_einval);
      }
      radix=r;
      return;
    }

    /** \brief Generate the next number in the sequence
     */
    fp_t gen() {
      
      fp_t x=0;
      
      // Since we're in the o2scl namespace, we explicitly
      // specify std::tanh() below.

      int d=((fp_t)(n-3))/8;
      
      if (n==0) {
	x=1;
      } else if (n==1) {
	x=0;
      } else if (n==2) {
	x=-1;
      } else if ((n-3)%8==0) {
        // The sequence 0.5, 0.25, 0.125, ..., -> 0
        x=pow(radix,-(d+1));
      } else if ((n-3)%8==1) {
        // The sequence -0.5, -0.25, -0.125, ... -> 0
        x=-pow(radix,-(d+1));
      } else if ((n-3)%8==2) {
        // The sequence 0.75, 0.875, 0.9375, ... -> 1
        x=1.0-pow(radix,-(d+2));
      } else if ((n-3)%8==3) {
        // The sequence -0.75, -0.875, -0.9375, ... -> -1
        x=-1.0+pow(radix,-(d+2));
      } else if ((n-3)%8==4) {
        // The sequence 1.5, 1.25, 1.125, ... -> 1
        x=1.0+pow(radix,-(d+1));
      } else if ((n-3)%8==5) {
        // The sequence -1.5, -1.25, -1.125, ... -> -1
        x=-1.0-pow(radix,-(d+1));
      } else if ((n-3)%8==6) {
        // The sequence 2, 4, 8, ... -> \infty
        x=pow(radix,d+1);
      } else if ((n-3)%8==7) {
        // The sequence -2, -4, -8, ... -> -\infty
        x=-pow(radix,d+1);
      }
      n++;
      return x;
    }
  };

  /// \name Quadratic extrema functions in src/base/misc.h
  //@{
  /** \brief Return the x value of the extremum of a quadratic defined by 
      three \f$ (x,y) \f$ pairs

      This function should work for any floating-point data type,
      but will suffer from problems due to lack of precision in
      some cases.
  */
  template<class data_t>
    data_t quadratic_extremum_x(const data_t x1, const data_t x2, 
				const data_t x3, const data_t y1, 
				const data_t y2, const data_t y3) {

    if (x1==x2 || x2==x3 || x1==x3) {
      O2SCL_ERR2("Two abscissae cannot be equal in function ",
		 "quadratic_extremum_x().",exc_einval);
    }
    
    /*
      Start with:
      y1=a x1^2 + b x1 + c
      y2=a x2^2 + b x2 + c
      y3=a x3^2 + b x3 + c
      
      Eliminate 'c':
      (y1-y2)=a(x1^2-x2^2)+b(x1-x2)
      (y3-y2)=a(x3^2-x2^2)+b(x3-x2)
      
      Eliminate 'b':
      (x3-x2)*(y1-y2)=a*(x1^2-x2^2)*(x3-x2)+b*(x1-x2)*(x3-x2)
      (x1-x2)*(y3-y2)=a*(x3^2-x2^2)*(x1-x2)+b*(x3-x2)*(x1-x2)
      
      Alternatively, eliminate 'c' with:
      (y2-y1)=a(x2^2-x1^2)+b(x2-x1)
      (y3-y1)=a(x3^2-x1^2)+b(x3-x1)
      
      Eliminate 'b':
      (x3-x1)*(y2-y1)=a(x2^2-x1^2)*(x3-x1)+b(x2-x1)*(x3-x1)
      (x2-x1)*(y3-y1)=a(x3^2-x1^2)*(x2-x1)+b(x3-x1)*(x2-x1)
    */
    
    data_t a,b,c,den=(x1*x1-x2*x2)*(x3-x2)-(x3*x3-x2*x2)*(x1-x2);
    if (den==0.0) {
      den=(x2*x2-x1*x1)*(x3-x1)-(x3*x3-x1*x1)*(x2-x1);
      a=((x3-x1)*(y2-y1)-(x2-x2)*(y3-y1))/den;
    } else {
      a=((x3-x2)*(y1-y2)-(x1-x2)*(y3-y2))/den;
    }
    b=(y1-y2-a*(x1*x1-x2*x2))/(x1-x2);
    c=y2-a*x2*x2-b*x2;
    
    return -b/2.0/a;
  }

  /** \brief Return values related to a quadratic defined by 
      three \f$ (x,y) \f$ pairs
      
      This function provides the three coefficients of the 
      quadratic, \c a, \c b, and \c c, and the denominator
      \c den.

      This function should work for any floating-point data type,
      but will suffer from problems due to lack of precision in
      some cases.
  */
  template<class data_t>
    void quadratic_extremum_y_full(const data_t x1, const data_t x2, 
				   const data_t x3, const data_t y1, 
				   const data_t y2, const data_t y3,
				   const data_t &xmin, const data_t &ymin,
				   const data_t &a, const data_t &b,
				   const data_t &c, const data_t &den) {

    if (x1==x2 || x2==x3 || x1==x3) {
      O2SCL_ERR2("Two abscissae cannot be equal in function ",
		 "quadratic_extremum_y().",exc_einval);
    }
    
    den=(x1*x1-x2*x2)*(x3-x2)-(x3*x3-x2*x2)*(x1-x2);
    if (den==0.0) {
      den=(x2*x2-x1*x1)*(x3-x1)-(x3*x3-x1*x1)*(x2-x1);
      a=((x3-x1)*(y2-y1)-(x2-x2)*(y3-y1))/den;
    } else {
      a=((x3-x2)*(y1-y2)-(x1-x2)*(y3-y2))/den;
    }
    b=(y1-y2-a*(x1*x1-x2*x2))/(x1-x2);
    c=y2-a*x2*x2-b*x2;
    xmin=-b/2.0/a;
    ymin=c-b*b/4.0/a;
    return;
  }

  /** \brief Return the y value of the extremum of a quadratic defined by 
      three \f$ (x,y) \f$ pairs

      This function should work for any floating-point data type,
      but will suffer from problems due to lack of precision in
      some cases.
  */
  template<class data_t>
    data_t quadratic_extremum_y(const data_t x1, const data_t x2, 
				const data_t x3, const data_t y1, 
				const data_t y2, const data_t y3) {
    
    if (x1==x2 || x2==x3 || x1==x3) {
      O2SCL_ERR2("Two abscissae cannot be equal in function ",
		 "quadratic_extremum_y().",exc_einval);
    }
    
    data_t a,b,c,den=(x1*x1-x2*x2)*(x3-x2)-(x3*x3-x2*x2)*(x1-x2);
    if (den==0.0) {
      den=(x2*x2-x1*x1)*(x3-x1)-(x3*x3-x1*x1)*(x2-x1);
      a=((x3-x1)*(y2-y1)-(x2-x2)*(y3-y1))/den;
    } else {
      a=((x3-x2)*(y1-y2)-(x1-x2)*(y3-y2))/den;
    }
    b=(y1-y2-a*(x1*x1-x2*x2))/(x1-x2);
    c=y2-a*x2*x2-b*x2;
    
    return c-b*b/4/a;    
  }

  /** \brief Return the (x,y) for the extremum of a quadratic defined by 
      three \f$ (x,y) \f$ pairs

      This function should work for any floating-point data type,
      but will suffer from problems due to lack of precision in
      some cases.
  */
  template<class data_t>
    void quadratic_extremum_xy(const data_t x1, const data_t x2, 
			       const data_t x3, const data_t y1, 
			       const data_t y2, const data_t y3,
			       data_t &x, data_t &y) {
    
    if (x1==x2 || x2==x3 || x1==x3) {
      O2SCL_ERR2("Two abscissae cannot be equal in function ",
		 "quadratic_extremum_xy().",exc_einval);
    }
    
    data_t a,b,c,den=(x1*x1-x2*x2)*(x3-x2)-(x3*x3-x2*x2)*(x1-x2);
    if (den==0.0) {
      den=(x2*x2-x1*x1)*(x3-x1)-(x3*x3-x1*x1)*(x2-x1);
      a=((x3-x1)*(y2-y1)-(x2-x2)*(y3-y1))/den;
    } else {
      a=((x3-x2)*(y1-y2)-(x1-x2)*(y3-y2))/den;
    }
    b=(y1-y2-a*(x1*x1-x2*x2))/(x1-x2);
    c=y2-a*x2*x2-b*x2;
    
    x=-b/2/a;
    y=c-b*b/4/a;    

    return;
  }

  /** \brief Return the (x,y) for the extremum of a quadratic defined by 
      three \f$ (x,y) \f$ pairs

      This function should work for any floating-point data type,
      but will suffer from problems due to lack of precision in
      some cases.
  */
  template<class data_t>
    void quadratic_extremum_coeffs(const data_t x1, const data_t x2, 
				   const data_t x3, const data_t y1, 
				   const data_t y2, const data_t y3,
				   data_t &a, data_t &b, data_t &c) {
    
    if (x1==x2 || x2==x3 || x1==x3) {
      O2SCL_ERR2("Two abscissae cannot be equal in function ",
		 "quadratic_extremum_coeffs().",exc_einval);
    }
    
    data_t den=(x1*x1-x2*x2)*(x3-x2)-(x3*x3-x2*x2)*(x1-x2);
    if (den==0.0) {
      den=(x2*x2-x1*x1)*(x3-x1)-(x3*x3-x1*x1)*(x2-x1);
      a=((x3-x1)*(y2-y1)-(x2-x2)*(y3-y1))/den;
    } else {
      a=((x3-x2)*(y1-y2)-(x1-x2)*(y3-y2))/den;
    }
    b=(y1-y2-a*(x1*x1-x2*x2))/(x1-x2);
    c=y2-a*x2*x2-b*x2;

    return;
  }
  //@}

  /** \brief A class to assign string labels to array indices
      
      \future Create a method to remove strings from the list
   */
  class vec_index {
    
  protected:

    /// The map version for string lookup
    std::map<std::string,size_t,std::greater<std::string> > tmap;
    /// The vector version for size_t lookup
    std::vector<std::string> tvec;

  public:

    /// \name Constructors
    //@{
    /// Create an empty assignment
    vec_index() {}
    
    /// Create an assignment based on the strings in \c list
    vec_index(const std::vector<std::string> &list) {
      for(size_t i=0;i<list.size();i++) {
	tmap.insert(std::make_pair(list[i],i));
	tvec.push_back(list[i]);
      }
    }
    
#ifndef O2SCL_OLDER_COMPILER

    /// Create an assignment based on the strings in \c list
    vec_index(std::initializer_list<std::string> list) {
      size_t ix=0;
      for(std::initializer_list<std::string>::iterator it=list.begin();
	  it!=list.end();it++) {
	tmap.insert(std::make_pair(*it,ix));
	tvec.push_back(*it);
	ix++;
      }
    }
    
#endif

    /// Copy constructor
    vec_index(const vec_index &t) {
      tmap=t.tmap;
      tvec=t.tvec;
    }
    //@}

    /// \name Translation between size_t and string
    //@{
    /// Return the string of index \c i
    std::string operator()(size_t i) const {
      return tvec[i];
    }

    /// Return the index of string \c s
    size_t operator()(std::string s) const {
      std::map<std::string,size_t,
	std::greater<std::string> >::const_iterator it;
      it=tmap.find(s);
      if (it==tmap.end()) {
	std::string str=((std::string)"Failed to find '")+s+
	  "' in vec_index::operator().";
	O2SCL_ERR(str.c_str(),o2scl::exc_efailed);
      }
      return it->second;
    }

    /// Return the string of index \c i
    std::string operator[](size_t i) const {
      return tvec[i];
    }

    /// Return the index of string \c s
    size_t operator[](std::string s) const {
      std::map<std::string,size_t,
	std::greater<std::string> >::const_iterator it;
      it=tmap.find(s);
      if (it==tmap.end()) {
	std::string str=((std::string)"Failed to find '")+s+
	  "' in vec_index::operator[].";
	O2SCL_ERR(str.c_str(),o2scl::exc_efailed);
      }
      return it->second;
    }
    //@}

    /// \name Other useful methods
    //@{
    /// Return the size
    size_t size() const {
      return tvec.size();
    }

    /// Return the list of strings
    std::vector<std::string> list() const {
      return tvec;
    }

    /// Copy constructor by assignment
    vec_index &operator=(const vec_index &t) {
      if (this!=&t) {
	tmap=t.tmap;
	tvec=t.tvec;
      }
      return *this;
    }
    //@}
    
    /// \name Adding strings
    //@{
    /// Add string \c s and assign it the next index
    void append(std::string s) {
      tmap.insert(std::make_pair(s,tvec.size()));
      tvec.push_back(s);
      return;
    }
    
    /// Add a list of strings
    void append(const std::vector<std::string> &list) {
      size_t ix=tvec.size();
      for(size_t i=0;i<list.size();i++) {
	tmap.insert(std::make_pair(list[i],ix));
	tvec.push_back(list[i]);
	ix++;
      }
    }

#ifndef O2SCL_OLDER_COMPILER
    
    /// Add a list of strings
    void append(std::initializer_list<std::string> list) {
      size_t ix=tvec.size();
      for(std::initializer_list<std::string>::iterator it=list.begin();
	  it!=list.end();it++) {
	tmap.insert(std::make_pair(*it,ix));
	tvec.push_back(*it);
	ix++;
      }
    }
    
#endif
    //@}
    
  };
  
  /// \name Filesystem wrapper functions in src/base/misc.h
  //@{
  /** \brief Wrapper for the glob() function which
      finds files which match a pattern

      \warning This function may not work on all operating 
      systems. 
      
      \future Fix for openSUSE (see
      https://github.com/awsteiner/o2scl/issues/8 )

      \verbatim test

      blah blah

      blah blah 2
      \endverbatim
  */
  int glob_wrapper(std::string pattern,
		   std::vector<std::string> &matches);

  /** \brief Wrapper for the wordexp() function
   */
  int wordexp_wrapper(std::string word,
		      std::vector<std::string> &matches);
  
  /** \brief Use wordexp() to obtain a single file
      
      The error handler is called if wordexp() returns either
      no files or more than one file.
   */
  void wordexp_single_file(std::string &fname);
  //@}

  /** \brief A class to support extended terminal output such 
      as colors and graphical characters
   */
  class terminal {

  protected:
    
    /** \brief If true, this terminal has been redirected to a file
     */
    bool redirected;
    
  public:

    terminal();

    /// Return true if this terminal has been redirected to a file
    bool is_redirected() {
      return redirected;
    }

    /// Determine string length, ignoring vt100 terminal sequences
    size_t str_len(std::string str);

    /// Generate a horizontal rule
    std::string hrule(size_t n=78);

    /// Switch to cyan foreground
    std::string cyan_fg();
    
    /// Switch to magenta foreground
    std::string magenta_fg();
    
    /// Switch to yellow foreground
    std::string yellow_fg();
    
    /// Switch to red foreground
    std::string red_fg();
    
    /// Switch to green foreground
    std::string green_fg();
    
    /// Switch to blue foreground
    std::string blue_fg();
    
    /// Switch to cyan background
    std::string cyan_bg();
    
    /// Switch to magenta background
    std::string magenta_bg();
    
    /// Switch to yellow background
    std::string yellow_bg();
    
    /// Switch to red background
    std::string red_bg();
    
    /// Switch to green background
    std::string green_bg();
    
    /// Switch to blue background
    std::string blue_bg();
    
    /// Switch to default foreground
    std::string default_fg();
    
    /// Switch to bold foreground
    std::string bold();
    
    /// Change foreground to an 8-bit color
    std::string eight_bit_fg(short col); 
    
    /// Change background to an 8-bit color
    std::string eight_bit_bg(short col); 
    
    /// Change foreground to an 3-byte color
    std::string three_byte_fg(short red, short green, short blue);
    
    /// Change background to an 3-byte color
    std::string three_byte_bg(short red, short green, short blue);
    
    /// Switch to low-intensity foreground
    std::string lowint();
    
    /// Switch to underline background
    std::string underline();
    
    /// Switch to reversed background
    std::string reverse();
    
    /// Switch to alternate character set
    std::string alt_font();
    
    /// Switch from alternate to normal character set
    std::string normal_font();
    
    /// Summarize 8-bit colors
    std::string eight_bit_summ();
    
    /// Summarize 3-byte colors
    std::string three_byte_summ();
    
    /// Summarize 3-byte colors (long form)
    std::string three_byte_summ_long();
    
  };
  
  /** \brief Reformat the columns for output of width \c size 

      Given a string array \c in_cols of size \c nin, screenify()
      reformats the array into columns creating a new string array \c
      out_cols.
      
      For example, for an array of 10 strings 
      \verbatim
      test1
      test_of_string2
      test_of_string3
      test_of_string4
      test5
      test_of_string6
      test_of_string77
      test_of_string8
      test_of_string9
      test_of_string10
      \endverbatim
      screenify() will create an array of 3 new strings:
      \verbatim
      test1            test_of_string4  test_of_string77 test_of_string10
      test_of_string2  test5            test_of_string8
      test_of_string3  test_of_string6  test_of_string9
      \endverbatim
      
      If the value of \c max_size is less than the length of the
      longest input string (plus one for a space character), then the
      output strings may have a larger length than \c max_size.
  */
  template<class string_arr_t>
    void screenify(size_t nin, const string_arr_t &in_cols, 
		   std::vector<std::string> &out_cols,
		   size_t max_size=80) {

    if (nin==0) {
      O2SCL_ERR("No strings specified in screenify().",exc_efailed);
    }

    size_t i,j,lmax,itemp;
    std::vector<std::string> in_spaces(nin);

    terminal ter;
    
    // Determine size of largest string
    lmax=0;
    for(i=0;i<nin;i++) {
      if (lmax<ter.str_len(in_cols[i])) {
	lmax=ter.str_len(in_cols[i]);
      }
    }

    // Pad with spaces
    for(i=0;i<nin;i++) {
      itemp=ter.str_len(in_cols[i]);
      in_spaces[i]=in_cols[i];
      for(j=0;j<lmax+1-itemp;j++) {
	in_spaces[i]+=' ';
      }
    }

    // Determine number of rows and columns
    size_t row, col;
    col=max_size/(lmax+1);
    if (col==0) col=1;
    if (nin/col*col==nin) row=nin/col;
    else row=nin/col+1;

    // Create outc
    out_cols.reserve(row);
    for(i=0;i<row;i++) {
      out_cols.push_back("");
      for(j=0;j<col;j++) {
	if (i+j*row<nin) {
	  out_cols[i]+=in_spaces[i+j*row];
	}
      }
    }

    return;
  }

}

#endif

