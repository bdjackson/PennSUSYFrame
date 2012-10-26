#include <cmath>

#include "include/Electron.h"
#include "AtlasSFrameUtils/include/CycleMacros.h"

ClassImp(Electron)

// ----------------------------------------------------------------------------
  Electron::Electron( const ParticleElement<D3PDReader::ElectronD3PDObjectElement>& p
                    , CommonTools::TLVTool* tlv_tool
                    , CommonTools::IsoCorrectionTool* iso_corr_tool
                    , int index
                    )
                    : ParticleElement<D3PDReader::ElectronD3PDObjectElement>(p,index,false)
                    , m_tlv_prepped(false)
                    , m_raw_tlv_prepped(false)
                    , m_tlv_tool(tlv_tool)
                    , m_iso_corr_tool(iso_corr_tool)
{
  // do nothing
}

// ----------------------------------------------------------------------------
TLorentzVector Electron::getTlv() const
{
  if (!m_tlv_prepped) {
    std::cout << "WARNING!!! Electron TLV is not set "
              << "-- may produce unexpected results!\n"
              << "\tCall prepTlv() to prepare the electron TLV\n";
  }
  return m_tlv;
}

// ----------------------------------------------------------------------------
TLorentzVector Electron::getRawTlv() const
{
  if (!m_raw_tlv_prepped) {
    std::cout << "WARNING!!! Electron raw TLV is not set "
              << "-- may produce unexpected results!\n"
              << "\tCall prepRawTlv() to prepare the electron TLV\n";
  }
  return m_raw_tlv;
}

// ----------------------------------------------------------------------------
void Electron::prepTlv()
{
  if (m_tlv_prepped == false) {
    m_tlv = m_tlv_tool->tlv(this);
    m_tlv_prepped = true;
  }
}

// ----------------------------------------------------------------------------
void Electron::prepRawTlv()
{
  if (m_raw_tlv_prepped == false) {
    m_raw_tlv = m_tlv_tool->rawTlv(this);
    m_raw_tlv_prepped = true;
  }
}

// ----------------------------------------------------------------------------
float Electron::getEta() const
{
  if (nSiHits() < 4) return cl_eta();
  return tracketa();
}

// ----------------------------------------------------------------------------
float Electron::getPhi() const
{
  if (nSiHits() < 4) return cl_phi();
  return trackphi();
}

// ----------------------------------------------------------------------------
float Electron::getD0Significance() const
{
  float d0     = trackd0pv();
  float d0_sig = tracksigd0pv();

  return d0/d0_sig;
}

// ----------------------------------------------------------------------------
float Electron::getZ0SinTheta() const
{
  float z0        = trackz0pv();
  float sin_theta = sin(getTlv().Theta());

  return z0*sin_theta;
}

// -----------------------------------------------------------------------------
double Electron::getIsoCorr( CommonTools::ISO_TYPE iso_type
                           , int cone_size
                           , int num_vertex
                           ) const
{
  double iso = 0;

  switch (iso_type) {
    case CommonTools::REL_PTCONE         : // same as PTCONE
    case CommonTools::PTCONE             : iso = ptcone(cone_size);
                                           break;
    case CommonTools::REL_ETCONE         : // same as ETCONE
    case CommonTools::ETCONE             : iso = etcone(cone_size);
                                           break;
    case CommonTools::REL_TOPOETCONE     : // same as TOPOETCONE
    case CommonTools::TOPOETCONE         : iso = topoetcone(cone_size);
                                           break;
    case CommonTools::REL_TOPOETCONE_CORR: // same as TOPOETCONE_CORR
    case CommonTools::TOPOETCONE_CORR    : iso = topoetcone_corrected(cone_size);
                                           break;
  }

  iso -= m_iso_corr_tool->getIsoCorrection(iso_type, cone_size, num_vertex);

  if (  iso_type == CommonTools::REL_PTCONE
     || iso_type == CommonTools::REL_ETCONE
     || iso_type == CommonTools::REL_TOPOETCONE
     || iso_type == CommonTools::REL_TOPOETCONE_CORR
     ) {
    iso /= getTlv().Pt();
  }

  return iso;
}

// -----------------------------------------------------------------------------
double Electron::ptcone(int cone_size) const
{
  double iso = 0.;

  switch (cone_size) {
    case 20: iso = ptcone20();
             break;
    case 30: iso = ptcone30();
             break;
    case 40: iso = ptcone40();
             break;
  };

  return iso;
}

