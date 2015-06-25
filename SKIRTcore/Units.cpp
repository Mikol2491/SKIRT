/*//////////////////////////////////////////////////////////////////
////       SKIRT -- an advanced radiative transfer code         ////
////       © Astronomical Observatory, Ghent University         ////
///////////////////////////////////////////////////////////////// */

#include <cmath>
#include <QHash>
#include <QMutex>
#include "FatalError.hpp"
#include "Units.hpp"

using namespace std;

////////////////////////////////////////////////////////////////////

namespace
{
    // fundamental physical and astronomical constants
    const double _c = 2.99792458e8;
    const double _h = 6.62606957e-34;
    const double _k = 1.3806488e-23;
    const double _NA = 6.02214129e23;
    const double _AU = 1.49597871e11;
    const double _pc = 3.08567758e16;
    const double _Mproton = 1.67262178e-27;
    const double _Melectron = 9.10938215e-31;
    const double _Msun = 1.9891e30;
    const double _Lsun = 3.839e26;              // solar luminosity without solar neutrino radiation
    const double _lambdaV = 550e-9;             // V-band wavelength
    const double _kappaV = 2600.;               // "standard" extinction coefficient in V-band
    const double _sigmaThomson = 6.652458734e-29; // Thomson cross-section for an electron
}

////////////////////////////////////////////////////////////////////

namespace
{
    // mutex to guard initialization of the static dictionary
    QMutex _mutex;

    // flag becomes true if static dictionary has been initialized
    bool _initialized = false;

    // static dictionary holding the proportionality factor for each predefined unit
    // (converting from specified unit to SI unit)
    QHash<QString, double> _factor;

