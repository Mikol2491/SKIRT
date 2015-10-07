/*//////////////////////////////////////////////////////////////////
////       SKIRT -- an advanced radiative transfer code         ////
////       © Astronomical Observatory, Ghent University         ////
///////////////////////////////////////////////////////////////// */

#include "FatalError.hpp"
#include "CylinderDustGrid.hpp"

using namespace std;

//////////////////////////////////////////////////////////////////////

CylinderDustGrid::CylinderDustGrid()
    : _Rmax(0), _zmin(0), _zmax(0)
{
}

//////////////////////////////////////////////////////////////////////

void CylinderDustGrid::setupSelfBefore()
{
    DustGrid::setupSelfBefore();
    if (_Rmax <= 0) throw FATALERROR("The outer radius of the grid should be positive");
    if (_zmax <= _zmin) throw FATALERROR("The extent of the Cylinder should be positive in the Z direction");
    setBoundingbox(Box(-_Rmax,-_Rmax,_zmin,_Rmax,_Rmax,_zmax));
}

//////////////////////////////////////////////////////////////////////

void CylinderDustGrid::setMaxR(double value)
{
    _Rmax = value;
}

//////////////////////////////////////////////////////////////////////

double CylinderDustGrid::maxR() const
{
    return _Rmax;
}

//////////////////////////////////////////////////////////////////////

void CylinderDustGrid::setMinZ(double value)
{
    _zmin = value;
}

//////////////////////////////////////////////////////////////////////

double CylinderDustGrid::minZ() const
{
    return _zmin;
}

//////////////////////////////////////////////////////////////////////

void CylinderDustGrid::setMaxZ(double value)
{
    _zmax = value;
}

//////////////////////////////////////////////////////////////////////

double CylinderDustGrid::maxZ() const
{
    return _zmax;
}

//////////////////////////////////////////////////////////////////////
