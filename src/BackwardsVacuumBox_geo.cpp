//==========================================================================
//
//      <detector name ="DetName" type="Beampipe" >
//      <layer id="#(int)" inner_r="#(double)" outer_z="#(double)" >
//      <slice material="string" thickness="#(double)" >         
//      </layer>
//      </detector>
//==========================================================================
#include "DD4hep/DetFactoryHelper.h"
#include "DD4hep/Printout.h"
#include "TMath.h"
#include <XML/Helper.h>

using namespace std;
using namespace dd4hep;

/** \addtogroup beamline Beamline Instrumentation 
 */

/** \addtogroup IRChamber Interaction Region Vacuum Chamber.
 * \brief Type: **IRChamber**.
 * \ingroup beamline
 *
 *
 * \code
 *   <detector>
 *   </detector>
 * \endcode
 *
 */
static Ref_t create_detector(Detector& det, xml_h e, SensitiveDetector sens)  {

  using namespace ROOT::Math;
  xml_det_t  x_det     = e;
  string     det_name  = x_det.nameStr();
  Material   air       = det.air();
  DetElement sdet        (det_name,x_det.id());
  Assembly   assembly    (det_name+"_assembly");
  Material   m_Cu      = det.material("Copper");
  Material   m_Al      = det.material("Aluminum");
  Material   m_Be      = det.material("Beryllium");
  Material   m_Au      = det.material("Gold");
  Material   m_Vacuum  = det.material("Vacuum");
  string     vis_name  = x_det.visStr();

  xml::Component box_dim = x_det.child(_Unicode(dimensions));
  double height        = box_dim.attr<double>(_Unicode(height));

  xml::Component box_place = x_det.child(_Unicode(placement));
  double zOff        = box_place.attr<double>(_Unicode(z));

  xml::Component points = x_det.child(_Unicode(points));
  double x00         = points.attr<double>(_Unicode(x00));
  double y00         = points.attr<double>(_Unicode(y00));
  double x01         = points.attr<double>(_Unicode(x01));
  double y01         = points.attr<double>(_Unicode(y01));
  double x02         = points.attr<double>(_Unicode(x02));
  double y02         = points.attr<double>(_Unicode(y02));
  double x03         = points.attr<double>(_Unicode(x03));
  double y03         = points.attr<double>(_Unicode(y03));
  double x10         = x00;
  double y10         = y00;
  double x11         = x01;
  double y11         = y01;
  double x12         = x02;
  double y12         = y02;
  double x13         = x03;
  double y13         = y03;

  double vertices[] = {x00,y00,x01,y01,x02,y02,x03,y03,x10,y10,x11,y11,x12,y12,x13,y13};

  EightPointSolid box_vacuum(height,vertices);
  

  //Trap box_vacuum(10, 0,0,10,10,20,1,20,10,20,2);
  
  Volume v_vacuum("v_vacuum", box_vacuum, m_Vacuum);

  sdet.setAttributes(det, v_vacuum, x_det.regionStr(), x_det.limitsStr(), vis_name);

  assembly.placeVolume(v_vacuum, Position(0, 0, 0));

  // -----------------------------
  // final placement
  auto pv_assembly = det.pickMotherVolume(sdet).placeVolume(assembly,Transform3D(RotationZYX( 0.0, 0.0 , -M_PI/2), Position(0.0, 0.0, zOff)));
  pv_assembly.addPhysVolID("system",sdet.id()).addPhysVolID("barrel",1);
  sdet.setPlacement(pv_assembly);
  assembly->GetShape()->ComputeBBox();
  return sdet;
}

DECLARE_DETELEMENT(BackwardsVacuumBox,create_detector)
