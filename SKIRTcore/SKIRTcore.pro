#-------------------------------------------------
#  SKIRT -- an advanced radiative transfer code
#  © Astronomical Observatory, Ghent University
#-------------------------------------------------

#---------------------------------------------------------------------
# This library provides the core SKIRT functionality, including all
# simulation item classes plus some SKIRT-specific support classes.
#---------------------------------------------------------------------

# overall setup
TEMPLATE = lib
TARGET = skirtcore
QT -= gui
CONFIG *= staticlib create_prl thread c++11

# compile with maximum optimization
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -O3

# include libraries internal to the project
INCLUDEPATH += $$PWD/../Fundamentals $$PWD/../Cfitsio $$PWD/../Voro $$PWD/../MPIsupport
DEPENDPATH += $$PWD/../Fundamentals $$PWD/../Cfitsio $$PWD/../Voro $$PWD/../MPIsupport
unix: LIBS += -L$$OUT_PWD/../Fundamentals/ -lfundamentals \
              -L$$OUT_PWD/../Cfitsio/ -lcfitsio \
              -L$$OUT_PWD/../Voro/ -lvoro \
              -L$$OUT_PWD/../MPIsupport/ -lmpisupport
unix: PRE_TARGETDEPS += $$OUT_PWD/../Fundamentals/libfundamentals.a \
                        $$OUT_PWD/../Cfitsio/libcfitsio.a \
                        $$OUT_PWD/../Voro/libvoro.a \
                        $$OUT_PWD/../MPIsupport/libmpisupport.a

#--------------------------------------------------
# source and header files: maintained by Qt creator
#--------------------------------------------------

