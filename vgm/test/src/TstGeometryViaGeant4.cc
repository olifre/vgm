// $Id$
//
// Class TstGeometryViaGeant4
// ---------------
// The test for solids construction
//
// Author: Ivana Hrivnacova; IPN Orsay

#include <iomanip>

#include "G4Material.hh"
#include "G4Element.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4ReflectionFactory.hh"
#include "G4IntersectionSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4UnionSolid.hh"
#include "G4VSolid.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Para.hh"
#include "G4Polycone.hh"
#include "G4Polyhedra.hh"
#include "G4Sphere.hh"
#include "G4Torus.hh"
#include "G4Trap.hh"
#include "G4Trd.hh"
#include "G4Tubs.hh"
#include "G4PVPlacement.hh"
#include "G4PVDivision.hh"
#include "G4RotationMatrix.hh"
#include "globals.hh"

#include "TstGeometryViaGeant4.hh"
#include "TstParameters.hh"

//_____________________________________________________________________________
TstGeometryViaGeant4::TstGeometryViaGeant4()
  : TstVGeometry(),
    fBasicMaterial(0)
{
//
}  

//_____________________________________________________________________________
TstGeometryViaGeant4::~TstGeometryViaGeant4()
{
}

//
// private methods
// 

//_____________________________________________________________________________
G4LogicalVolume* TstGeometryViaGeant4::CreateWorld()
{
// Create world volume
// ---
  
  // Get material from G4
  if (!fBasicMaterial) {
    fBasicMaterial = G4Material::GetMaterial("Basic");
    G4cout << "Basic material: " << fBasicMaterial << G4endl;
  }  

  G4double wSize = TstParameters::WorldLength();
  G4VSolid* worldS
    = new G4Box("worldS", wSize, wSize, wSize);

  return new G4LogicalVolume(worldS, fBasicMaterial, "worldV");
}    

//_____________________________________________________________________________
G4LogicalVolume* TstGeometryViaGeant4::CreateBox()
{
  G4VSolid* boxS
    = new G4Box("boxS", 20.*cm, 60.*cm, 50.*cm);
  
  return new G4LogicalVolume(boxS, fBasicMaterial, "boxV");
}  


//_____________________________________________________________________________
G4LogicalVolume* TstGeometryViaGeant4::CreateCons(G4double sphi, G4double dphi)
{
  G4VSolid* consS
    = new G4Cons("consS", 10.*cm, 40.*cm, 20.*cm, 60.*cm, 50*cm,
                 sphi, dphi);
  
  return new G4LogicalVolume(consS, fBasicMaterial, "consV");
}

//_____________________________________________________________________________
G4LogicalVolume* TstGeometryViaGeant4::CreatePara()
{
  G4VSolid* paraS
    = new G4Para("paraS", 40.*cm, 60.*cm, 50.*cm, 
                  30.*deg, 30.*deg, 30.*deg);

  return new G4LogicalVolume(paraS, fBasicMaterial, "paraV");
}  

//_____________________________________________________________________________
G4LogicalVolume* 
TstGeometryViaGeant4::CreatePolycone(G4double sphi, G4double dphi)
{
  // Define parameters

  G4int nofPlanes = 3;
  G4double z[3];
  G4double rin[3];
  G4double rout[3];

  z[0] = -50.*cm;
  rin[0] = 10.*cm;
  rout[0] = 50.*cm;
  
  z[1] = 10.*cm;
  rin[1] = 20.*cm;
  rout[1] = 30.*cm;
  
  z[2] = 40.*cm;
  rin[2] = 30.*cm;
  rout[2] = 60.*cm;
  
  G4VSolid* pconeS
    = new G4Polycone("pconeS", sphi, dphi, nofPlanes, z, rin, rout);
  
  return new G4LogicalVolume(pconeS, fBasicMaterial, "pconeV");
}  

