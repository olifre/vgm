// $Id$
//
// Class Units
// ------------------
// Conversion from Root physical units to VGM units.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include <iostream>

#include "RootGM/common/Units.h"

//
// static const data members
//

const double RootGM::Units::fgkLength       = 10.;     // cm 
const double RootGM::Units::fgkAngle        = 1.;      // deg
const double RootGM::Units::fgkMassDensity  = 1.;      // g/cm3;
const double RootGM::Units::fgkAtomicWeight = 1.;      // g/mole;

//_____________________________________________________________________________
RootGM::Units::Units() 
{
/// Protected default constructor
}
  
//_____________________________________________________________________________
RootGM::Units::~Units() {
//
}

//
// public functions
//

//_____________________________________________________________________________
double RootGM::Units::AxisUnit(VGM::Axis axis)
{
  if (axis == VGM::kXAxis || 
      axis == VGM::kYAxis || 
      axis == VGM::kZAxis ||
      axis == VGM::kRho   || 
      axis == VGM::kRadial3D) { 
    
    return Length();
  }  

  if (axis == VGM::kPhi || 
      axis == VGM::kSphTheta) {
    return Angle();
  }  

  // axis == kUndefined  
  std::cerr << "    RootGM::Units::AxisUnit:"       << std::endl; 
  std::cerr << "    Undefined axis"                 << std::endl;
  std::cerr << "*** Error: Aborting execution  ***" << std::endl; 
  exit(1);
}