    // initialize the predefined units in the static dictionary
    void initialize()
    {
        // initialization must be locked to protect against race conditions when used in multiple threads
        // (which can happen if the application fails to explicitly call this function).
        QMutexLocker lock(&_mutex);

        if (!_initialized)
        {
            // *** add any extra quantity/unit combinations to the list below

            // length
            _factor["length m"] = 1.;
            _factor["length cm"] = 1e-2;
            _factor["length km"] = 1e3;
            _factor["length AU"] = _AU;
            _factor["length pc"] = _pc;
            _factor["length kpc"] = 1e3 * _pc;
            _factor["length Mpc"] = 1e6 * _pc;

            // distance
            _factor["distance m"] = 1.;
            _factor["distance cm"] = 1e-2;
            _factor["distance km"] = 1e3;
            _factor["distance AU"] = _AU;
            _factor["distance pc"] = _pc;
            _factor["distance kpc"] = 1e3 * _pc;
            _factor["distance Mpc"] = 1e6 * _pc;

            // wavelength
            _factor["wavelength m"] = 1.;
            _factor["wavelength cm"] = 1e-2;
            _factor["wavelength mm"] = 1e-3;
            _factor["wavelength micron"] = 1e-6;
            _factor["wavelength nm"] = 1e-9;
            _factor["wavelength A"] = 1e-10;

            // grainsize
            _factor["grainsize m"] = 1.;
            _factor["grainsize cm"] = 1e-2;
            _factor["grainsize mm"] = 1e-3;
            _factor["grainsize micron"] = 1e-6;
            _factor["grainsize nm"] = 1e-9;
            _factor["grainsize A"] = 1e-10;

            // cross section
            _factor["section m2"] = 1.;

            // volume
            _factor["volume m3"] = 1.;
            _factor["volume AU3"] = pow(_AU,3);
            _factor["volume pc3"] = pow(_pc,3);

            // velocity
            _factor["velocity m/s"] = 1.;
            _factor["velocity km/s"] = 1e3;

            // mass
            _factor["mass kg"] = 1.;
            _factor["mass g"] = 1e-3;
            _factor["mass Msun"] = _Msun;

            // bulk mass
            _factor["bulkmass kg"] = 1.;

            // bulk mass density
            _factor["bulkmassdensity kg/m3"] = 1.;
            _factor["bulkmassdensity g/cm3"] = 1e3;

            // mass surface density
            _factor["masssurfacedensity kg/m2"] = 1.;
            _factor["masssurfacedensity Msun/AU2"] = _Msun/pow(_AU,2);
            _factor["masssurfacedensity Msun/pc2"] = _Msun/pow(_pc,2);

            // mass volume density
            _factor["massvolumedensity kg/m3"] = 1.;
            _factor["massvolumedensity g/cm3"] = 1e3;
            _factor["massvolumedensity Msun/AU3"] = _Msun/pow(_AU,3);
            _factor["massvolumedensity Msun/pc3"] = _Msun/pow(_pc,3);

            // opacity
            _factor["opacity m2/kg"] = 1.;

            // energy
            _factor["energy J"] = 1.;

            // bolometric luminosity
            _factor["bolluminosity W"] = 1.;
            _factor["bolluminosity Lsun"] = _Lsun;

            // monochromatic luminosity
            _factor["monluminosity W/m"] = 1.;
            _factor["monluminosity W/micron"] = 1e6;
            _factor["monluminosity Lsun/micron"] = _Lsun * 1e6;

            // neutral flux density (lambda F_lambda = nu F_nu)
            _factor["neutralfluxdensity W/m2"] = 1.;

            // neutral surface brightness (lambda f_lambda = nu f_nu)
            _factor["neutralsurfacebrightness W/m2/sr"] = 1.;
            _factor["neutralsurfacebrightness W/m2/arcsec2"] = 1. / pow(M_PI/(180.*3600.),2);

            // wavelength flux density (F_lambda)
            _factor["wavelengthfluxdensity W/m3"] = 1.;
            _factor["wavelengthfluxdensity W/m2/micron"] = 1e6;

            // wavelength surface brightness (f_lambda)
            _factor["wavelengthsurfacebrightness W/m3/sr"] = 1.;
            _factor["wavelengthsurfacebrightness W/m2/micron/sr"] = 1e6;
            _factor["wavelengthsurfacebrightness W/m2/micron/arcsec2"] = 1e6 / pow(M_PI/(180.*3600.),2);

            // frequency flux density (F_nu)
            _factor["frequencyfluxdensity W/m2/Hz"] = 1.;
            _factor["frequencyfluxdensity Jy"] = 1e-26;
            _factor["frequencyfluxdensity mJy"] = 1e-29;
            _factor["frequencyfluxdensity MJy"] = 1e-20;

            // frequency surface brightness (f_nu)
            _factor["frequencysurfacebrightness W/m2/Hz/sr"] = 1.;
            _factor["frequencysurfacebrightness W/m2/Hz/arcsec2"] = 1. / pow(M_PI/(180.*3600.),2);
            _factor["frequencysurfacebrightness Jy/sr"] = 1e-26;
            _factor["frequencysurfacebrightness Jy/arcsec2"] = 1e-26 / pow(M_PI/(180.*3600.),2);
            _factor["frequencysurfacebrightness MJy/sr"] = 1e-20;
            _factor["frequencysurfacebrightness MJy/arcsec2"] = 1e-20 / pow(M_PI/(180.*3600.),2);

            // temperature
            _factor["temperature K"] = 1.;

            // angular size (for objects in the sky)
            _factor["angle rad"] = 1.;
            _factor["angle deg"] = M_PI/180.;
            _factor["angle arcsec"] = M_PI/(180.*3600.);

            // positioning angle (for instruments)
            _factor["posangle rad"] = 1.;
            _factor["posangle deg"] = M_PI/180.;

            // solid angle
            _factor["solidangle sr"] = 1.;
            _factor["solidangle arcsec2"] = pow(M_PI/(180.*3600.),2);

            // pressure
            _factor["pressure Pa"] = 1.;
            _factor["pressure K/m3"] = _k;

            _initialized = true;
        }
    }
}

