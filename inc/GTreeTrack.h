#ifndef __GTreeTrack_h__
#define __GTreeTrack_h__


#include <TLorentzVector.h>
#include "Rtypes.h"
#include "GTree.h"


#define GTreeTrack_MAX 128

class   GTreeParticle;
class   GTreeMeson;

class  GTreeTrack : public GTree
{
public:
    enum
    {
        DETECTOR_NONE = 0,
        DETECTOR_NaI = 1,
        DETECTOR_PID = 2,
        DETECTOR_MWPC = 4,
        DETECTOR_BaF2 = 8,
        DETECTOR_PbWO4 = 16,
        DETECTOR_Veto = 32,
    };
private:
    Int_t		nTracks;
    Double_t	clusterEnergy[GTreeTrack_MAX];
    Double_t 	theta[GTreeTrack_MAX];
    Double_t 	phi[GTreeTrack_MAX];
    Double_t	time[GTreeTrack_MAX];
    Int_t       clusterSize[GTreeTrack_MAX];
    Int_t       centralCrystal[GTreeTrack_MAX];
    Int_t       centralVeto[GTreeTrack_MAX];
    Int_t       detectors[GTreeTrack_MAX];
    //Charged detector energies
    Double_t	vetoEnergy[GTreeTrack_MAX];
    Double_t	MWPC0Energy[GTreeTrack_MAX];
    Double_t	MWPC1Energy[GTreeTrack_MAX];
    //TAPS PSA Short-gate Energy
    Double_t	shortEnergy[GTreeTrack_MAX];
    //Pseudo vertex information
    Double_t    pseudoVertexX[GTreeTrack_MAX];
    Double_t    pseudoVertexY[GTreeTrack_MAX];
    Double_t    pseudoVertexZ[GTreeTrack_MAX];

    Double_t    targetShift;
    Double_t    TAPSDistance;
    Double_t    CBDistance;

protected:
    virtual void    SetBranchAdresses();
    virtual void    SetBranches();

public:
    GTreeTrack(GTreeManager *Manager, const TString& _Name);
    virtual ~GTreeTrack();

    virtual void    Clear()     {nTracks = 0;}

    const	Int_t*          GetDetectors()                      const	{return detectors;}
            Int_t           GetDetectors(const Int_t index)     const	{return detectors[index];}
    const	Int_t*          GetClusterSize()                    const	{return clusterSize;}
            Int_t           GetClusterSize(const Int_t index)   const 	{return clusterSize[index];}
    const	Int_t*          GetCentralCrystal()                   const	{return centralCrystal;}
            Int_t           GetCentralCrystal(const Int_t index)  const {return centralCrystal[index];}
    const	Int_t*          GetCentralVeto()                      const	{return centralVeto;}
            Int_t           GetCentralVeto(const Int_t index)   const 	{return centralVeto[index];}
    const	Double_t*       GetVetoEnergy()                     const	{return vetoEnergy;}
            Double_t        GetVetoEnergy(const Int_t index)    const	{return vetoEnergy[index];}
    const	Double_t*       GetClusterEnergy()                  const	{return clusterEnergy;}
            Double_t        GetClusterEnergy(const Int_t index) const	{return clusterEnergy[index];}
            Int_t           GetNTracks()                        const	{return nTracks;}
    inline  Int_t           GetNCB()                            const;
    inline  Int_t           GetNTAPS()                          const;
    inline  Bool_t          HasCB(const Int_t index)            const;
    inline  Bool_t          HasTAPS(const Int_t index)          const;
    const	Double_t*       GetPhi()                            const	{return phi;}
            Double_t        GetPhi(const Int_t index)           const	{return phi[index];}
            Double_t        GetPhiRad(const Int_t index)        const	{return phi[index] * TMath::DegToRad();}
    const	Double_t*       GetTheta()                          const	{return theta;}
    inline  Double_t        GetTheta(const Int_t index)         const;
    inline  Double_t        GetThetaRad(const Int_t index)      const;
    const	Double_t*       GetTime()                           const	{return time;}
            Double_t        GetTime(const Int_t index)          const	{return time[index];}
    inline  TLorentzVector	GetVector(const Int_t index)        const;
    inline  TLorentzVector	GetVector(const Int_t index, const Double_t mass)   const;
    inline  TVector3    	GetUnitVector(const Int_t index)        const;
    const	Double_t*       GetMWPC0Energy()                          const	{return MWPC0Energy;}
            Double_t        GetMWPC0Energy(const Int_t index)         const	{return MWPC0Energy[index];}
    const	Double_t*       GetMWPC1Energy()                          const	{return MWPC1Energy;}
            Double_t        GetMWPC1Energy(const Int_t index)         const	{return MWPC1Energy[index];}
    const	Double_t*       GetShortEnergy()                          const	{return shortEnergy;}
            Double_t        GetShortEnergy(const Int_t index)         const	{return shortEnergy[index];}
            Double_t        GetPSAAngle(const Int_t index)            const	{return TMath::ATan(shortEnergy[index]/clusterEnergy[index])*TMath::RadToDeg();}
            Double_t        GetPSARadius(const Int_t index)           const	{return TMath::Sqrt(TMath::Power(shortEnergy[index],2)+TMath::Power(clusterEnergy[index],2));}
    const	Double_t*       GetPseudoVertexX()                        const	{return pseudoVertexX;}
            Double_t        GetPseudoVertexX(const Int_t index)       const	{return pseudoVertexX[index];}
    const	Double_t*       GetPseudoVertexY()                        const	{return pseudoVertexY;}
            Double_t        GetPseudoVertexY(const Int_t index)       const	{return pseudoVertexY[index];}
    const	Double_t*       GetPseudoVertexZ()                        const	{return pseudoVertexZ;}
            Double_t        GetPseudoVertexZ(const Int_t index)       const	{return pseudoVertexZ[index];}
    inline  Bool_t          IsNeutral(const Int_t index)              const;
    inline  Bool_t          IsCharged(const Int_t index)              const;
            Double_t        GetTargetShift()   const   {return targetShift;}
            Double_t        GetTAPSDistance()  const   {return TAPSDistance;}
            void            SetTargetShift(const Double_t shift) {targetShift = shift;}
            void            SetTAPSDistance(const Double_t tapsd) {TAPSDistance = tapsd;}
    virtual void            Print(const Bool_t All = kFALSE)    const;