// -----------------------------------------------------------------------------
double Electron::etcone(int cone_size) const
{
  double iso = 0.;

  switch (cone_size) {
    case 20: iso = Etcone20();
             break;
    case 30: iso = Etcone30();
             break;
    case 40: iso = Etcone40();
             break;
  };

  return iso;
}

// -----------------------------------------------------------------------------
double Electron::topoetcone(int cone_size) const
{
  double iso = 0.;

  switch (cone_size) {
    case 20: iso = topoEtcone20();
             break;
    case 30: iso = topoEtcone30();
             break;
    case 40: iso = topoEtcone40();
             break;
  };

  return iso;
}
// -----------------------------------------------------------------------------
double Electron::topoetcone_corrected(int cone_size) const
{
  double iso = 0.;

  switch (cone_size) {
    case 20: iso = topoEtcone20_corrected();
             break;
    case 30: iso = topoEtcone30_corrected();
             break;
    case 40: iso = topoEtcone40_corrected();
             break;
  };

  return iso;
}

// ----------------------------------------------------------------------------
void Electron::print(const VertexContainer& vertices) const
{
  TLorentzVector tlv = getTlv();
  TLorentzVector raw_tlv = getRawTlv();

  size_t num_good_vertices = vertices.num(VERT_GOOD);

  std::cout << "\traw pt: "  << raw_tlv.Pt()
            << "\traw eta: " << raw_tlv.Eta()
            << "\traw phi: " << raw_tlv.Phi()
            << "\n"
            << "\tpt: "  << tlv.Pt()
            << "\teta: " << tlv.Eta()
            << "\tphi: " << tlv.Phi()
            << "\n"
            << "\td0sig: " << getD0Significance()
            << "\tz0sinthata: " << getZ0SinTheta()
            << "\n"
            << "\tptcone30 (no correction): " << getIsoCorr(
                CommonTools::PTCONE, 30, 0)
            << "\tptcone30/pt (no correction): " << getIsoCorr(
                CommonTools::REL_PTCONE, 30, 0)
            << "\tetcone30 (no correction): " << getIsoCorr(
                CommonTools::TOPOETCONE_CORR, 30, 0)
            << "\tetcone30/pt (no correction): " << getIsoCorr(
                CommonTools::REL_TOPOETCONE_CORR, 30, 0)
            << "\n"
            << "\tptcone30: " << getIsoCorr(
                CommonTools::PTCONE, 30, num_good_vertices)
            << "\tptcone30/pt: " << getIsoCorr(
                CommonTools::REL_PTCONE, 30, num_good_vertices)
            << "\tetcone30: " << getIsoCorr(
                CommonTools::TOPOETCONE_CORR, 30, num_good_vertices)
            << "\tetcone30/pt: " << getIsoCorr(
                CommonTools::REL_TOPOETCONE_CORR, 30, num_good_vertices)
            << "\n";
}

// -----------------------------------------------------------------------------
bool Electron::eq(const Electron& el1, const Electron& el2)
{
  return (el1 == el2);
}

// -----------------------------------------------------------------------------
bool Electron::lt(const Electron& el1, const Electron& el2)
{
  return (el1 < el2);
}

// -----------------------------------------------------------------------------
bool Electron::gt(const Electron& el1, const Electron& el2)
{
  return (el1 > el2);
}

// -----------------------------------------------------------------------------
bool Electron::le(const Electron& el1, const Electron& el2)
{
  return (el1 <= el2);
}

// -----------------------------------------------------------------------------
bool Electron::ge(const Electron& el1, const Electron& el2)
{
  return (el1 >= el2);
}

// -----------------------------------------------------------------------------
bool Electron::operator==(const Electron& rhs) const
{
  return (getTlv().Pt() == rhs.getTlv().Pt());
}

// -----------------------------------------------------------------------------
bool Electron::operator<(const Electron& rhs) const
{
  return (getTlv().Pt() < rhs.getTlv().Pt());
}

// -----------------------------------------------------------------------------
bool Electron::operator>(const Electron& rhs) const
{
  return (getTlv().Pt() > rhs.getTlv().Pt());
}

// -----------------------------------------------------------------------------
bool Electron::operator<=(const Electron& rhs) const
{
  return (getTlv().Pt() <= rhs.getTlv().Pt());
}

// -----------------------------------------------------------------------------
bool Electron::operator>=(const Electron& rhs) const
{
  return (getTlv().Pt() >= rhs.getTlv().Pt());
}