HEADERS += \
    AdaptiveMesh.hpp \
    AdaptiveMeshAmrvacFile.hpp \
    AdaptiveMeshAsciiFile.hpp \
    AdaptiveMeshDustDistribution.hpp \
    AdaptiveMeshDustGridStructure.hpp \
    AdaptiveMeshFile.hpp \
    AdaptiveMeshGeometry.hpp \
    AdaptiveMeshInterface.hpp \
    AdaptiveMeshNode.hpp \
    AllCellsDustLib.hpp \
    AngularDistribution.hpp \
    AxDustGridStructure.hpp \
    AxGeometry.hpp \
    AxSpheDustGridStructure.hpp \
    BaryBinTreeNode.hpp \
    BaryOctTreeNode.hpp \
    Benchmark1DDustMix.hpp \
    Benchmark2DDustMix.hpp \
    BinTreeDustGridStructure.hpp \
    BinTreeNode.hpp \
    BlackBodySED.hpp \
    BolLuminosityStellarCompNormalization.hpp \
    BruzualCharlotSED.hpp \
    BruzualCharlotSEDFamily.hpp \
    CompDustDistribution.hpp \
    ConfigurableDustMix.hpp \
    Console.hpp \
    CubDustGridStructure.hpp \
    CubicSplineSmoothingKernel.hpp \
    Dim1DustLib.hpp \
    Dim2DustLib.hpp \
    Direction.hpp \
    DistantInstrument.hpp \
    DraineGraphiteGrainComposition.hpp \
    DraineIonizedPAHGrainComposition.hpp \
    DraineLiDustMix.hpp \
    DraineNeutralPAHGrainComposition.hpp \
    DraineSilicateGrainComposition.hpp \
    DustComp.hpp \
    DustCompNormalization.hpp \
    DustDistribution.hpp \
    DustEmGrainComposition.hpp \
    DustEmissivity.hpp \
    DustGridDensityInterface.hpp \
    DustGridPath.hpp \
    DustGridPlotFile.hpp \
    DustGridStructure.hpp \
    DustLib.hpp \
    DustMassDustCompNormalization.hpp \
    DustMassInBoxInterface.hpp \
    DustMix.hpp \
    DustMixPopulation.hpp \
    DustParticleInterface.hpp \
    DustSystem.hpp \
    DustSystemDensityCalculator.hpp \
    DustSystemDepthCalculator.hpp \
    EdgeOnDustCompNormalization.hpp \
    EinastoGeometry.hpp \
    ExpDiskGeometry.hpp \
    ExtragalacticUnits.hpp \
    FITSInOut.hpp \
    FaceOnDustCompNormalization.hpp \
    FatalError.hpp \
    FileLog.hpp \
    FilePaths.hpp \
    FileSED.hpp \
    FileWavelengthGrid.hpp \
    Foam.hpp \
    FoamAxGeometry.hpp \
    FoamCell.hpp \
    FoamDensity.hpp \
    FoamGeometry.hpp \
    FoamHistogram.hpp \
    FoamMatrix.hpp \
    FoamPartition.hpp \
    FoamVector.hpp \
    FrameInstrument.hpp \
    FullInstrument.hpp \
    GammaGeometry.hpp \
    GaussianGeometry.hpp \
    GenDustGridStructure.hpp \
    GenGeometry.hpp \
    GenLinCubDustGridStructure.hpp \
    Geometry.hpp \
    GrainComposition.hpp \
    GrainSizeDistribution.hpp \
    GrainSizeDistributionInterface.hpp \
    GreyBodyDustEmissivity.hpp \
    HomogeneousTransform.hpp \
    ISRF.hpp \
    Instrument.hpp \
    InstrumentFrame.hpp \
    InstrumentSystem.hpp \
    InterstellarDustMix.hpp \
    KuruczSED.hpp \
    LinAxDustGridStructure.hpp \
    LinCubDustGridStructure.hpp \
    LinSpheDustGridStructure.hpp \
    Log.hpp \
    LogLinAxDustGridStructure.hpp \
    LogLinAxSpheDustGridStructure.hpp \
    LogNormalGrainSizeDistribution.hpp \
    LogPowAxDustGridStructure.hpp \
    LogSpheDustGridStructure.hpp \
    LogWavelengthGrid.hpp \
    LuminosityStellarCompNormalization.hpp \
    MGEGeometry.hpp \
    MRNDustMix.hpp \
    MappingsSED.hpp \
    MappingsSEDFamily.hpp \
    MarastonSED.hpp \
    MeanZubkoDustMix.hpp \
    MeshDustComponent.hpp \
    MieSilicateGrainComposition.hpp \
    ModifiedLogNormalGrainSizeDistribution.hpp \
    ModifiedPowerLawGrainSizeDistribution.hpp \
    MonteCarloSimulation.hpp \
    MultiFrameInstrument.hpp \
    MultiGrainDustMix.hpp \
    NestedLogWavelengthGrid.hpp \
    NetzerAccretionDiskGeometry.hpp \
    OctTreeDustGridStructure.hpp \
    OctTreeNode.hpp \
    OligoDustSystem.hpp \
    OligoMonteCarloSimulation.hpp \
    OligoStellarComp.hpp \
    OligoWavelengthGrid.hpp \
    PanDustSystem.hpp \
    PanMonteCarloSimulation.hpp \
    PanStellarComp.hpp \
    PanWavelengthGrid.hpp \
    Parallel.hpp \
    ParallelFactory.hpp \
    ParallelTarget.hpp \
    ParticleTreeDustGridStructure.hpp \
    PegaseSED.hpp \
    PerspectiveInstrument.hpp \
    PhotonPackage.hpp \
    PlanckFunction.hpp \
    PlummerGeometry.hpp \
    PointGeometry.hpp \
    Position.hpp \
    PowAxDustGridStructure.hpp \
    PowCubDustGridStructure.hpp \
    PowSpheDustGridStructure.hpp \
    PowerLawGrainSizeDistribution.hpp \
    PseudoSersicGeometry.hpp \
    QuasarSED.hpp \
    RadialDustCompNormalization.hpp \
    Random.hpp \
    RingGeometry.hpp \
    SED.hpp \
    SEDInstrument.hpp \
    SIUnits.hpp \
    SPHDustDistribution.hpp \
    SPHGasParticle.hpp \
    SPHGasParticleGrid.hpp \
    SepAxGeometry.hpp \
    SersicFunction.hpp \
    SersicGeometry.hpp \
    ShellGeometry.hpp \
    SignalHandler.hpp \
    SimpleInstrument.hpp \
    Simulation.hpp \
    SimulationItem.hpp \
    SingleFrameInstrument.hpp \
    SmoothingKernel.hpp \
    SpecialFunctions.hpp \
    SpheDustGridStructure.hpp \
    SpheGeometry.hpp \
    StarburstSED.hpp \
    StellarComp.hpp \
    StellarCompNormalization.hpp \
    StellarSED.hpp \
    StellarSystem.hpp \
    StellarUnits.hpp \
    StopWatch.hpp \
    SunSED.hpp \
    TTauriDiskGeometry.hpp \
    TimeLogger.hpp \
    TorusGeometry.hpp \
    TransientDustEmissivity.hpp \
    TreeDustGridStructure.hpp \
    TreeNode.hpp \
    TreeNodeBoxDensityCalculator.hpp \
    TreeNodeDensityCalculator.hpp \
    TreeNodeSampleDensityCalculator.hpp \
    Trust1Geometry.hpp \
    Trust6Geometry.hpp \
    Trust7aGeometry.hpp \
    Trust7bGeometry.hpp \
    TrustDustMix.hpp \
    TrustGraphiteGrainComposition.hpp \
    TrustMeanDustMix.hpp \
    TrustNeutralPAHGrainComposition.hpp \
    TrustSilicateGrainComposition.hpp \
    TwoPhaseDustGridStructure.hpp \
    UniformCuboidGeometry.hpp \
    UniformSmoothingKernel.hpp \
    Units.hpp \
    VoronoiDustDistribution.hpp \
    VoronoiDustGridStructure.hpp \
    VoronoiGeometry.hpp \
    VoronoiMesh.hpp \
    VoronoiMeshAsciiFile.hpp \
    VoronoiMeshFile.hpp \
    VoronoiMeshInterface.hpp \
    WavelengthGrid.hpp \
    WeingartnerDraineDustMix.hpp \
    XDustCompNormalization.hpp \
    YDustCompNormalization.hpp \
    ZDustCompNormalization.hpp \
    ZubkoDustMix.hpp \
    ZubkoSilicateGrainSizeDistribution.hpp \
    ZubkoGraphiteGrainSizeDistribution.hpp \
    ZubkoPAHGrainSizeDistribution.hpp \
    MinSilicateGrainComposition.hpp \
    ForsteriteGrainComposition.hpp \
    EnstatiteGrainComposition.hpp \
    GeometricStellarComp.hpp \
    SPHStellarComp.hpp \
    VoronoiStellarComp.hpp \
    AdaptiveMeshStellarComp.hpp \
    FileGrainComposition.hpp \
    StellarSurfaceGeometry.hpp \
    RangeGrainSizeDistribution.hpp \
    SingleGrainSizeDistribution.hpp \
    Trust2Geometry.hpp \
    SolarPatchGeometry.hpp \
    ProcessCommunicator.hpp \
    PeerToPeerCommunicator.hpp \
    MasterSlaveCommunicator.hpp \
    ProcessAssigner.hpp \
    IdenticalAssigner.hpp \
    StaggeredAssigner.hpp \
    SequentialAssigner.hpp \
    SPHGeometry.hpp \
    StokesVector.hpp \
    PolarizedSilicateGrainComposition.hpp \
    PolarizedGraphiteGrainComposition.hpp \
    ReadFitsGeometry.hpp \
    AmHydrocarbonGrainComposition.hpp \
    OffsetGeometryDecorator.hpp \
    RotateGeometryDecorator.hpp \
    SpheroidalGeometryDecorator.hpp \
    TriaxialGeometryDecorator.hpp \
    SphericalCavityGeometryDecorator.hpp \
    SpiralStructureGeometryDecorator.hpp \
    ClumpyGeometryDecorator.hpp \
    FoamGeometryDecorator.hpp \
    CombineGeometryDecorator.hpp \
    CropGeometryDecorator.hpp \
    LaserGeometry.hpp \
    ElectronDustMix.hpp \
    CubBackgroundGeometry.hpp \
    SpheBackgroundGeometry.hpp \
    SpectralLuminosityStellarCompNormalization.hpp \
    RootAssigner.hpp \
    RandomAssigner.hpp \
    TextOutFile.hpp \
    Image.hpp \
    SphericalAdaptiveMesh.hpp \
    SphericalAdaptiveMeshDustDistribution.hpp \
    TextInFile.hpp \
    SEDFamily.hpp \
    CylindricalCavityGeometryDecorator.hpp \
    ConicalShellGeometry.hpp

