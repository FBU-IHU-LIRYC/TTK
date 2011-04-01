/*=========================================================================

  Program:   Tensor ToolKit - TTK
  Module:    $URL$
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) INRIA 2010. All rights reserved.
  See LICENSE.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef _itk_Fibers_h_
#define _itk_Fibers_h_

#include <itkPoint.h>
#include <itkTensor.h>
#include <ostream>

namespace itk
{
  /*! \class Fiber
    \ingroup TensorToolKit
    Convenient way to handle dti fiber data.
   */

  template <  class T , unsigned int NDimension, class TTensorCoord = float >
    class Fiber
  {
  public:
    typedef T                                ScalarType;
    typedef Fiber                            Self;
    typedef Point<ScalarType, NDimension>    PointType;
    typedef Tensor<TTensorCoord, NDimension> TensorType;
     
    struct FiberPoint
    {
       PointType  Point;
       TensorType Tensor;
       FiberPoint(): Tensor(0.0) 
       {
         for(unsigned int i=0; i<NDimension; i++)
           Point[i] = 0.0;
       };
    };
     
    typedef std::vector<FiberPoint> FiberPointListType;
     

    itkStaticConstMacro (Dimension, unsigned int, NDimension);
    
    
    /** add a point to the tail of the fiber. */
    void AddPoint ( const FiberPoint & );

    /** set the list of points */
    void SetPointList ( const FiberPointListType &l)
    { m_FiberPointList = l; }
    
    /** get the list of points */
    FiberPointListType GetPointList (void) const
    { return m_FiberPointList; }
    
    /** return the ith point (if it exists)*/
    FiberPoint GetPoint (const int) const;

    /** merge two fibers */
    void MergeWith (const Self& );

    /** return the geodesic length of the fiber*/
    double GetLength (void) const;

    /** Get the Euclidean length*/
    double GetEuclideanLength (void) const;

    /** return the number of points */
    unsigned int GetNumberOfPoints (void) const
    { return m_FiberPointList.size(); }

    /** Empties the point list */
    void Clear (void)
    { m_FiberPointList.clear(); }
    
    /** Integrates the FA along the fiber */
    double GetMeanFA (void) const;

    /** Integrates the ADC along the fiber */
    double GetMeanADC (void) const;

    Fiber(){};
    ~Fiber(){};
    Fiber (const Self& f)
    {
      m_FiberPointList  = f.GetPointList();
    }
    Self& operator=(const Self& f);

    
    
  private:
    FiberPointListType  m_FiberPointList;

  };


  template <class T, unsigned int NDimension>
    std::ostream & operator<<(std::ostream &os, const Fiber<T,NDimension> &f)
  {
    for( unsigned int i=0; i<f.GetNumberOfPoints(); i++)
      os << f.GetPointList()[i].Point << " " << f.GetPointList()[i].Tensor << std::endl;

    return os;
  }
  

} // end of namespace itk


#ifndef ITK_MANUAL_INSTANTIATION
#include "itkFiber.txx"
#endif

#endif
