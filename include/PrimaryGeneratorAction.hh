//
// $Id$
//
/// \file PrimaryGeneratorAction.hh
/// \brief Definition of the PrimaryGeneratorAction class

#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"

#include "TFile.h"
#include "TTree.h"
#include "TH2F.h"

#include "InputInfo.hh"

#define maxGammas maxNumberOfStates+1

class G4ParticleGun;
class G4Event;
class DetectorConstruction;

/// The primary generator action class with particle gum.
///
/// The default kinematic is a 6 MeV gamma, randomly distribued 
/// in front of the phantom across 80% of the (X,Y) phantom size.

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    // PrimaryGeneratorAction();    
    PrimaryGeneratorAction(InputInfo* info);    
    virtual ~PrimaryGeneratorAction();

    // static access method
    static const PrimaryGeneratorAction* Instance();

    // open root file and get tree
    void SetRootTreeInput();

    // method from the base class
    virtual void GeneratePrimaries(G4Event*);         
  
    // method to access particle gun
    const G4ParticleGun* GetParticleGun() const { return fParticleGun; }

    // getter and setter for root file name
    // todo: incomplete!
    void SetRootInputFileName(std::string name){fRootInputFileName=name;}
    std::string GetRootInputFileName(){return fRootInputFileName;}

    G4int GetEventNumber() const {return fEventNumber;}
  
  private:
    static PrimaryGeneratorAction* fgInstance;

    std::string fRootInputFileName;
    TFile* fRootInputFile;
    TTree* fTree;
    TH2F* fHistKinematics;

    Double_t fTheta, fPhi, fEnergy;
    Int_t fEventNumber, fPdgId;
    Float_t fX0, fY0, fZ0;
    Float_t vertex[3];
    //Double_t fX0, fY0, fZ0;

    Int_t fGammaMul;
    Float_t fGammaE[maxGammas], fGammaTheta[maxGammas], fGammaPhi[maxGammas];
   
    G4ParticleGun*  fParticleGun; // pointer a to G4 gun class
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif


