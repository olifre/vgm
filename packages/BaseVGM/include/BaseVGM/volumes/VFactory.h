// $Id$
// Category: basic
//
// Class VFactory
// ---------------
// The abstract base class to geometry factory.
// It owns the solids and volumes stores and
// implements the export to other factory. 
//
// Author: Ivana Hrivnacova; IPN Orsay

#ifndef BASE_VGM_V_FACTORY_H
#define BASE_VGM_V_FACTORY_H

#include <map>

#include "VGM/volumes/IFactory.h"
#include "VGM/solids/ISolid.h"
#include "VGM/solids/IBooleanSolid.h"

namespace BaseVGM {

  class VGM::IVolume;
  class VGM::IPlacement;
  class VGM::IMaterialFactory;

  class VFactory : public virtual VGM::IFactory
  {
    public:
      VFactory(const std::string& name, 
                VGM::IMaterialFactory* materialFactory);
      virtual ~VFactory();
    
      //
      // methods
      //
      
      virtual std::string Name() const;
      virtual const VGM::SolidStore&   Solids() const;			       
      virtual const VGM::VolumeStore&  Volumes() const;			       
      virtual VGM::IMaterialFactory*   MaterialFactory() const;

      virtual bool  Export(VGM::IFactory* factory) const;			       

      virtual void  PrintSolids() const;			       
      virtual void  PrintVolumes() const;	

      virtual void  SetDebug (int debug);			       
      virtual int   Debug() const;

    protected:
      VFactory() : VGM::IFactory() {}
      VFactory(const VFactory& rhs) : VGM::IFactory(rhs) {}

      virtual VGM::SolidStore&   SolidStore();			       
      virtual VGM::VolumeStore&  VolumeStore();

    private:
      // types
      typedef std::map<VGM::IVolume*, VGM::IVolume*>  VolumeMap;

      // methods
      VGM::ISolid*     ExportSolid(
                             VGM::ISolid* solid, 
                             VGM::IFactory* factory) const;
      VGM::ISolid*     ExportBooleanSolid(
                             VGM::IBooleanSolid* solid,
                             VGM::IFactory* factory) const;
      VolumeMap*       ExportVolumeStore(VGM::IFactory* factory) const;

      VGM::IPlacement* ExportSimplePlacement(
                             VGM::IPlacement* placement, 
                             VGM::IFactory* factory, 
			     VolumeMap* volumeMap) const;
      VGM::IPlacement* ExportMultiplePlacement(
                             VGM::IPlacement* placement, 
                             VGM::IFactory* factory, 
			     VolumeMap* volumeMap) const;
      void             ExportPlacements(
                             VGM::IFactory* factory, 
			     VolumeMap* map) const;
  
      VGM::Transform   Identity() const;

      // data members
      int                     fDebug;
      std::string             fName;
      VGM::SolidStore         fSolids;
      VGM::VolumeStore        fVolumes;
      VGM::IMaterialFactory*  fMaterialFactory;
  };
  
}  

// inline functions

inline std::string 
BaseVGM::VFactory::Name() const
{ return fName; }

inline const VGM::SolidStore& 
BaseVGM::VFactory::Solids() const
{ return fSolids; }
			       
inline const VGM::VolumeStore& 
BaseVGM::VFactory::Volumes() const
{ return fVolumes; }

inline VGM::IMaterialFactory*  
BaseVGM::VFactory::MaterialFactory() const
{ return fMaterialFactory; }

inline VGM::SolidStore& 
BaseVGM::VFactory::SolidStore()
{ return fSolids; }
			       
inline VGM::VolumeStore& 
BaseVGM::VFactory::VolumeStore()
{ return fVolumes; }

inline int BaseVGM::VFactory::Debug() const
{ return fDebug; }

#endif //BASE_VGM_V_FACTORY_H