////////////////////////////////////////////////////////////////////

Units::Units()
    : _fluxOutputStyle(Neutral)
{
    // initialize static dictionary only if needed (to avoid function call and locking)
    if (!_initialized) initialize();

    // set the unit for dimensionless quantities
    _unitForQty["dimensionless"] = "";
}

////////////////////////////////////////////////////////////////////

void Units::initCache()
{
    _ulength = _unitForQty["length"];
    _udistance = _unitForQty["distance"];
    _uwavelength = _unitForQty["wavelength"];
    _ugrainsize = _unitForQty["grainsize"];
    _usection = _unitForQty["section"];
    _uvolume = _unitForQty["volume"];
    _uvelocity = _unitForQty["velocity"];
    _umass = _unitForQty["mass"];
    _ubulkmass = _unitForQty["bulkmass"];
    _umasssurfacedensity = _unitForQty["masssurfacedensity"];
    _umassvolumedensity = _unitForQty["massvolumedensity"];
    _uopacity = _unitForQty["opacity"];
    _uenergy = _unitForQty["energy"];
    _ubolluminosity = _unitForQty["bolluminosity"];
    _umonluminosity = _unitForQty["monluminosity"];
    _uneutralfluxdensity = _unitForQty["neutralfluxdensity"];
    _uneutralsurfacebrightness = _unitForQty["neutralsurfacebrightness"];
    _uwavelengthfluxdensity = _unitForQty["wavelengthfluxdensity"];
    _uwavelengthsurfacebrightness = _unitForQty["wavelengthsurfacebrightness"];
    _ufrequencyfluxdensity = _unitForQty["frequencyfluxdensity"];
    _ufrequencysurfacebrightness = _unitForQty["frequencysurfacebrightness"];
    _utemperature = _unitForQty["temperature"];
    _uangle = _unitForQty["angle"];
    _uposangle = _unitForQty["posangle"];
    _usolidangle = _unitForQty["solidangle"];
    _upressure = _unitForQty["pressure"];

    _clength = in("length", _ulength);
    _cdistance = in("distance", _udistance);
    _cwavelength = in("wavelength", _uwavelength);
    _cgrainsize = in("grainsize", _ugrainsize);
    _csection = in("section", _usection);
    _cvolume = in("volume", _uvolume);
    _cvelocity = in("velocity", _uvelocity);
    _cmass = in("mass", _umass);
    _cbulkmass = in("bulkmass", _ubulkmass);
    _cmasssurfacedensity = in("masssurfacedensity", _umasssurfacedensity);
    _cmassvolumedensity = in("massvolumedensity", _umassvolumedensity);
    _copacity = in("opacity", _uopacity);
    _cenergy = in("energy", _uenergy);
    _cbolluminosity = in("bolluminosity", _ubolluminosity);
    _cmonluminosity = in("monluminosity", _umonluminosity);
    _cneutralfluxdensity = in("neutralfluxdensity", _uneutralfluxdensity);
    _cneutralsurfacebrightness = in("neutralsurfacebrightness", _uneutralsurfacebrightness);
    _cwavelengthfluxdensity = in("wavelengthfluxdensity", _uwavelengthfluxdensity);
    _cwavelengthsurfacebrightness = in("wavelengthsurfacebrightness", _uwavelengthsurfacebrightness);
    _cfrequencyfluxdensity = in("frequencyfluxdensity", _ufrequencyfluxdensity);
    _cfrequencysurfacebrightness = in("frequencysurfacebrightness", _ufrequencysurfacebrightness);
    _ctemperature = in("temperature", _utemperature);
    _cangle = in("angle", _uangle);
    _cposangle = in("posangle", _uposangle);
    _csolidangle = in("solidangle", _usolidangle);
    _cpressure = in("pressure", _upressure);
}

////////////////////////////////////////////////////////////////////

void Units::setFluxOutputStyle(Units::FluxOutputStyle value)
{
    _fluxOutputStyle = value;
}

