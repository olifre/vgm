// $Id$
/// \ingroup VGM_solids
///
/// \class VGM::IBooleanSolid
/// 
/// The VGM interface to Boolean solids.
///
/// Author: Ivana Hrivnacova; IPN Orsay

#ifndef VGM_I_BOOLEAN_SOLID_H
#define VGM_I_BOOLEAN_SOLID_H

#include <iostream>

#include "VGM/common/Transform.h"
#include "VGM/solids/ISolid.h"

namespace VGM {

  enum BooleanType {
    kIntersection,
    kSubtraction,
    kUnion,
    kUnknownBoolean
  };
  
  std::string BooleanTypeName(BooleanType typeId);

  class IBooleanSolid : public virtual ISolid
  {
    public:
      virtual ~IBooleanSolid() {}

      // methods
      
      virtual SolidType    Type() const = 0;
      virtual std::string  Name() const = 0;

			    /// 
                            /// Return the Boolean type of this solid
      virtual BooleanType  BoolType() const = 0;
			    /// 
                            /// Return the first constituent solid
      virtual ISolid*      ConstituentSolidA() const = 0;
			    /// 
                            /// Return the second constituent solid
      virtual ISolid*      ConstituentSolidB() const = 0;
			    /// 
                            /// Return the 3D displacement of the second 
			    /// constituent solid with respect to the first one
      virtual Transform    Displacement() const = 0;      

      // streaming
      virtual std::ostream& Put(std::ostream& out) const = 0;
  };

}  

std::ostream& operator << (std::ostream& out, const VGM::IBooleanSolid& box);

#endif //VGM_I_BOOLEAN_SOLID_H