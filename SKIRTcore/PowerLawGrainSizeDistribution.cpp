/*//////////////////////////////////////////////////////////////////
////       SKIRT -- an advanced radiative transfer code         ////
////       © Astronomical Observatory, Ghent University         ////
//////////////////////////////////////////////////////////////////*/

#include <cmath>
#include "FatalError.hpp"
#include "PowerLawGrainSizeDistribution.hpp"

////////////////////////////////////////////////////////////////////

PowerLawGrainSizeDistribution::PowerLawGrainSizeDistribution()
    : _gamma(0)
{
}

////////////////////////////////////////////////////////////////////

void PowerLawGrainSizeDistribution::setupSelfBefore()
{
    RangeGrainSizeDistribution::setupSelfBefore();

    // verify the attributes
    if (_gamma <= 0) throw FATALERROR("The exponent must be positive");
}

////////////////////////////////////////////////////////////////////

void PowerLawGrainSizeDistribution::setExponent(double value)
{
    _gamma = value;
}

////////////////////////////////////////////////////////////////////

double PowerLawGrainSizeDistribution::exponent() const
{
    return _gamma;
}

////////////////////////////////////////////////////////////////////

double PowerLawGrainSizeDistribution::dnda(double a) const
{
    return _C * pow(a,-_gamma);
}

////////////////////////////////////////////////////////////////////
