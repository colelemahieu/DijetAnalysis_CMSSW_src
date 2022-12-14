#ifndef pfIsoCalculator_h
#define pfIsoCalculator_h

#include "DataFormats/EgammaCandidates/interface/Photon.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Utilities/interface/EDGetToken.h"
#include "Geometry/CaloGeometry/interface/CaloGeometry.h"
#include "Geometry/Records/interface/IdealGeometryRecord.h"

class pfIsoCalculator
{
  public:
    pfIsoCalculator(const edm::Event &iEvent, const edm::EDGetTokenT<edm::View<reco::PFCandidate> > pfCandidates, const math::XYZPoint& pv);

    template <class T>
    bool isInFootprint(const T& footprint, const edm::Ptr<reco::PFCandidate>& candidate, const int matchOpt);

    double getPfIso(const reco::Photon& photon, int pfId, double r1=0.4, double r2=0.00, double threshold=0, double jWidth=0.0, int footprintRemoval = 0, const std::vector<reco::PFCandidateRef>& particlesInIsoMap = {});
    double getPfIsoSubUE(const reco::Photon& photon, int pfId, double r1=0.4, double r2=0.00, double threshold=0, double jWidth=0.0, int footprintRemoval = 0, const std::vector<reco::PFCandidateRef>& particlesInIsoMap = {}, bool excludeCone = false);

    double getPfIso(const reco::GsfElectron& ele, int pfId, double r1=0.4, double r2=0.00, double threshold=0);

    enum footprintOptions {
      noRemoval=0,
      PFcand_matchKey=1,    // remove PF candidates in the isolation map by matching its key
      PFcand_matchKin=2,    // remove PF candidates in the isolation map by matching its kinematics
      removeSCenergy=3,     // remove SC raw transverse energy
    };

  private:
    edm::Handle<edm::View<reco::PFCandidate> > candidatesView;
    reco::Vertex::Point vtx_;

    const float limit_match_kin = 0.00001;
};

#endif
