/*//////////////////////////////////////////////////////////////////
////       SKIRT -- an advanced radiative transfer code         ////
////       © Astronomical Observatory, Ghent University         ////
///////////////////////////////////////////////////////////////// */

#ifndef DRAINEIONIZEDPAHGRAINCOMPOSITION_HPP
#define DRAINEIONIZEDPAHGRAINCOMPOSITION_HPP

#include "GrainComposition.hpp"

////////////////////////////////////////////////////////////////////

/** The DraineIonizedPAHGrainComposition class represents the optical and calorimetric properties of
    ionized PAH dust grains. The optical properties are taken from Bruce Draine's website, the
    calorimetric properties follow the prescription of Draine & Li (2001). */
class DraineIonizedPAHGrainComposition : public GrainComposition
{
    Q_OBJECT
    Q_CLASSINFO("Title", "a Draine ionized PAH dust grains composition")

    //============= Construction - Setup - Destruction =============

public:
    /** The default constructor. */
    Q_INVOKABLE DraineIonizedPAHGrainComposition();

    /** This constructor can be invoked by dust mix classes that wish to hard-code the creation of
        a new grain composition object of this type (as opposed to creation through the ski file).
        Before the constructor returns, the newly created object is hooked up as a child to the
        specified parent in the simulation hierarchy (so it will automatically be deleted), and
        its setup() function has been called. */
    explicit DraineIonizedPAHGrainComposition(SimulationItem* parent);

protected:
    /** This function reads the raw optical property data from a resource file, calculates the
        enthalpy data using the analytical function for graphite derived in Draine & Li 2001 (for
        lack of a better alternative), and sets the bulk mass density to the standard value of 2240
        kg m\f$^{-3}\f$ for graphite grains. */
    void setupSelfBefore();

    //====================== Identifying =====================

public:
    /** This function returns a brief human-readable identifier for the type of grain composition
        represented by the instance. */
    QString name() const;
};

////////////////////////////////////////////////////////////////////

#endif // DRAINEIONIZEDPAHGRAINCOMPOSITION_HPP