SOURCES += \
    AdaptiveMesh.cpp \
    AdaptiveMeshAmrvacFile.cpp \
    AdaptiveMeshAsciiFile.cpp \
    AdaptiveMeshDustDistribution.cpp \
    AdaptiveMeshDustGridStructure.cpp \
    AdaptiveMeshFile.cpp \
    AdaptiveMeshGeometry.cpp \
    AdaptiveMeshNode.cpp \
    AllCellsDustLib.cpp \
    AxDustGridStructure.cpp \
    AxGeometry.cpp \
    AxSpheDustGridStructure.cpp \
    BaryBinTreeNode.cpp \
    BaryOctTreeNode.cpp \
    Benchmark1DDustMix.cpp \
    Benchmark2DDustMix.cpp \
    BinTreeDustGridStructure.cpp \
    BinTreeNode.cpp \
    BlackBodySED.cpp \
    BolLuminosityStellarCompNormalization.cpp \
    BruzualCharlotSED.cpp \
    BruzualCharlotSEDFamily.cpp \
    CompDustDistribution.cpp \
    ConfigurableDustMix.cpp \
    Console.cpp \
    CubDustGridStructure.cpp \
    CubicSplineSmoothingKernel.cpp \
    Dim1DustLib.cpp \
    Dim2DustLib.cpp \
    Direction.cpp \
    DistantInstrument.cpp \
    DraineGraphiteGrainComposition.cpp \
    DraineIonizedPAHGrainComposition.cpp \
    DraineLiDustMix.cpp \
    DraineNeutralPAHGrainComposition.cpp \
    DraineSilicateGrainComposition.cpp \
    DustComp.cpp \
    DustCompNormalization.cpp \
    DustDistribution.cpp \
    DustEmGrainComposition.cpp \
    DustEmissivity.cpp \
    DustGridPath.cpp \
    DustGridPlotFile.cpp \
    DustGridStructure.cpp \
    DustLib.cpp \
    DustMassDustCompNormalization.cpp \
    DustMix.cpp \
    DustMixPopulation.cpp \
    DustSystem.cpp \
    DustSystemDensityCalculator.cpp \
    DustSystemDepthCalculator.cpp \
    EdgeOnDustCompNormalization.cpp \
    EinastoGeometry.cpp \
    ExpDiskGeometry.cpp \
    ExtragalacticUnits.cpp \
    FITSInOut.cpp \
    FaceOnDustCompNormalization.cpp \
    FatalError.cpp \
    FileLog.cpp \
    FilePaths.cpp \
    FileSED.cpp \
    FileWavelengthGrid.cpp \
    Foam.cpp \
    FoamAxGeometry.cpp \
    FoamCell.cpp \
    FoamGeometry.cpp \
    FoamHistogram.cpp \
    FoamMatrix.cpp \
    FoamPartition.cpp \
    FoamVector.cpp \
    FrameInstrument.cpp \
    FullInstrument.cpp \
    GammaGeometry.cpp \
    GaussianGeometry.cpp \
    GenDustGridStructure.cpp \
    GenGeometry.cpp \
    GenLinCubDustGridStructure.cpp \
    Geometry.cpp \
    GrainComposition.cpp \
    GrainSizeDistribution.cpp \
    GreyBodyDustEmissivity.cpp \
    HomogeneousTransform.cpp \
    ISRF.cpp \
    Instrument.cpp \
    InstrumentFrame.cpp \
    InstrumentSystem.cpp \
    InterstellarDustMix.cpp \
    KuruczSED.cpp \
    LinAxDustGridStructure.cpp \
    LinCubDustGridStructure.cpp \
    LinSpheDustGridStructure.cpp \
    Log.cpp \
    LogLinAxDustGridStructure.cpp \
    LogLinAxSpheDustGridStructure.cpp \
    LogNormalGrainSizeDistribution.cpp \
    LogPowAxDustGridStructure.cpp \
    LogSpheDustGridStructure.cpp \
    LogWavelengthGrid.cpp \
    LuminosityStellarCompNormalization.cpp \
    MGEGeometry.cpp \
    MRNDustMix.cpp \
    MappingsSED.cpp \
    MappingsSEDFamily.cpp \
    MarastonSED.cpp \
    MeanZubkoDustMix.cpp \
    MeshDustComponent.cpp \
    MieSilicateGrainComposition.cpp \
    ModifiedLogNormalGrainSizeDistribution.cpp \
    ModifiedPowerLawGrainSizeDistribution.cpp \
    MonteCarloSimulation.cpp \
    MultiFrameInstrument.cpp \
    MultiGrainDustMix.cpp \
    NestedLogWavelengthGrid.cpp \
    NetzerAccretionDiskGeometry.cpp \
    OctTreeDustGridStructure.cpp \
    OctTreeNode.cpp \
    OligoDustSystem.cpp \
    OligoMonteCarloSimulation.cpp \
    OligoStellarComp.cpp \
    OligoWavelengthGrid.cpp \
    PanDustSystem.cpp \
    PanMonteCarloSimulation.cpp \
    PanStellarComp.cpp \
    PanWavelengthGrid.cpp \
    Parallel.cpp \
    ParallelFactory.cpp \
    ParallelTarget.cpp \
    ParticleTreeDustGridStructure.cpp \
    PegaseSED.cpp \
    PerspectiveInstrument.cpp \
    PhotonPackage.cpp \
    PlanckFunction.cpp \
    PlummerGeometry.cpp \
    PointGeometry.cpp \
    Position.cpp \
    PowAxDustGridStructure.cpp \
    PowCubDustGridStructure.cpp \
    PowSpheDustGridStructure.cpp \
    PowerLawGrainSizeDistribution.cpp \
    PseudoSersicGeometry.cpp \
    QuasarSED.cpp \
    RadialDustCompNormalization.cpp \
    Random.cpp \
    RingGeometry.cpp \
    SED.cpp \
    SEDInstrument.cpp \
    SIUnits.cpp \
    SPHDustDistribution.cpp \
    SPHGasParticle.cpp \
    SPHGasParticleGrid.cpp \
    SepAxGeometry.cpp \
    SersicFunction.cpp \
    SersicGeometry.cpp \
    ShellGeometry.cpp \
    SignalHandler.cpp \
    SimpleInstrument.cpp \
    Simulation.cpp \
    SimulationItem.cpp \
    SingleFrameInstrument.cpp \
    SmoothingKernel.cpp \
    SpecialFunctions.cpp \
    SpheDustGridStructure.cpp \
    SpheGeometry.cpp \
    StarburstSED.cpp \
    StellarComp.cpp \
    StellarCompNormalization.cpp \
    StellarSED.cpp \
    StellarSystem.cpp \
    StellarUnits.cpp \
    StopWatch.cpp \
    SunSED.cpp \
    TTauriDiskGeometry.cpp \
    TimeLogger.cpp \
    TorusGeometry.cpp \
    TransientDustEmissivity.cpp \
    TreeDustGridStructure.cpp \
    TreeNode.cpp \
    TreeNodeBoxDensityCalculator.cpp \
    TreeNodeSampleDensityCalculator.cpp \
    Trust1Geometry.cpp \
    Trust6Geometry.cpp \
    Trust7aGeometry.cpp \
    Trust7bGeometry.cpp \
    TrustDustMix.cpp \
    TrustGraphiteGrainComposition.cpp \
    TrustMeanDustMix.cpp \
    TrustNeutralPAHGrainComposition.cpp \
    TrustSilicateGrainComposition.cpp \
    TwoPhaseDustGridStructure.cpp \
    UniformCuboidGeometry.cpp \
    UniformSmoothingKernel.cpp \
    Units.cpp \
    VoronoiDustDistribution.cpp \
    VoronoiDustGridStructure.cpp \
    VoronoiGeometry.cpp \
    VoronoiMesh.cpp \
    VoronoiMeshAsciiFile.cpp \
    VoronoiMeshFile.cpp \
    WavelengthGrid.cpp \
    WeingartnerDraineDustMix.cpp \
    XDustCompNormalization.cpp \
    YDustCompNormalization.cpp \
    ZDustCompNormalization.cpp \
    ZubkoDustMix.cpp \
    ZubkoSilicateGrainSizeDistribution.cpp \
    ZubkoGraphiteGrainSizeDistribution.cpp \
    ZubkoPAHGrainSizeDistribution.cpp \
    MinSilicateGrainComposition.cpp \
    ForsteriteGrainComposition.cpp \
    EnstatiteGrainComposition.cpp \
    GeometricStellarComp.cpp \
    SPHStellarComp.cpp \
    VoronoiStellarComp.cpp \
    AdaptiveMeshStellarComp.cpp \
    FileGrainComposition.cpp \
    StellarSurfaceGeometry.cpp \
    RangeGrainSizeDistribution.cpp \
    SingleGrainSizeDistribution.cpp \
    Trust2Geometry.cpp \
    SolarPatchGeometry.cpp \
    ProcessCommunicator.cpp \
    PeerToPeerCommunicator.cpp \
    MasterSlaveCommunicator.cpp \
    ProcessAssigner.cpp \
    IdenticalAssigner.cpp \
    StaggeredAssigner.cpp \
    SequentialAssigner.cpp \
    SPHGeometry.cpp \
    StokesVector.cpp \
    PolarizedSilicateGrainComposition.cpp \
    PolarizedGraphiteGrainComposition.cpp \
    ReadFitsGeometry.cpp \
    AmHydrocarbonGrainComposition.cpp \
    OffsetGeometryDecorator.cpp \
    RotateGeometryDecorator.cpp \
    SpheroidalGeometryDecorator.cpp \
    TriaxialGeometryDecorator.cpp \
    SphericalCavityGeometryDecorator.cpp \
    SpiralStructureGeometryDecorator.cpp \
    ClumpyGeometryDecorator.cpp \
    FoamGeometryDecorator.cpp \
    CombineGeometryDecorator.cpp \
    CropGeometryDecorator.cpp \
    LaserGeometry.cpp \
    ElectronDustMix.cpp \
    CubBackgroundGeometry.cpp \
    SpheBackgroundGeometry.cpp \
    SpectralLuminosityStellarCompNormalization.cpp \
    RootAssigner.cpp \
    RandomAssigner.cpp \
    TextOutFile.cpp \
    Image.cpp \
    SphericalAdaptiveMesh.cpp \
    SphericalAdaptiveMeshDustDistribution.cpp \
    TextInFile.cpp \
    SEDFamily.cpp \
    CylindricalCavityGeometryDecorator.cpp \
    ConicalShellGeometry.cpp
