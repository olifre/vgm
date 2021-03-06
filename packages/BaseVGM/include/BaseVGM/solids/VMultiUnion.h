// $Id$

// -----------------------------------------------------------------------
// The BaseVGM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

/// \ingroup BaseVGM_solids
//
/// \class BaseVGM::VMultiUnion
///
/// The ABC for Boolean solids.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef BASE_VGM_V_MULTI_UNION_H
#define BASE_VGM_V_MULTI_UNION_H

#include "VGM/solids/IMultiUnion.h"

#include <iostream>

namespace BaseVGM {

class VMultiUnion : public virtual VGM::IMultiUnion
{
 public:
  VMultiUnion();
  virtual ~VMultiUnion();

  // methods
  virtual VGM::SolidType Type() const;

  // streaming
  virtual std::ostream& Put(std::ostream& out) const;
};

} // namespace BaseVGM

// inline functions

inline VGM::SolidType BaseVGM::VMultiUnion::Type() const
{
  return VGM::kMultiUnion;
}

#endif // BASE_VGM_V_MULTI_UNION_H
