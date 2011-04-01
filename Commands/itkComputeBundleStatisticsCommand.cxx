/*=========================================================================

  Program:   Tensor ToolKit - TTK
  Module:    $URL: https://scm.gforge.inria.fr/svn/ttk/trunk/Commands/itkComputeBundleStatisticsCommand.cxx $
  Language:  C++
  Date:      $Date: 2010-12-10 21:55:58 +0100 (ven., 10 déc. 2010) $
  Version:   $Revision: 122 $

  Copyright (c) INRIA 2010. All rights reserved.
  See LICENSE.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#include "itkComputeBundleStatisticsCommand.h"

#include <itkFiberBundleToScalarFunction.h>

#include <vtkPolyData.h>
#include <vtkPolyDataReader.h>

#include <iostream>
#include "GetPot.h"


namespace itk
{

  ComputeBundleStatisticsCommand::ComputeBundleStatisticsCommand()
  {
    m_ShortDescription = "Compute mean FA/ADC of a fiber bundle";
    m_LongDescription = "Usage:\n";
    m_LongDescription += "<-i input bundle>\n";
    m_LongDescription += "<-o output>\n\n";
    m_LongDescription += m_ShortDescription;
  }

  
  ComputeBundleStatisticsCommand::~ComputeBundleStatisticsCommand()
  {}
  

  int ComputeBundleStatisticsCommand::Execute (int narg, const char* arg[])
  {

    GetPot   cl(narg, const_cast<char**>(arg)); // argument parser
    if( cl.size() == 1 || cl.search(2, "--help", "-h") )
    {
      std::cout << this->GetLongDescription() << std::endl;
      return -1;
    }
    
    const char* file_in     = cl.follow ("",2,"-i","-I");
    const char* file_out    = cl.follow ("",2,"-o","-O");
    
    vtkPolyDataReader *reader = vtkPolyDataReader::New();
    reader->SetFileName (file_in);
    reader->Update();

    vtkPolyData *bundle = reader->GetOutput();
    
    itk::FiberBundleToScalarFunction::Pointer calculator = itk::FiberBundleToScalarFunction::New();
    calculator->SetInput (bundle);
    try
    {
        calculator->Compute();
    }
    catch (itk::ExceptionObject &e)
    {
        std::cerr << e;
        return EXIT_FAILURE;
    }

    std::cout << "Mean FA: " << calculator->GetMeanFA() << std::endl;
    std::cout << "Mean ADC: " << calculator->GetMeanADC() << std::endl;
    std::cout << "Mean Length: " << calculator->GetMeanFiberLength() << std::endl;

    reader->Delete();

    return 0;
  }
  
}