////////////////////////////////////////////////////////////////////

Units::FluxOutputStyle Units::fluxOutputStyle() const
{
    return _fluxOutputStyle;
}

////////////////////////////////////////////////////////////////////

double Units::in(QString qty, QString unit, double value)
{
    // initialize static dictionary only if needed (to avoid function call and locking)
    if (!_initialized) initialize();

    double factor = _factor.value(qty + " " + unit, 0.);
    if (factor) return value * factor;
    else throw FATALERROR("Unknow quantity " + qty + " and/or unit " + unit);
}

////////////////////////////////////////////////////////////////////

double Units::out(QString qty, QString unit, double value)
{
    // initialize static dictionary only if needed (to avoid function call and locking)
    if (!_initialized) initialize();

    double factor = _factor.value(qty + " " + unit, 0.);
    if (factor) return value / factor;
    else throw FATALERROR("Unknow quantity " + qty + " and/or unit " + unit);
}

////////////////////////////////////////////////////////////////////

QStringList Units::units(QString qty)
{
    // initialize static dictionary only if needed (to avoid function call and locking)
    if (!_initialized) initialize();

    QStringList result;
    foreach (QString qty_unit, _factor.keys())
    {
        QStringList segments = qty_unit.split(" ");
        if (segments.size() == 2 && segments[0] == qty) result << segments[1];
    }
    result.sort();
    return result;
}

////////////////////////////////////////////////////////////////////

bool Units::isQuantity(QString qty) const
{
    return _unitForQty.contains(qty);
}

////////////////////////////////////////////////////////////////////

QString Units::unit(QString qty) const
{
    // Check whether the given quantity is either surface brightness or flux density; in those cases
    // appropriate functions are called to return the corresponding units for the current flux output style
    QString result;
    if (qty == "surfacebrightness") result = usurfacebrightness();
    else if (qty == "fluxdensity") result = ufluxdensity();
    else result = _unitForQty.value(qty, QString("?"));

    // Verify and return the resulting unit string
    if (result == "?") throw FATALERROR("Unknow quantity " + qty);
    return result;
}

////////////////////////////////////////////////////////////////////

double Units::in(QString qty, double value) const
{
    return in(qty, _unitForQty.value(qty), value);
}

////////////////////////////////////////////////////////////////////

double Units::out(QString qty, double value) const
{
    return out(qty, _unitForQty.value(qty), value);
}

////////////////////////////////////////////////////////////////////

double Units::c()
{
    return _c;
}

////////////////////////////////////////////////////////////////////

double Units::h()
{
    return _h;
}

////////////////////////////////////////////////////////////////////

double Units::k()
{
    return _k;
}

////////////////////////////////////////////////////////////////////

double Units::NA()
{
    return _NA;
}

////////////////////////////////////////////////////////////////////

double Units::AU()
{
    return _AU;
}

////////////////////////////////////////////////////////////////////

double Units::pc()
{
    return _pc;
}

////////////////////////////////////////////////////////////////////

double Units::massproton()
{
    return _Mproton;
}

////////////////////////////////////////////////////////////////////

double Units::masselectron()
{
    return _Melectron;
}

////////////////////////////////////////////////////////////////////

double Units::Msun()
{
    return _Msun;
}

////////////////////////////////////////////////////////////////////

double Units::Lsun()
{
    return _Lsun;
}

////////////////////////////////////////////////////////////////////

double Units::lambdaV()
{
    return _lambdaV;
}

////////////////////////////////////////////////////////////////////

double Units::kappaV()
{
    return _kappaV;
}

////////////////////////////////////////////////////////////////////

double Units::sigmaThomson()
{
    return _sigmaThomson;
}

////////////////////////////////////////////////////////////////////

QString Units::ulength() const
{
    return _ulength;
}

////////////////////////////////////////////////////////////////////

double Units::ilength(double x) const
{
    return x*_clength;
}

////////////////////////////////////////////////////////////////////