//_____________________________________________________________________________
G4LogicalVolume* TstGeometryViaGeant4::CreatePolyhedra(G4double sphi, G4double dphi)
{
  // Define parameters

  G4int nofSides = 4;
  G4int nofPlanes = 3;
  G4double z[3];
  G4double rin[3];
  G4double rout[3];

  z[0] = -50.*cm;
  rin[0] = 10.*cm;
  rout[0] = 40.*cm;
  
  z[1] = 10.*cm;
  rin[1] = 20.*cm;
  rout[1] = 20.*cm;
  
  z[2] = 40.*cm;
  rin[2] = 30.*cm;
  rout[2] = 50.*cm;
  

  if (sphi != 0.*deg || dphi != 360.*deg) {
    std::cerr << "TstGeometryViaGeant4::CreatePolyhedra: " << std::endl
              << "   The sphi, dphi parameteres were ignored" << std::endl
	      << "   (to avoid G4Exception from G4Polyhedra.) " << std::endl;  
  }	      

  //G4VSolid* phedraS
  //  = new G4Polyhedra("phedraS", sphi, dphi, 
  //                     nofSides, nofPlanes, z, rin, rout);
  G4VSolid* phedraS
    = new G4Polyhedra("phedraS", 0., 360.*deg, 
                       nofSides, nofPlanes, z, rin, rout);

  return new G4LogicalVolume(phedraS, fBasicMaterial, "phedraV");
}  

//_____________________________________________________________________________
G4LogicalVolume* 
TstGeometryViaGeant4::CreateSphere(G4double sphi, G4double dphi)
{
  G4VSolid* sphereS1
    = new G4Sphere("sphereS", 20.*cm, 60.*cm,
                    sphi, dphi, sphi/2., dphi/2.); 
			    
  return new G4LogicalVolume(sphereS1, fBasicMaterial, "sphereV1");
}  

//_____________________________________________________________________________
G4LogicalVolume* 
TstGeometryViaGeant4::CreateTorus(G4double sphi, G4double dphi)
{
  G4VSolid* torusS
    = new G4Torus("torusS", 20.*cm, 30.*cm, 40.*cm,
                   sphi, dphi);
			    
  return new G4LogicalVolume(torusS, fBasicMaterial, "torusV");  
}  

//_____________________________________________________________________________
G4LogicalVolume* TstGeometryViaGeant4::CreateTrap()
{
  G4VSolid* trapS
    = new G4Trap("trapS", 30.*cm, 25.*deg, 35.*deg,
		  20.*cm, 10.*cm, 15.*cm, 0.*deg,
		  20.*cm, 10.*cm, 15.*cm, 0.*deg);

  return new G4LogicalVolume(trapS, fBasicMaterial, "trapV");
}

//_____________________________________________________________________________
G4LogicalVolume* TstGeometryViaGeant4::CreateTrd()
{
  G4VSolid* trdS
    = new G4Trd("trdS", 20.*cm, 30*cm, 40.*cm, 50.*cm, 50.*cm);

  return new G4LogicalVolume(trdS, fBasicMaterial, "trdV");
}  

//_____________________________________________________________________________
G4LogicalVolume* TstGeometryViaGeant4::CreateTubs(G4double sphi, G4double dphi)
{
  G4VSolid* tubsS
    = new G4Tubs("tubsS", 20.*cm, 40*cm, 50.*cm, sphi, dphi);

  return new G4LogicalVolume(tubsS, fBasicMaterial, "tubsV");
}  
 
