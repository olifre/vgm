// $Id$
//
// Class MaterialFactory
// ------------------------
// The interface to material factory.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "G4Material.hh"
#include "G4Element.hh"

#include "ClhepVGM/Units.h"

#include "BaseVGM/common/utilities.h"

#include "Geant4GM/materials/MaterialFactory.h"
#include "Geant4GM/materials/ElementMap.h"
#include "Geant4GM/materials/Element.h"
#include "Geant4GM/materials/MaterialMap.h"
#include "Geant4GM/materials/Material.h"
#include "Geant4GM/materials/Medium.h"

//_____________________________________________________________________________
Geant4GM::MaterialFactory::MaterialFactory()
  : VGM::IMaterialFactory(),
    BaseVGM::VMaterialFactory("Geant4_GM_Material_Factory"),
    fVacuumElements()
{  
/// Standard default constructor
}

//_____________________________________________________________________________
Geant4GM::MaterialFactory::MaterialFactory(const MaterialFactory& rhs)
  : VGM::IMaterialFactory(rhs),
    BaseVGM::VMaterialFactory(rhs),
    fVacuumElements(rhs.fVacuumElements)
    
{  
/// Protected copy constructor
}

//_____________________________________________________________________________
Geant4GM::MaterialFactory::~MaterialFactory() {
//
  
  // delete map singletons

  delete Geant4GM::ElementMap::Instance();
  delete Geant4GM::MaterialMap::Instance();
              // There is inconsistence in using the singleton maps
	      // via a factory which is not a singleton
	      // TO DO: to be improved later

}

//
// private functions
//

//_____________________________________________________________________________
void Geant4GM::MaterialFactory::ImportElement(G4Element* element)
{
/// Import the specified G4 element.

  if (Debug()>0) {
    BaseVGM::DebugInfo();
    std::cout << "Importing element: "; 
    if (Debug()>1) std::cout << element;
    std::cout << std::endl;
    BaseVGM::DebugInfo();
    std::cout << *element << std::endl;
  }	      

  VGM::IElement* vgmElement = new Geant4GM::Element(element);
  ElementStore().push_back(vgmElement);
}

//_____________________________________________________________________________
void Geant4GM::MaterialFactory::ImportMaterial(G4Material* material)
{
/// Import the specified G4 material.

  if (Debug()>0) {
    BaseVGM::DebugInfo();
    std::cout << "Importing material: "; 
    if (Debug()>1) std::cout << material;
    std::cout << std::endl;
    BaseVGM::DebugInfo();
    std::cout << *material << std::endl;
  }	      

  VGM::IMaterial* vgmMaterial = new Geant4GM::Material(material);
  MaterialStore().push_back(vgmMaterial);
}

//
// public functions
//

//_____________________________________________________________________________
VGM::IElement* 
Geant4GM::MaterialFactory::CreateElement(
                                  const std::string& name,      
                                  const std::string& symbol,      
                                  double z, double a)
{
// Create element if such element with specified properties does not
// yet exist

  G4Element* g4Element = G4Element::GetElement(name, false);
  
  VGM::IElement* vgmElement;
  if (g4Element)
    vgmElement = Geant4GM::ElementMap::Instance()->GetElement(g4Element);
  else  {
    if ( z < 1.0) {
      // special case (vacuum)
      // in Geant4 vacuum has element with z = 1.0, a = 1.01
      vgmElement 
       = new Geant4GM::Element(name, symbol, z = 1.0, 
                               a = 1.01*ClhepVGM::Units::AtomicWeight(g/mole));

      fVacuumElements.insert(vgmElement);                               
    }
    else  {
      vgmElement = new Geant4GM::Element(name, symbol, z, a);
    }  

    ElementStore().push_back(vgmElement);
  }    
  return vgmElement; 
}			       

//_____________________________________________________________________________
VGM::IMaterial* 
Geant4GM::MaterialFactory::CreateMaterial(     
                                 const std::string& name,      
                                 double density, 
		                 VGM::IElement* element,
		                 double /*radlen*/, double /*intlen*/)
{
// Create material 

  bool isVacuum = false;
  if ( fVacuumElements.find(element) != fVacuumElements.end() ) isVacuum = true;

  VGM::IMaterial* vgmMaterial 
    = new Geant4GM::Material(name, density, element, isVacuum);
		      
  MaterialStore().push_back(vgmMaterial);
  return vgmMaterial; 
}			       

//_____________________________________________________________________________
VGM::IMaterial* 
Geant4GM::MaterialFactory::CreateMaterial(     
                                 const std::string& name,      
                                 double density, 
                                 VGM::IElement* element,
                                 double /*radlen*/, double /*intlen*/,
                                 VGM::MaterialState state, 
                                 double temperature, double pressure)
{
// Create material 

  bool isVacuum = false;
  if ( fVacuumElements.find(element) != fVacuumElements.end() ) isVacuum = true;

  VGM::IMaterial* vgmMaterial 
    = new Geant4GM::Material(name, density, element, 
                             state, temperature, pressure, isVacuum);
		      
  MaterialStore().push_back(vgmMaterial);
  return vgmMaterial; 
}			       

//_____________________________________________________________________________
VGM::IMaterial* 
Geant4GM::MaterialFactory::CreateMaterial(
                                 const std::string& name, 
                                 double density,
			         const VGM::ElementVector& elements,
                                 const VGM::MassFractionVector& fractions)
{
// Create material 

  VGM::IMaterial* vgmMaterial
    = new Geant4GM::Material(name, density, elements, fractions);
		      
  MaterialStore().push_back(vgmMaterial);
  return vgmMaterial; 
}			       

//_____________________________________________________________________________
VGM::IMaterial* 
Geant4GM::MaterialFactory::CreateMaterial(
                                 const std::string& name, 
                                 double density,
			         const VGM::ElementVector& elements,
                                 const VGM::MassFractionVector& fractions,
                                 VGM::MaterialState state,
                                 double temperature, double pressure)
{
// Create material 

  VGM::IMaterial* vgmMaterial
    = new Geant4GM::Material(name, density, elements, fractions,
                             state, temperature, pressure);
		      
  MaterialStore().push_back(vgmMaterial);
  return vgmMaterial; 
}			       

//_____________________________________________________________________________
VGM::IMedium*  
Geant4GM::MaterialFactory::CreateMedium(const std::string& name,
                                 int mediumId,
	  		         VGM::IMaterial* material,
			         int nofParameters,
			         double* parameters)
{
// Create medium
 				    
  VGM::IMedium* vgmMedium
    = new Geant4GM::Medium(name, mediumId, material, nofParameters, parameters);
		      
  MediumStore().push_back(vgmMedium);
  return vgmMedium; 
}			       

//_____________________________________________________________________________
bool Geant4GM::MaterialFactory::Import()
{
/// Import all elements, materials from G4MaterialTable

  const G4ElementTable* elementTable = G4Element::GetElementTable();
  
  for (G4int i=0; i<G4int(elementTable->size()); i++) {
    G4Element* element = (*elementTable)[i];
    ImportElement(element);
  }  

  const G4MaterialTable* materialTable = G4Material::GetMaterialTable();
  
  for (G4int j=0; j<G4int(materialTable->size()); j++) {
    G4Material* material = (*materialTable)[j];
    ImportMaterial(material);
  }  

  return true;
}			      


