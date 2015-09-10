/*//////////////////////////////////////////////////////////////////
////       SKIRT -- an advanced radiative transfer code         ////
////       © Astronomical Observatory, Ghent University         ////
///////////////////////////////////////////////////////////////// */

#include <cmath>
#include "ExpDiskGeometry.hpp"
#include "FatalError.hpp"
#include "Random.hpp"
#include "SpecialFunctions.hpp"

using namespace std;

////////////////////////////////////////////////////////////////////

ExpDiskGeometry::ExpDiskGeometry()
    : _hR(0), _hz(0), _Rmax(0), _zmax(0), _Rmin(0), _rho0(0)
{
}

////////////////////////////////////////////////////////////////////

void ExpDiskGeometry::setupSelfBefore()
{
    SepAxGeometry::setupSelfBefore();

    // verify property values
    if (_hR <= 0) throw FATALERROR("The radial scale length hR should be positive");
    if (_hz <= 0) throw FATALERROR("The axial scale height hz should be positive");
    if (_Rmax < 0) throw FATALERROR("The radial truncation length Rmax should be zero or positive");
    if (_zmax < 0) throw FATALERROR("The axial truncation length zmax should be zero or positive");
    if (_Rmin < 0) throw FATALERROR("The minimum radius Rmax should be zero or positive");
    else if (_Rmin > _Rmax && _Rmax > 0)
        throw FATALERROR("The minimum radius Rmin should be larger than the truncation radius Rmax");

    // calculate central density
    double intphi = 2.0*M_PI;
    double intz = (_zmax>0) ? -2.0*_hz*expm1(-_zmax/_hz) : 2.0*_hz;
    double tmin = (_Rmin>0) ? exp(-_Rmin/_hR)*(1.0+_Rmin/_hR) : 1.0;
    double tmax = (_Rmax>0) ? exp(-_Rmax/_hR)*(1.0+_Rmax/_hR) : 0.0;
    double intR = _hR*_hR*(tmin-tmax);
    _rho0 = 1.0/(intR*intphi*intz);
}

////////////////////////////////////////////////////////////////////

void ExpDiskGeometry::setRadialScale(double value)
{
    _hR = value;
}

////////////////////////////////////////////////////////////////////

double ExpDiskGeometry::radialScale() const
{
    return _hR;
}

////////////////////////////////////////////////////////////////////

void ExpDiskGeometry::setAxialScale(double value)
{
    _hz = value;
}

////////////////////////////////////////////////////////////////////

double ExpDiskGeometry::axialScale() const
{
    return _hz;
}

////////////////////////////////////////////////////////////////////

void ExpDiskGeometry::setRadialTrunc(double value)
{
    _Rmax = value;
}

////////////////////////////////////////////////////////////////////

double ExpDiskGeometry::radialTrunc() const
{
    return _Rmax;
}

////////////////////////////////////////////////////////////////////

void ExpDiskGeometry::setAxialTrunc(double value)
{
    _zmax = value;
}

////////////////////////////////////////////////////////////////////

double ExpDiskGeometry::axialTrunc() const
{
    return _zmax;
}

////////////////////////////////////////////////////////////////////

void ExpDiskGeometry::setInnerRadius(double value)
{
    _Rmin = value;
}

////////////////////////////////////////////////////////////////////

double ExpDiskGeometry::innerRadius() const
{
    return _Rmin;
}

////////////////////////////////////////////////////////////////////

double
ExpDiskGeometry::density(double R, double z)
const
{
    double absz = fabs(z);
    if (_Rmax>0.0 && R>_Rmax)
        return 0.0;
    else if (_zmax>0.0 && absz>_zmax)
        return 0.0;
    else if (R<_Rmin)
        return 0.0;
    return _rho0 * exp(-R/_hR) * exp(-absz/_hz);
}

////////////////////////////////////////////////////////////////////

double
ExpDiskGeometry::randomR()
const
{
    double R, X;
    do
    {
        X = _random->uniform();
        R =_hR*(-1.0-SpecialFunctions::LambertW1((X-1.0)/M_E));
    }
    while ( (_Rmax>0.0 && R>=_Rmax) || R<=_Rmin);
    return R;
}

////////////////////////////////////////////////////////////////////

double
ExpDiskGeometry::randomz()
const
{
    double z, X;
    do
    {
        X = _random->uniform();
        z = (X<=0.5) ? _hz*log(2.0*X) : -_hz*log(2.0*(1.0-X));
    }
    while (_zmax>0.0 && fabs(z)>=_zmax);
    return z;
}

//////////////////////////////////////////////////////////////////////

double
ExpDiskGeometry::SigmaR()
const
{
    if (_Rmax>0.0)
        return _rho0 * _hR * (exp(-_Rmin/_hR)-exp(-_Rmax/_hR));
    else
        return _rho0 * _hR * exp(-_Rmin/_hR);
}

//////////////////////////////////////////////////////////////////////

double
ExpDiskGeometry::SigmaZ()
const
{
    if (_Rmin>0.0)
        return 0.0;
    else if (_zmax>0.0)
        return -2.0 * _rho0 * _hz * expm1(-_zmax/_hz);
    else
        return 2.0 * _rho0 * _hz;
}

////////////////////////////////////////////////////////////////////