//_____________________________________________________________________________
G4LogicalVolume* 
TstGeometryViaGeant4::PlaceSolids(G4LogicalVolume* mother,
                                  G4bool fullPhi, G4bool reflect, G4double zpos)
{
  G4double sphi =   0.*deg;
  G4double dphi = 360.*deg;
  if (!fullPhi) {
    sphi = 45.*deg;
    dphi = 90.*deg;
  }  
 
  G4int counter = 0;
  G4double wSize = TstParameters::WorldLength();
  G4double dz = wSize/6.;
  G4double dy = wSize/4.;
  
  HepReflectZ3D reflect3D;
 
  // Box
  //
  G4LogicalVolume* boxV = CreateBox();
  new G4PVPlacement(
               HepTranslate3D(-wSize + (counter)*dz,  -dy, zpos),
	       boxV, "box", mother, false, 0);

  if (reflect) {
    G4ReflectionFactory::Instance()
      ->Place(HepTranslate3D(-wSize + (counter)*dz,  -dy, -zpos) * reflect3D,
	      "box", boxV, mother, false, 0);
  }	      

  // Cons 
  //
  G4LogicalVolume* consV = CreateCons(sphi, dphi);
  new G4PVPlacement(
               HepTranslate3D(-wSize + (counter)*dz, dy, zpos),
	       consV, "cons", mother, false, 0);

  if (reflect) {
    G4ReflectionFactory::Instance()
      ->Place(HepTranslate3D(-wSize + (counter)*dz, dy, -zpos) * reflect3D,
	      "cons", consV, mother, false, 0);
  }	      

  // Para
  //
  G4LogicalVolume* paraV = CreatePara();
  new G4PVPlacement( 
               HepTranslate3D(-wSize + (++counter)*dz,  -dy, zpos),
	       paraV, "para", mother, false, 0);

  if (reflect) {
    G4ReflectionFactory::Instance()
      ->Place(HepTranslate3D(-wSize + (counter)*dz,  -dy, -zpos) * reflect3D,
	      "para", paraV, mother, false, 0);
  }	      
  
  // Polycone
  //
  G4LogicalVolume* pconeV = CreatePolycone(sphi, dphi);
  new G4PVPlacement( 
               HepTranslate3D(-wSize + (counter)*dz, dy, zpos),
	       pconeV, "pcone", mother, false, 0);

  if (reflect) {
    G4ReflectionFactory::Instance()
      ->Place(HepTranslate3D(-wSize + (counter)*dz, dy, -zpos) * reflect3D,
	      "pcone", pconeV, mother, false, 0);
  }	      

  // Polyhedra
  //
  G4LogicalVolume* phedraV = CreatePolyhedra(sphi, dphi);
  new G4PVPlacement( 
               HepTranslate3D(-wSize + (++counter)*dz,  -dy, zpos),
	       phedraV, "phedra", mother, false, 0);

  if (reflect) {
    G4ReflectionFactory::Instance()
      ->Place(HepTranslate3D(-wSize + (counter)*dz,  -dy, -zpos) * reflect3D,
	      "phedra", phedraV, mother, false, 0);
  }	      

  // Sphere 
  //
  G4LogicalVolume* sphereV = CreateSphere(sphi, dphi);
  new G4PVPlacement(
               HepTranslate3D(-wSize + (counter)*dz, dy, zpos),
	       sphereV, "sphere", mother, false, 0);
	       
  if (reflect) {
    G4ReflectionFactory::Instance()
      ->Place(HepTranslate3D(-wSize + (counter)*dz, dy, -zpos) * reflect3D,
	      "sphere", sphereV, mother, false, 0);
  }	      

  // Torus
  //
  G4LogicalVolume* torusV = CreateTorus(sphi, dphi);
  new G4PVPlacement( 
               HepTranslate3D(-wSize + (++counter)*dz,  -dy, zpos),
	       torusV, "torus", mother, false, 0);

  if (reflect) {
    G4ReflectionFactory::Instance()
      ->Place(HepTranslate3D(-wSize + (counter)*dz,  -dy, -zpos) * reflect3D,
	      "torus", torusV, mother, false, 0);
  }	      

  // Trap 
  //
  G4LogicalVolume* trapV = CreateTrap();
  new G4PVPlacement( 
               HepTranslate3D(-wSize + (counter)*dz, dy, zpos),
	       trapV, "trap", mother, false, 0);

  if (reflect) {
    G4ReflectionFactory::Instance()
      ->Place(HepTranslate3D(-wSize + (counter)*dz, dy, -zpos) * reflect3D,
	      "trap", trapV, mother, false, 0);
  }	      

  // Trd
  //
  G4LogicalVolume* trdV = CreateTrd();
  new G4PVPlacement( 
               HepTranslate3D(-wSize + (++counter)*dz,  -dy, zpos),
	       trdV, "trd", mother, false, 0);

  if (reflect) {
    G4ReflectionFactory::Instance()
      ->Place(HepTranslate3D(-wSize + (counter)*dz,  -dy, -zpos) * reflect3D,
	      "trd", trdV, mother, false, 0);
  }	      
 
  // Trd
  //
  G4LogicalVolume* tubsV = CreateTubs(sphi, dphi);
  new G4PVPlacement(
               HepTranslate3D(-wSize + (counter)*dz, dy, zpos),
	       tubsV, "tubs", mother, false, 0);

  if (reflect) {
    G4ReflectionFactory::Instance()
      ->Place(HepTranslate3D(-wSize + (counter)*dz, dy, -zpos) * reflect3D,
	      "tubs", tubsV, mother, false, 0);
  }	      

  return mother;
 }