double Units::olength(double x) const
{
    return x/_clength;
}

////////////////////////////////////////////////////////////////////

QString Units::udistance() const
{
    return _udistance;
}

////////////////////////////////////////////////////////////////////

double Units::idistance(double d) const
{
    return d*_cdistance;
}

////////////////////////////////////////////////////////////////////

double Units::odistance(double d) const
{
    return d/_cdistance;
}

////////////////////////////////////////////////////////////////////

QString Units::uwavelength() const
{
    return _uwavelength;
}

////////////////////////////////////////////////////////////////////

double Units::iwavelength(double lambda) const
{
    return lambda*_cwavelength;
}

////////////////////////////////////////////////////////////////////

double Units::owavelength(double lambda) const
{
    return lambda/_cwavelength;
}

////////////////////////////////////////////////////////////////////

QString Units::ugrainsize() const
{
    return _ugrainsize;
}

////////////////////////////////////////////////////////////////////

double Units::igrainsize(double a) const
{
    return a*_cgrainsize;
}

////////////////////////////////////////////////////////////////////

double Units::ograinsize(double a) const
{
    return a/_cgrainsize;
}

////////////////////////////////////////////////////////////////////

QString Units::usection() const
{
    return _usection;
}

////////////////////////////////////////////////////////////////////

double Units::isection(double C) const
{
    return C*_csection;
}

////////////////////////////////////////////////////////////////////

double Units::osection(double C) const
{
    return C/_csection;
}

////////////////////////////////////////////////////////////////////

QString Units::uvolume() const
{
    return _uvolume;
}

////////////////////////////////////////////////////////////////////

double Units::ivolume(double V) const
{
    return V*_cvolume;
}

////////////////////////////////////////////////////////////////////

double Units::ovolume(double V) const
{
    return V/_cvolume;
}

////////////////////////////////////////////////////////////////////

QString Units::uvelocity() const
{
    return _uvelocity;
}

////////////////////////////////////////////////////////////////////

double Units::ivelocity(double v) const
{
    return v*_cvelocity;
}

////////////////////////////////////////////////////////////////////

double Units::ovelocity(double v) const
{
    return v/_cvelocity;
}

////////////////////////////////////////////////////////////////////

QString Units::umass() const
{
    return _umass;
}

////////////////////////////////////////////////////////////////////

double Units::imass(double M) const
{
    return M*_cmass;
}

////////////////////////////////////////////////////////////////////

double Units::omass(double M) const
{
    return M/_cmass;
}

////////////////////////////////////////////////////////////////////

QString Units::ubulkmass() const
{
    return _ubulkmass;
}

////////////////////////////////////////////////////////////////////

double Units::ibulkmass(double mu) const
{
    return mu*_cbulkmass;
}

////////////////////////////////////////////////////////////////////

double Units::obulkmass(double mu) const
{
    return mu/_cbulkmass;
}

////////////////////////////////////////////////////////////////////

QString Units::umasssurfacedensity() const
{
    return _umasssurfacedensity;
}

////////////////////////////////////////////////////////////////////

double Units::imasssurfacedensity(double Sigma) const
{
    return Sigma*_cmasssurfacedensity;
}

////////////////////////////////////////////////////////////////////

double Units::omasssurfacedensity(double Sigma) const
{
    return Sigma/_cmasssurfacedensity;
}

////////////////////////////////////////////////////////////////////

QString Units::umassvolumedensity() const
{
    return _umassvolumedensity;
}

////////////////////////////////////////////////////////////////////

double Units::imassvolumedensity(double rho) const
{
    return rho*_cmassvolumedensity;
}

////////////////////////////////////////////////////////////////////

double Units::omassvolumedensity(double rho) const
{
    return rho/_cmassvolumedensity;
}

////////////////////////////////////////////////////////////////////

QString Units::uopacity() const
{
    return _uopacity;
}

////////////////////////////////////////////////////////////////////