    friend  class GTreeParticle;
    friend  class GTreeMeson;
};

Double_t GTreeTrack::GetTheta(const Int_t index) const
{
    if(targetShift == 0)
    {
        return theta[index];
    }
    else if(HasCB(index) && !HasTAPS(index))
    {
        return (TMath::RadToDeg()*TMath::ATan2((CBDistance*TMath::Sin(theta[index]*TMath::DegToRad())),((CBDistance*TMath::Cos(theta[index]*TMath::DegToRad()))-targetShift)));
    }
    else if(!HasCB(index) && HasTAPS(index))
    {
        return (TMath::RadToDeg()*TMath::ATan2((TAPSDistance*TMath::Tan(theta[index]*TMath::DegToRad())),(TAPSDistance-targetShift)));
    }
    else
    {
        std::cout << "How did I get here?" << std::endl;
        return 0;
    }
}

Double_t GTreeTrack::GetThetaRad(const Int_t index) const
{
    Double_t th = theta[index] * TMath::DegToRad();
    if(targetShift == 0)
    {
        return th;
    }
    else if(HasCB(index) && !HasTAPS(index))
    {
        return (TMath::ATan2((CBDistance*TMath::Sin(th)),((CBDistance*TMath::Cos(th))-targetShift)));
    }
    else if(!HasCB(index) && HasTAPS(index))
    {
        return (TMath::ATan2((TAPSDistance*TMath::Tan(th)),(TAPSDistance-targetShift)));
    }
    else
    {
        std::cout << "How did I get here?" << std::endl;
        return 0;
    }
}

TLorentzVector	GTreeTrack::GetVector(const Int_t index) const
{
    Double_t th = GetThetaRad(index);
    Double_t ph = GetPhiRad(index);

    Double_t Px = clusterEnergy[index]* sin(th)*cos(ph);
    Double_t Py = clusterEnergy[index]* sin(th)*sin(ph);
    Double_t Pz = clusterEnergy[index]* cos(th);

    return TLorentzVector(Px, Py, Pz, clusterEnergy[index]);
}

TLorentzVector	GTreeTrack::GetVector(const Int_t index, const Double_t mass) const
{
    Double_t th = GetThetaRad(index);
    Double_t ph = GetPhiRad(index);

    Double_t E 	= clusterEnergy[index] + mass;
    Double_t P 	= TMath::Sqrt(E*E - mass*mass);
    Double_t Px = P* sin(th)*cos(ph);
    Double_t Py = P* sin(th)*sin(ph);
    Double_t Pz = P* cos(th);

    return TLorentzVector(Px, Py, Pz, E);
}

TVector3	GTreeTrack::GetUnitVector(const Int_t index) const
{
    Double_t th = GetThetaRad(index);
    Double_t ph = GetPhiRad(index);

    Double_t Px = sin(th)*cos(ph);
    Double_t Py = sin(th)*sin(ph);
    Double_t Pz = cos(th);

    return TVector3(Px, Py, Pz);
}

Int_t		GTreeTrack::GetNCB()	const
{
    Int_t NCB = 0;
    for(Int_t i = 0; i < nTracks; i++)
    {
        if (HasCB(i)) NCB++;
    }
    return NCB;
}

Int_t		GTreeTrack::GetNTAPS()	const
{
    Int_t NTAPS = 0;
    for(Int_t i = 0; i < nTracks; i++)
    {
        if (HasTAPS(i)) NTAPS++;
    }
    return NTAPS;
}

Bool_t      GTreeTrack::HasCB(const Int_t index) const
{
    if (detectors[index] & DETECTOR_NaI) return true;
    if (detectors[index] & DETECTOR_PID) return true;
    if (detectors[index] & DETECTOR_MWPC) return true;
    return false;
}

Bool_t      GTreeTrack::HasTAPS(const Int_t index) const
{
    if (detectors[index] & DETECTOR_BaF2) return true;
    if (detectors[index] & DETECTOR_PbWO4) return true;
    if (detectors[index] & DETECTOR_Veto) return true;
    return false;
}

Bool_t      GTreeTrack::IsNeutral(const Int_t index) const
{
    if (vetoEnergy[index] > 0) return false;
    if (MWPC0Energy[index] > 0) return false;
    if (MWPC1Energy[index] > 0) return false;
    return true;
}

Bool_t      GTreeTrack::IsCharged(const Int_t index) const
{
    if (vetoEnergy[index] > 0) return true;
    if (MWPC0Energy[index] > 0) return true;
    if (MWPC1Energy[index] > 0) return true;
    return false;
}
#endif