//
// public methods
// 


//_____________________________________________________________________________
void  TstGeometryViaGeant4::DefineMaterials()
{
  // simple material (Al)
  //
  G4double z, a, density, fractionmass; 
  new G4Material("Basic", z=13., a=26.98*g/mole, density=2.700*g/cm3);

  // compound/mixture material
  //
  G4Element* N 
    = new G4Element("Nitrogen", "N" , z= 7., a=14.01*g/mole);
  G4Element* O  
    = new G4Element("Oxygen"  , "O" , z= 8., a=16.00*g/mole);

  density = 1.290*mg/cm3;
  G4Material* material2 = new G4Material("Air", density, 2);
  material2->AddElement(N, fractionmass=0.7);
  material2->AddElement(O, fractionmass=0.3);

  // vacuum
  //
  new G4Material("Vacuum", 
                 z=1., a=1.01*g/mole,density= universe_mean_density,
                 kStateGas, 3.e-18*pascal, 2.73*kelvin);
}

//_____________________________________________________________________________
void* TstGeometryViaGeant4::TestSolids(G4bool fullPhi)
{
  G4LogicalVolume* worldV = CreateWorld();
  G4VPhysicalVolume* world
    = new G4PVPlacement(0, Hep3Vector(), worldV, "world", 0, false, 0); 
  
  PlaceSolids(worldV, fullPhi, false, 0.);

  return (void*) world;
 }

//_____________________________________________________________________________
void* TstGeometryViaGeant4::TestPlacements()
{
  // World
  //
  G4LogicalVolume* worldV = CreateWorld();
  G4VPhysicalVolume* world
    = new G4PVPlacement(0, Hep3Vector(), worldV, "world", 0, false, 0); 
    
  // Big box A
  //
  G4VSolid * boxA
    = new G4Box("boxA", 20.*cm, 60.*cm, 50.*cm);
  G4LogicalVolume* volA
    = new G4LogicalVolume(boxA, fBasicMaterial, "volA");
  
  // Thick layer B (in A)
  //
  G4VSolid * boxB
    = new G4Box("boxB", 20.*cm, 10.*cm, 50.*cm);
  G4LogicalVolume * volB
    = new G4LogicalVolume(boxB, fBasicMaterial, "volB");

  // Thin layer C (in B)
  //
  G4VSolid * boxC
    = new G4Box("boxC", 20.*cm, 0.2*cm, 50.*cm);
  G4LogicalVolume * volC
    = new G4LogicalVolume(boxC, fBasicMaterial, "volC");

  // Place layers C
  //
  new G4PVPlacement(0, Hep3Vector(0.,  9.8*cm, 0.),
                    volC, "layerC", volB, false, 0);
  new G4PVPlacement( 0, Hep3Vector(0., -9.8*cm, 0.),
                    volC, "layerC", volB, false, 1);

  // Place layers B   
  //
  //new G4PVDivision("layerB", volB, volA, kYAxis, 6, 20.*cm, 0.);
             // division in the whole mother
  
  new G4PVDivision("layerB", volB, volA, kYAxis, 3, 20.*cm, 60.*cm);
             // division with offeset

  // Placements of A in a circle
  //
  for (G4int i=0; i<24; i++) {
   
     G4double x0 = 5. *m;
     G4double y0 = 0. *m;
     G4double dphi = 15.*deg;

     G4double phi = dphi*(i+1);
     G4double x = x0*cos(phi);
     G4double z = x0*sin(phi);

     HepRotation* rot = new HepRotation();
     rot->rotateY(phi);
     
     new G4PVPlacement(rot, Hep3Vector(x, y0, z),
                       volA, "layerA", worldV, false, i);
   }
   
  return (void*) world;
}