double Units::iopacity(double kappa) const
{
    return kappa*_copacity;
}

////////////////////////////////////////////////////////////////////

double Units::oopacity(double kappa) const
{
    return kappa/_copacity;
}

////////////////////////////////////////////////////////////////////

QString Units::uenergy() const
{
    return _uenergy;
}

////////////////////////////////////////////////////////////////////

double Units::ienergy(double E) const
{
    return E*_cenergy;
}

////////////////////////////////////////////////////////////////////

double Units::oenergy(double E) const
{
    return E/_cenergy;
}

////////////////////////////////////////////////////////////////////

QString Units::ubolluminosity() const
{
    return _ubolluminosity;
}

////////////////////////////////////////////////////////////////////

double Units::ibolluminosity(double L) const
{
    return L*_cbolluminosity;
}

////////////////////////////////////////////////////////////////////

double Units::obolluminosity(double L) const
{
    return L/_cbolluminosity;
}

////////////////////////////////////////////////////////////////////

QString Units::umonluminosity() const
{
    return _umonluminosity;
}

////////////////////////////////////////////////////////////////////

double Units::imonluminosity(double Llambda) const
{
    return Llambda*_cmonluminosity;
}

////////////////////////////////////////////////////////////////////

double Units::omonluminosity(double Llambda) const
{
    return Llambda/_cmonluminosity;
}

////////////////////////////////////////////////////////////////////

QString Units::uneutralfluxdensity() const
{
    return _uneutralfluxdensity;
}

////////////////////////////////////////////////////////////////////

double Units::ineutralfluxdensity(double lambdaFlambda) const
{
    return lambdaFlambda*_cneutralfluxdensity;
}

////////////////////////////////////////////////////////////////////

double Units::oneutralfluxdensity(double lambdaFlambda) const
{
    return lambdaFlambda/_cneutralfluxdensity;
}

////////////////////////////////////////////////////////////////////

QString Units::uneutralsurfacebrightness() const
{
    return _uneutralsurfacebrightness;
}

////////////////////////////////////////////////////////////////////

double Units::ineutralsurfacebrightness(double lambdaflambda) const
{
    return lambdaflambda*_cneutralsurfacebrightness;
}

////////////////////////////////////////////////////////////////////

double Units::oneutralsurfacebrightness(double lambdaflambda) const
{
    return lambdaflambda/_cneutralsurfacebrightness;
}

////////////////////////////////////////////////////////////////////

QString Units::uwavelengthfluxdensity() const
{
    return _uwavelengthfluxdensity;
}

////////////////////////////////////////////////////////////////////

double Units::iwavelengthfluxdensity(double Flambda) const
{
    return Flambda*_cwavelengthfluxdensity;
}

////////////////////////////////////////////////////////////////////

double Units::owavelengthfluxdensity(double Flambda) const
{
    return Flambda/_cwavelengthfluxdensity;
}

////////////////////////////////////////////////////////////////////

QString Units::uwavelengthsurfacebrightness() const
{
    return _uwavelengthsurfacebrightness;
}

////////////////////////////////////////////////////////////////////

double Units::iwavelengthsurfacebrightness(double flambda) const
{
    return flambda*_cwavelengthsurfacebrightness;
}

////////////////////////////////////////////////////////////////////

double Units::owavelengthsurfacebrightness(double flambda) const
{
    return flambda/_cwavelengthsurfacebrightness;
}

////////////////////////////////////////////////////////////////////

QString Units::ufrequencyfluxdensity() const
{
    return _ufrequencyfluxdensity;
}

////////////////////////////////////////////////////////////////////

double Units::ifrequencyfluxdensity(double Fnu) const
{
    return Fnu*_cfrequencyfluxdensity;
}

////////////////////////////////////////////////////////////////////

double Units::ofrequencyfluxdensity(double Fnu) const
{
    return Fnu/_cfrequencyfluxdensity;
}

////////////////////////////////////////////////////////////////////

