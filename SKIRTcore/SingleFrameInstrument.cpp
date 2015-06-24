/*//////////////////////////////////////////////////////////////////
////       SKIRT -- an advanced radiative transfer code         ////
////       © Astronomical Observatory, Ghent University         ////
///////////////////////////////////////////////////////////////// */

#include "FatalError.hpp"
#include "FilePaths.hpp"
#include "Image.hpp"
#include "Log.hpp"
#include "PeerToPeerCommunicator.hpp"
#include "PhotonPackage.hpp"
#include "SingleFrameInstrument.hpp"
#include "Units.hpp"
#include "WavelengthGrid.hpp"

using namespace std;

////////////////////////////////////////////////////////////////////

SingleFrameInstrument::SingleFrameInstrument()
    : _Nxp(0), _xpmax(0), _Nyp(0), _ypmax(0)
{
}

////////////////////////////////////////////////////////////////////

void SingleFrameInstrument::setupSelfBefore()
{
    DistantInstrument::setupSelfBefore();

    // verify attribute values
    if (_Nxp <= 0 || _Nyp <= 0) throw FATALERROR("Number of pixels was not set");
    if (_xpmax <= 0 || _ypmax <= 0) throw FATALERROR("Maximum extent was not set");

    // calculate derived values
    _Nframep = _Nxp * _Nyp;
    _xpres = 2.0*_xpmax/(_Nxp-1);
    _ypres = 2.0*_ypmax/(_Nyp-1);
    _xpmin = -_xpmax;
    _ypmin = -_ypmax;
}

////////////////////////////////////////////////////////////////////

void SingleFrameInstrument::setPixelsX(int value)
{
    _Nxp = value;
}

////////////////////////////////////////////////////////////////////

int SingleFrameInstrument::pixelsX() const
{
    return _Nxp;
}

////////////////////////////////////////////////////////////////////

void SingleFrameInstrument::setExtentX(double value)
{
    _xpmax = value;
}

////////////////////////////////////////////////////////////////////

double SingleFrameInstrument::extentX() const
{
    return _xpmax;
}

////////////////////////////////////////////////////////////////////

void SingleFrameInstrument::setPixelsY(int value)
{
    _Nyp = value;
}

////////////////////////////////////////////////////////////////////

int SingleFrameInstrument::pixelsY() const
{
    return _Nyp;
}

////////////////////////////////////////////////////////////////////

void SingleFrameInstrument::setExtentY(double value)
{
    _ypmax = value;
}

////////////////////////////////////////////////////////////////////

double SingleFrameInstrument::extentY() const
{
    return _ypmax;
}

////////////////////////////////////////////////////////////////////

int SingleFrameInstrument::pixelondetector(const PhotonPackage* pp) const
{
    // get the position
    double x, y, z;
    pp->position().cartesian(x,y,z);

    // transform to detector coordinates using inclination, azimuth, and position angle
    double xpp = - _sinphi*x + _cosphi*y;
    double ypp = - _cosphi*_costheta*x - _sinphi*_costheta*y + _sintheta*z;
    double xp = _cospa * xpp - _sinpa * ypp;
    double yp = _sinpa * xpp + _cospa * ypp;

    // scale and round to pixel index
    int i = static_cast<int>(floor(((xp-_xpmin)/_xpres)+0.5));
    int j = static_cast<int>(floor(((yp-_ypmin)/_ypres)+0.5));
    if (i<0 || i>=_Nxp || j<0 || j>=_Nyp) return -1;
    else return i + _Nxp*j;
}

////////////////////////////////////////////////////////////////////

void SingleFrameInstrument::calibrateAndWriteDataCubes(QList< Array*> farrays, QStringList fnames)
{
    PeerToPeerCommunicator* comm = find<PeerToPeerCommunicator>();
    if (!comm->isRoot()) return;

    WavelengthGrid* lambdagrid = find<WavelengthGrid>();
    int Nlambda = lambdagrid->Nlambda();

    // calibration step 1: conversion from bolometric luminosities (units W) to monochromatic luminosities (units W/m)

    for (int ell=0; ell<Nlambda; ell++)
    {
        double dlambda = lambdagrid->dlambda(ell);
        for (int i=0; i<_Nxp; i++)
        {
            for (int j=0; j<_Nyp; j++)
            {
                size_t m = i + _Nxp*j + _Nframep*ell;
                foreach (Array* farr, farrays)
                {
                    if (farr->size()) (*farr)[m] /= dlambda;
                }
            }
        }
    }

    // calibration step 2: correction for the area of the pixels of the images; the units are now W/m/sr

    double xpresang = 2.0*atan(_xpres/(2.0*_distance));
    double ypresang = 2.0*atan(_ypres/(2.0*_distance));
    double area = xpresang*ypresang;
    foreach (Array* farr, farrays)
    {
        (*farr) /= area;
    }

    // calibration step 3: conversion of the flux per pixel from monochromatic luminosity units (W/m/sr)
    // to flux density units (W/m3/sr) by taking into account the distance

    double fourpid2 = 4.0*M_PI*_distance*_distance;
    foreach (Array* farr, farrays)
    {
        (*farr) /= fourpid2;
    }

    // conversion from program SI units (at this moment W/m3/sr) to the correct output units;
    // we use lambda*flambda for the surface brightness (in units like W/m2/arcsec2)

    Units* units = find<Units>();
    for (int ell=0; ell<Nlambda; ell++)
    {
        double lambda = lambdagrid->lambda(ell);
        for (int i=0; i<_Nxp; i++)
        {
            for (int j=0; j<_Nyp; j++)
            {
                size_t m = i + _Nxp*j + _Nframep*ell;
                foreach (Array* farr, farrays)
                {
                    if (farr->size()) (*farr)[m] = units->osurfacebrightness(lambda, (*farr)[m]);
                }
            }
        }
    }

    // Write a FITS file for each array
    for (int q = 0; q < farrays.size(); q++)
    {
        if (farrays[q]->size())
        {
            QString filename = _instrumentname + "_" + fnames[q];
            QString description = fnames[q] + " flux";

            // Create an image and save it
            Image image(this, _Nxp, _Nyp, Nlambda, _xpres, _ypres);
            image.saveto(this, *(farrays[q]), filename, description);
        }
    }
}

////////////////////////////////////////////////////////////////////
