/*//////////////////////////////////////////////////////////////////
////       SKIRT -- an advanced radiative transfer code         ////
////       © Astronomical Observatory, Ghent University         ////
///////////////////////////////////////////////////////////////// */

#ifndef VORONOISTELLARCOMP_HPP
#define VORONOISTELLARCOMP_HPP

#include "ArrayTable.hpp"
#include "BoxStellarComp.hpp"
class VoronoiMesh;
class VoronoiMeshFile;
class Random;

//////////////////////////////////////////////////////////////////////

/** The VoronoiStellarComp class represents a stellar component defined by the stellar density and
    properties imported from a Voronoi mesh data file. The data file must have one of the supported
    formats; refer to the VoronoiMeshFile class and its subclasses. The VoronoiStellarComp class
    allows selecting the data columns respectively containing the initial stellar density
    \f$\rho\f$ (in \f$M_\odot\,\text{pc}^{-3}\f$ at \f$t=0\f$), the metallicity \f$Z\f$ of the
    stellar population (dimensionless fraction), and the age of the stellar population (in yr).
    Since the Voronoi mesh data format does not specify the size of the domain, this information
    must be provided as properties of this class as well. */
class VoronoiStellarComp : public BoxStellarComp
{
    Q_OBJECT
    Q_CLASSINFO("Title", "a stellar component imported from a Voronoi mesh data file")

    Q_CLASSINFO("Property", "voronoiMeshFile")
    Q_CLASSINFO("Title", "the Voronoi mesh data file")
    Q_CLASSINFO("Default", "VoronoiMeshAsciiFile")

    Q_CLASSINFO("Property", "densityIndex")
    Q_CLASSINFO("Title", "the index of the column defining the stellar density distribution")
    Q_CLASSINFO("MinValue", "0")
    Q_CLASSINFO("MaxValue", "99")
    Q_CLASSINFO("Default", "0")

    Q_CLASSINFO("Property", "metallicityIndex")
    Q_CLASSINFO("Title", "the index of the column defining the metallicity of the stellar population")
    Q_CLASSINFO("MinValue", "0")
    Q_CLASSINFO("MaxValue", "99")
    Q_CLASSINFO("Default", "1")

    Q_CLASSINFO("Property", "ageIndex")
    Q_CLASSINFO("Title", "the index of the column defining the age of the stellar population")
    Q_CLASSINFO("MinValue", "0")
    Q_CLASSINFO("MaxValue", "99")
    Q_CLASSINFO("Default", "2")

    //============= Construction - Setup - Destruction =============

public:
    /** The default constructor. */
    Q_INVOKABLE VoronoiStellarComp();

    /** The destructor releases the data structure allocated during setup. */
    ~VoronoiStellarComp();

protected:
    /** This function verifies the property values, imports the Voronoi mesh data, and calculates
        the luminosity \f$L_{\ell,m}\f$ for each mesh cell \f$m\f$ and at each wavelength grid
        point \f$\ell\f$. The luminosity distribution in each cell is determined using bilinear
        interpolation on age and metallicity in the family of Bruzual & Charlot SEDs (read from the
        appropriate resource files). These cell-specific SEDs are resampled on the simulation's
        global wavelength grid. Summing over all cells, a vector with the total luminosity for each
        wavelength bin is constructed. Finally, a matrix \f$X_{\ell,m}\f$ is filled that contains
        the normalized cumulative luminosity, \f[ X_{\ell,m} = \frac{ \sum_{i=0}^{m-1} L_{\ell,i}
        }{ \sum_{i=0}^{N-1} L_{\ell,i} } \f] where \f$N\f$ is the total number of mesh cells. This
        matrix will be used for the efficient generation of random photon packages from the stellar
        component. */
    void setupSelfBefore();

    //======== Setters & Getters for Discoverable Attributes =======

public:
    /** Sets the file containing the Voronoi mesh data that defines this stellar component. */
    Q_INVOKABLE void setVoronoiMeshFile(VoronoiMeshFile* value);

    /** Returns the file containing the Voronoi mesh data that defines this stellar component. */
    Q_INVOKABLE VoronoiMeshFile* voronoiMeshFile() const;

    /** Sets the index of the column in the data file that defines the initial stellar density
        \f$\rho\f$ for this stellar component, in \f$M_\odot\,\text{pc}^{-3}\f$ at \f$t=0\f$. */
    Q_INVOKABLE void setDensityIndex(int value);

    /** Returns the index of the column in the data file that defines the stellar density
        \f$\rho\f$ for this stellar component. */
    Q_INVOKABLE int densityIndex() const;

    /** Sets the index of the column in the data file that defines the metallicity \f$Z\f$ of the
        stellar population for this stellar component, as a dimensionless fraction. */
    Q_INVOKABLE void setMetallicityIndex(int value);

    /** Returns the index of the column in the data file that defines the metallicity \f$Z\f$ of
        the stellar population for this stellar component. */
    Q_INVOKABLE int metallicityIndex() const;

    /** Sets the index of the column in the data file that defines the age of the stellar
        population for this stellar component, in years. */
    Q_INVOKABLE void setAgeIndex(int value);

    /** Returns the index of the column in the data file that defines the age of the stellar
        population for this stellar component. */
    Q_INVOKABLE int ageIndex() const;

    //======================== Other Functions =======================

public:
    /** This function returns the monochromatic luminosity \f$L_\ell\f$ of the stellar component at
        the wavelength index \f$\ell\f$. It just reads the appropriate number from the internally
        stored vector. */
    double luminosity(int ell) const;

    /** This function simulates the emission of a monochromatic photon package with a monochromatic
        luminosity \f$L\f$ at wavelength index \f$\ell\f$ from the stellar component. It randomly
        chooses a mesh cell from the normalized cumulative luminosity matrix defined in the setup
        phase and stored internally. Once the cell has been determined, a position is determined
        randomly within the cell boundaries. */
    void launch(PhotonPackage* pp, int ell, double L) const;

    //======================== Data Members ========================

private:
    // discoverable attributes
    VoronoiMeshFile* _meshfile;
    int _densityIndex;
    int _metallicityIndex;
    int _ageIndex;

    // other data members
    Random* _random;
    VoronoiMesh* _mesh;
    Array _Ltotv;
    ArrayTable<2> _Xvv;
};

////////////////////////////////////////////////////////////////////

#endif // VORONOISTELLARCOMP_HPP
