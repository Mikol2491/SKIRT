/*//////////////////////////////////////////////////////////////////
////       SKIRT -- an advanced radiative transfer code         ////
////       © Astronomical Observatory, Ghent University         ////
///////////////////////////////////////////////////////////////// */

#include "DustSystem.hpp"
#include "HISystem.hpp"
#include "LyaMonteCarloSimulation.hpp"
#include "LyaWavelengthGrid.hpp"
#include "StellarSystem.hpp"

using namespace std;

////////////////////////////////////////////////////////////////////

LyaMonteCarloSimulation::LyaMonteCarloSimulation()
    : _his(0)
{
}

////////////////////////////////////////////////////////////////////

void LyaMonteCarloSimulation::setWavelengthGrid(LyaWavelengthGrid* value)
{
    if (_lambdagrid) delete _lambdagrid;
    _lambdagrid = value;
    if (_lambdagrid) _lambdagrid->setParent(this);
}

////////////////////////////////////////////////////////////////////

LyaWavelengthGrid* LyaMonteCarloSimulation::wavelengthGrid() const
{
    return dynamic_cast<LyaWavelengthGrid*>(_lambdagrid);
}

////////////////////////////////////////////////////////////////////

void LyaMonteCarloSimulation::setStellarSystem(StellarSystem* value)
{
    if (_ss) delete _ss;
    _ss = value;
    if (_ss) _ss->setParent(this);
}

////////////////////////////////////////////////////////////////////

StellarSystem* LyaMonteCarloSimulation::stellarSystem() const
{
    return _ss;
}

////////////////////////////////////////////////////////////////////

void LyaMonteCarloSimulation::setHISystem(HISystem* value)
{
    if (_his) delete _his;
    _his = value;
    if (_his) _his->setParent(this);
}

////////////////////////////////////////////////////////////////////

HISystem* LyaMonteCarloSimulation::hISystem() const
{
    return _his;
}

////////////////////////////////////////////////////////////////////

void LyaMonteCarloSimulation::runSelf()
{
    runstellaremission();
    write();
}

////////////////////////////////////////////////////////////////////