//_____________________________________________________________________________
void* TstGeometryViaGeant4::TestReflections(G4bool fullPhi)
{

  // World
  //
  G4LogicalVolume* worldV = CreateWorld();
  G4VPhysicalVolume* world
    = new G4PVPlacement(0, Hep3Vector(), worldV, "world", 0, false, 0); 
  
  PlaceSolids(worldV, fullPhi, true, 1.*m);

  return (void*) world;
}

//_____________________________________________________________________________
void* TstGeometryViaGeant4::TestBooleanSolids1()
{
// Only translation in solid displacement

  G4double wSize = TstParameters::WorldLength();

  // World
  //
  G4LogicalVolume* worldV = CreateWorld();
  G4VPhysicalVolume* world
    = new G4PVPlacement(0, Hep3Vector(), worldV, "world", 0, false, 0); 
  
  // Create solids
  G4VSolid* solid1 
    = new G4Box("boxS", 50.*cm, 50.*cm, 50.*cm);

  G4VSolid* solid2 
    = new G4Cons("consS", 10.*cm, 30.*cm, 20.*cm, 40.*cm, 100.*cm, 0., 360.*deg) ;
 
  // Simple solids placed for a control
  //
  G4LogicalVolume* volume1
    = new G4LogicalVolume(solid1, fBasicMaterial, "volume1");
  new G4PVPlacement(0, Hep3Vector(-wSize/8., 0., -2.*m),
		    volume1, "solid1", worldV, false, 0);

  G4LogicalVolume* volume2
    = new G4LogicalVolume(solid2, fBasicMaterial, "volume2");
  new G4PVPlacement(0, Hep3Vector( wSize/8., 0., -2.*m),
                    volume2, "solid2", worldV, false, 0);


  // Intersection
  //
  G4VSolid* intersectionS
    = new G4IntersectionSolid(
                  "solid1Isolid2S", solid1, solid2, 0, Hep3Vector(20.*cm, 0., 0.)); 
  G4LogicalVolume* intersectionV
    = new G4LogicalVolume(intersectionS, fBasicMaterial, "solid1Isolid2V");

  new G4PVPlacement(0, Hep3Vector(-wSize/4., 0., 2.*m),
                    intersectionV, "solid1Isolid2", worldV, false, 0); 
  
  // Subtraction
  //
  G4VSolid* subtractionS
    = new G4SubtractionSolid(
                  "solid1Ssolid2S", solid1, solid2, 0, Hep3Vector(20.*cm, 0., 0.)); 
  G4LogicalVolume* subtractionV
    = new G4LogicalVolume(subtractionS, fBasicMaterial, "solid1Ssolid2V");

  new G4PVPlacement(0, Hep3Vector(0., 0., 2.*m), 
                   subtractionV, "solid1Ssolid2", worldV, false, 0);
  
  // Union
  //
  G4VSolid* unionS
    = new G4UnionSolid(
                  "solid1Usolid2S", solid1, solid2, 0, Hep3Vector(20.*cm, 0., 0.)); 
  G4LogicalVolume* unionV
    = new G4LogicalVolume(unionS, fBasicMaterial, "solid1Usolid2V");

  new G4PVPlacement(0, Hep3Vector( wSize/4., 0., 2.*m),
                    unionV, "solid1Usolid2", worldV, false, 0);
  
  return (void*) world;
}


