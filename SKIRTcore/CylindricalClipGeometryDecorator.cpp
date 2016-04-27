/*//////////////////////////////////////////////////////////////////
////       SKIRT -- an advanced radiative transfer code         ////
////       © Astronomical Observatory, Ghent University         ////
///////////////////////////////////////////////////////////////// */

#include "CylindricalClipGeometryDecorator.hpp"

using namespace std;

////////////////////////////////////////////////////////////////////

CylindricalClipGeometryDecorator::CylindricalClipGeometryDecorator()
    : _radius(0)
{
}

////////////////////////////////////////////////////////////////////

void CylindricalClipGeometryDecorator::setRadius(double value)
{
    _radius = value;
}

////////////////////////////////////////////////////////////////////

double CylindricalClipGeometryDecorator::radius() const
{
    return _radius;
}

////////////////////////////////////////////////////////////////////

int CylindricalClipGeometryDecorator::dimension() const
{
    return std::max(geometry()->dimension(), 2);
}

////////////////////////////////////////////////////////////////////

bool CylindricalClipGeometryDecorator::inside(Position bfr) const
{
    return bfr.cylradius() <= _radius;
}

////////////////////////////////////////////////////////////////////

double CylindricalClipGeometryDecorator::SigmaX() const
{
    return geometry()->SigmaX() * _norm;
}

////////////////////////////////////////////////////////////////////

double CylindricalClipGeometryDecorator::SigmaY() const
{
    return geometry()->SigmaY() * _norm;
}

////////////////////////////////////////////////////////////////////

double CylindricalClipGeometryDecorator::SigmaZ() const
{
    if (remove()==Inside) return 0.0;
    else return geometry()->SigmaZ();
}

////////////////////////////////////////////////////////////////////