QString Units::ufrequencysurfacebrightness() const
{
    return _ufrequencysurfacebrightness;
}

////////////////////////////////////////////////////////////////////

double Units::ifrequencysurfacebrightness(double fnu) const
{
    return fnu*_cfrequencysurfacebrightness;
}

////////////////////////////////////////////////////////////////////

double Units::ofrequencysurfacebrightness(double fnu) const
{
    return fnu/_cfrequencysurfacebrightness;
}

////////////////////////////////////////////////////////////////////

QString Units::utemperature() const
{
    return _utemperature;
}

////////////////////////////////////////////////////////////////////

double Units::itemperature(double T) const
{
    return T*_ctemperature;
}

////////////////////////////////////////////////////////////////////

double Units::otemperature(double T) const
{
    return T/_ctemperature;
}

////////////////////////////////////////////////////////////////////

QString Units::uangle() const
{
    return _uangle;
}

////////////////////////////////////////////////////////////////////

double Units::iangle(double theta) const
{
    return theta*_cangle;
}

////////////////////////////////////////////////////////////////////

double Units::oangle(double theta) const
{
    return theta/_cangle;
}

////////////////////////////////////////////////////////////////////

QString Units::usolidangle() const
{
    return _usolidangle;
}

////////////////////////////////////////////////////////////////////

double Units::isolidangle(double Omega) const
{
    return Omega*_csolidangle;
}

////////////////////////////////////////////////////////////////////

double Units::osolidangle(double Omega) const
{
    return Omega/_csolidangle;
}

////////////////////////////////////////////////////////////////////

QString Units::upressure() const
{
    return _upressure;
}

////////////////////////////////////////////////////////////////////

double Units::ipressure(double p) const
{
    return p*_cpressure;
}

////////////////////////////////////////////////////////////////////

double Units::opressure(double p) const
{
    return p/_cpressure;
}

////////////////////////////////////////////////////////////////////

QString Units::sfluxdensity() const
{
    switch (_fluxOutputStyle)
    {
    case Wavelength: return "F_lambda";
    case Frequency:  return "F_nu";
    default:         return "lambda*F_lambda";
    }
}

////////////////////////////////////////////////////////////////////

QString Units::ufluxdensity() const
{
    switch (_fluxOutputStyle)
    {
    case Wavelength: return uwavelengthfluxdensity();
    case Frequency:  return ufrequencyfluxdensity();
    default:         return uneutralfluxdensity();
    }
}

////////////////////////////////////////////////////////////////////

double Units::ofluxdensity(double lambda, double Flambda) const
{
    switch (_fluxOutputStyle)
    {
    case Wavelength: return owavelengthfluxdensity(Flambda);
    case Frequency:  return ofrequencyfluxdensity(lambda*lambda*Flambda/_c);
    default:         return oneutralfluxdensity(lambda*Flambda);
    }
}

////////////////////////////////////////////////////////////////////

QString Units::ssurfacebrightness() const
{
    switch (_fluxOutputStyle)
    {
    case Wavelength: return "f_lambda";
    case Frequency:  return "f_nu";
    default:         return "lambda*f_lambda";
    }
}

////////////////////////////////////////////////////////////////////

QString Units::usurfacebrightness() const
{
    switch (_fluxOutputStyle)
    {
    case Wavelength: return uwavelengthsurfacebrightness();
    case Frequency:  return ufrequencysurfacebrightness();
    default:         return uneutralsurfacebrightness();
    }
}

////////////////////////////////////////////////////////////////////

double Units::osurfacebrightness(double lambda, double flambda) const
{
    switch (_fluxOutputStyle)
    {
    case Wavelength: return owavelengthsurfacebrightness(flambda);
    case Frequency:  return ofrequencysurfacebrightness(lambda*lambda*flambda/_c);
    default:         return oneutralsurfacebrightness(lambda*flambda);
    }
}

////////////////////////////////////////////////////////////////////