//_____________________________________________________________________________
void* TstGeometryViaGeant4::TestBooleanSolids2()
{
// Translation + rotation in solid displacement

  G4double wSize = TstParameters::WorldLength();

  // World
  //
  G4LogicalVolume* worldV = CreateWorld();
  G4VPhysicalVolume* world
    = new G4PVPlacement(0, Hep3Vector(), worldV, "world", 0, false, 0); 
  
  // Create solids
  G4VSolid* solid1 
    = new G4Box("boxS", 50.*cm, 50.*cm, 50.*cm);

  G4VSolid* solid2 
    = new G4Cons("consS", 10.*cm, 30.*cm, 20.*cm, 40.*cm, 100.*cm, 0., 360.*deg) ;
 
  // Simple solids placed for a control
  //
  G4LogicalVolume* volume1
    = new G4LogicalVolume(solid1, fBasicMaterial, "volume1");
  new G4PVPlacement(0, Hep3Vector(-wSize/8., 0., -2.*m),
		    volume1, "solid1", worldV, false, 0);

  G4LogicalVolume* volume2
    = new G4LogicalVolume(solid2, fBasicMaterial, "volume2");
  new G4PVPlacement(0, Hep3Vector( wSize/8., 0., -2.*m),
                    volume2, "solid2", worldV, false, 0);


  // Define displacement transformations
  //
 
   // Rotate solid1  
  HepRotation* rot1 = new HepRotation();
  rot1->rotateY(-45.*deg);

  // Rotate + translate solid2
  //
  HepRotation* rot2 = new HepRotation();
  rot2->rotateX(-30.*deg);
  rot2->rotateY(45.*deg); 
       // apply inverse rotation to solid1 rotation
       // as this one will be applied with placement
  Hep3Vector  tr2 = Hep3Vector(20.*cm, 0., 0.);
     
  
  // Intersection
  //
  G4VSolid* intersectionS
    = new G4IntersectionSolid(
                  "solid1Isolid2S", solid1, solid2, rot2, tr2); 
  G4LogicalVolume* intersectionV
    = new G4LogicalVolume(intersectionS, fBasicMaterial, "solid1Isolid2V");

  new G4PVPlacement(rot1, Hep3Vector(-wSize/4., 0., 2.*m),
                    intersectionV, "solid1Isolid2", worldV, false, 0); 
  
  // Subtraction
  //
  G4VSolid* subtractionS
    = new G4SubtractionSolid(
                  "solid1Ssolid2S", solid1, solid2, rot2, tr2); 
  G4LogicalVolume* subtractionV
    = new G4LogicalVolume(subtractionS, fBasicMaterial, "solid1Ssolid2V");

  new G4PVPlacement(rot1, Hep3Vector(0., 0., 2.*m), 
                   subtractionV, "solid1Ssolid2", worldV, false, 0);
  
  // Union
  //
  G4VSolid* unionS
    = new G4UnionSolid(
                  "solid1Usolid2S", solid1, solid2, rot2, tr2); 
  G4LogicalVolume* unionV
    = new G4LogicalVolume(unionS, fBasicMaterial, "solid1Usolid2V");

  new G4PVPlacement(rot1, Hep3Vector( wSize/4., 0., 2.*m),
                    unionV, "solid1Usolid2", worldV, false, 0);
  
  return (void*) world;
}

//_____________________________________________________________________________
void* TstGeometryViaGeant4::TestBooleanSolids3()
{
// Translation + reflection in solid displacement

  G4cout << "Reflections are not allowed in Boolean solids in Geant4." << G4endl;
  exit(1);
}

