#pragma once
#include <SFML/Graphics.hpp>
#include "Core/BaseFunctions.hpp"
#include <vector>

namespace Config {
    //these seconds are 12:00 on January 1, 2000
    //inline constexpr startTime = 946727935.816  // seconds since January 1, 1970

    namespace Window {
        inline constexpr uint64_t width = 800;
        inline constexpr uint64_t height = 800;

        inline constexpr uint64_t minWidth = width;
        inline constexpr uint64_t minHeight = height;


        inline constexpr sf::Color backgroundColor(51, 31, 61);
        inline constexpr unsigned int fps = 60U;

        inline constexpr uint64_t starsSeed = 42;
        inline constexpr uint64_t starsCount = 500;
        inline constexpr uint64_t maxStarsRadius = 2;  // px
        inline const std::vector<sf::Color> startStarsColor{ sf::Color(255, 255, 255) };

        // for solution of accumulation of error
        inline constexpr float maxDt = 0.05f;      // clamping
        inline constexpr float maxSubDt = 0.001f;  // sub-stepping
        inline constexpr int maxSteps = 200;       // sub-stepping
    }

    namespace Gui {
        inline constexpr float width = 450.f;
        inline constexpr float height = 360.f;

        inline constexpr float fontGlobalCase = 1.4f;
    };

    namespace Coefs {
        inline constexpr double G = 6.67430E-11; // N*m^2/kg^2   or   m^3/(kg*s^2)
        inline constexpr double AU_TO_M = 149597870.7 * 1000.;  // m     (1.496E-11)
        inline constexpr double M_TO_AU = 6.684587E-12;  // or (1. / AU_TO_M)
        inline constexpr double EM_TO_KG = 5.972E24;
        inline constexpr float startTimeAcceleration = 1;

        inline constexpr float minTimeAcceleraion = 1.f;
        inline constexpr float maxTimeAcceleraion = 25E6;

        // deprecated functions
        //float auToPixels();
        //float pixelsToAu();
        //float pixelsToKm();
        //float kmToPixels();
        //float auToKm();
        //float kmToAu();
        //float emToKg();
        //float kgToEm();
    }

    namespace CB {
        // J2000.0
        namespace Sun {
            inline const std::string name = "Sun";

            // heliocentric rectangular coordinate system
            inline constexpr double startBaseRealX = 0.;   // au
            inline constexpr double startBaseRealY = 0.;   // au

            // heliocentric polar coordinate system
            inline constexpr double longitude = 0.;        // degrees
            inline constexpr double distance = 0.;         // degrees

            inline const sf::Vector2<double> realV = sf::Vector2<double>(0., sf::Angle(sf::degrees(180.f)));  // {m per s, degrees}

            inline constexpr double mass = 332950.;    // Earth masses

            inline constexpr double realR = 695500.;   // km
            inline constexpr float pixelRadius = 35.f;
            inline constexpr float minPixelRadius = 4.f;

            inline const sf::Color color(243, 159, 24, 235);
        }

        // terrestial planets
        namespace Mercury {
            inline const std::string name = "Mercury";

            inline constexpr double aphelion = 0.466697;         // au
            inline constexpr double perihelion = 0.307499;       // au
            inline constexpr double semiMajorAxis = 0.38709821;  // au (circular orbit)

            inline constexpr double eccentricity = 0.2056;  // e
            inline const sf::Angle inclination = sf::degrees(7.00);  // i
            inline const sf::Angle longitudeAscendingNode = sf::degrees(48.33);  // big omega
            inline const sf::Angle argumentOfPericenter = sf::degrees(29.12); // little omega
            inline const sf::Angle trueAnomaly = sf::degrees(176.49f);  // nu
            inline const sf::Angle argumentOfLatitude = argumentOfPericenter + trueAnomaly; // u

            inline const double polarRadius = calculatePolarRadius(semiMajorAxis, eccentricity, trueAnomaly);
            inline const sf::Vector2<double> heliocentricEclipticCoords = calculateEclipticCoords(polarRadius, longitudeAscendingNode, argumentOfLatitude, inclination);

            // heliocentric rectangular coordinate system
            inline const double startBaseRealX = heliocentricEclipticCoords.x;  // au
            inline const double startBaseRealY = heliocentricEclipticCoords.y;  // au

            // heliocentric polar coordinate system
            inline const sf::Angle trueLongitude = longitudeAscendingNode + argumentOfPericenter + trueAnomaly;  // degrees, L
            inline const sf::Angle longitudeAphelion = sf::degrees(348.7);                                                 // degrees
            inline const sf::Angle longitudePerihelion = sf::degrees(normalizeDegrees(longitudeAphelion.asDegrees() - 180.));  // degrees, varpi

            //inline const sf::Angle argumentOfVelocityForTrueLongitude = argumentOfVelocityAtTrueLongitude(trueLongitude.asDegrees(), eccentricity, longitudePerihelion.asDegrees());
            //inline const sf::Angle argumentOfVelocityForAphelion = argumentOfVelocityAtTrueLongitude(trueLongitude.asDegrees(), eccentricity, longitudePerihelion.asDegrees());
            //inline const sf::Angle argumentOfVelocityForPerihelion = argumentOfVelocityAtTrueLongitude(trueLongitude.asDegrees(), eccentricity, longitudePerihelion.asDegrees());
            inline const sf::Angle argumentOfVelocityForTrueLongitude = argumentOfVelocityAtTrueLongitude(trueLongitude, eccentricity, longitudeAscendingNode, inclination, argumentOfPericenter);
            inline const sf::Angle argumentOfVelocityForAphelion = argumentOfVelocityAtTrueLongitude(longitudeAphelion, eccentricity, longitudeAscendingNode, inclination, argumentOfPericenter);
            inline const sf::Angle argumentOfVelocityForPerihelion = argumentOfVelocityAtTrueLongitude(longitudePerihelion, eccentricity, longitudeAscendingNode, inclination, argumentOfPericenter);

            inline const sf::Vector2<double> trueVelocity = sf::Vector2<double>(38.88 * 1000., argumentOfVelocityForTrueLongitude);          // {m per s, degrees}
            inline const sf::Vector2<double> aphelionVelocity = sf::Vector2<double>(38.7 * 1000., argumentOfVelocityForAphelion);            // {m per s, degrees}
            inline const sf::Vector2<double> perihelionVelocity = sf::Vector2<double>(56.6 * 1000., argumentOfVelocityForPerihelion);        // {m per s, degrees}

            inline constexpr double mass = 0.055;  // Earth masses

            inline constexpr double realR = 2440.f;  // km
            inline constexpr float pixelRadius = 10.f;
            inline constexpr float minPixelRadius = 1.f;

            inline const sf::Color color(125, 81, 45);
        }
        namespace Venus {
            inline const std::string name = "Venus";

            inline constexpr double aphelion = 0.728213;       // au
            inline constexpr double perihelion = 0.718440;     // au
            inline constexpr double semiMajorAxis = 0.723332;  // au (circular orbit)

            inline constexpr double eccentricity = 0.0068;
            inline const sf::Angle inclination = sf::degrees(3.39);  // i
            inline const sf::Angle longitudeAscendingNode = sf::degrees(76.68);  // big omega
            inline const sf::Angle argumentOfPericenter = sf::degrees(54.85); // little omega
            inline const sf::Angle trueAnomaly = sf::degrees(51.05);  // nu
            inline const sf::Angle argumentOfLatitude = argumentOfPericenter + trueAnomaly; // u

            inline const double polarRadius = calculatePolarRadius(semiMajorAxis, eccentricity, trueAnomaly);
            inline const sf::Vector2<double> heliocentricEclipticCoords = calculateEclipticCoords(polarRadius, longitudeAscendingNode, argumentOfLatitude, inclination);

            // heliocentric rectangular coordinate system
            inline const double startBaseRealX = heliocentricEclipticCoords.x;  // au
            inline const double startBaseRealY = heliocentricEclipticCoords.y;  // au

            // heliocentric polar coordinate system
            inline const sf::Angle trueLongitude = sf::degrees(182.58);  // degrees, L
            inline const sf::Angle longitudeAphelion = sf::degrees(311.3);                                     // degrees
            inline const sf::Angle longitudePerihelion = sf::degrees(normalizeDegrees(longitudeAphelion.asDegrees() - 180.));  // degrees, varpi

            inline const sf::Angle argumentOfVelocityForTrueLongitude = argumentOfVelocityAtTrueLongitude(trueLongitude, eccentricity, longitudeAscendingNode, inclination, argumentOfPericenter);
            inline const sf::Angle argumentOfVelocityForAphelion = argumentOfVelocityAtTrueLongitude(longitudeAphelion, eccentricity, longitudeAscendingNode, inclination, argumentOfPericenter);
            inline const sf::Angle argumentOfVelocityForPerihelion = argumentOfVelocityAtTrueLongitude(longitudePerihelion, eccentricity, longitudeAscendingNode, inclination, argumentOfPericenter);

            inline const sf::Vector2<double> trueVelocity = sf::Vector2<double>(35.17 * 1000., argumentOfVelocityForTrueLongitude);          // {m per s, degrees}
            inline const sf::Vector2<double> aphelionVelocity = sf::Vector2<double>(35.78 * 1000., argumentOfVelocityForAphelion);            // {m per s, degrees}
            inline const sf::Vector2<double> perihelionVelocity = sf::Vector2<double>(35.26 * 1000., argumentOfVelocityForPerihelion);        // {m per s, degrees}

            inline constexpr double mass = 0.815;  // Earth masses

            inline constexpr double realR = 6052.;  // km
            inline constexpr float pixelRadius = 15.f;
            inline constexpr float minPixelRadius = 2.f;

            inline const sf::Color color(236, 124, 38);
        }
        namespace Earth {
            inline const std::string name = "Earth";

            inline constexpr double aphelion = 1.0167;    // au
            inline constexpr double perihelion = 0.9833;  // au
            inline constexpr double semiMajorAxis = 1.;   // au (circular orbit)

            inline constexpr double eccentricity = 0.0167086;
            inline const sf::Angle inclination = sf::degrees(0.f);  // i
            inline const sf::Angle longitudeAscendingNode = sf::degrees(0.f);  // big omega
            inline const sf::Angle argumentOfPericenter = sf::degrees(102.947f); // little omega
            inline const sf::Angle trueAnomaly = sf::degrees(357.432f);  // nu
            inline const sf::Angle argumentOfLatitude = argumentOfPericenter + trueAnomaly; // u

            inline const double polarRadius = calculatePolarRadius(semiMajorAxis, eccentricity, trueAnomaly);
            inline const sf::Vector2<double> heliocentricEclipticCoords = calculateEclipticCoords(polarRadius, longitudeAscendingNode, argumentOfLatitude, inclination);

            // heliocentric rectangular coordinate system
            inline const double startBaseRealX = heliocentricEclipticCoords.x;  // au
            inline const double startBaseRealY = heliocentricEclipticCoords.y;  // au

            // heliocentric polar coordinate system
            inline const double trueLongitude = radToDeg(atan2(startBaseRealY, startBaseRealX));   // degrees, L
            inline constexpr double longitudeAphelion = 283.0;                                     // degrees
            inline const double longitudePerihelion = normalizeDegrees(longitudeAphelion - 180.);  // degrees, varpi

            inline const sf::Angle argumentOfVelocityForTrueLongitude = argumentOfVelocityAtTrueLongitude(trueLongitude, eccentricity, longitudePerihelion);
            inline const sf::Angle argumentOfVelocityForAphelion = argumentOfVelocityAtTrueLongitude(longitudeAphelion, eccentricity, longitudePerihelion);
            inline const sf::Angle argumentOfVelocityForPerihelion = argumentOfVelocityAtTrueLongitude(longitudePerihelion, eccentricity, longitudePerihelion);

            inline const sf::Vector2<double> trueVelocity = sf::Vector2<double>(30.27 * 1000., argumentOfVelocityForTrueLongitude);           // {m per s, degrees}
            inline const sf::Vector2<double> aphelionVelocity = sf::Vector2<double>(29.29 * 1000., argumentOfVelocityForAphelion);            // {m per s, degrees}
            inline const sf::Vector2<double> perihelionVelocity = sf::Vector2<double>(30.29 * 1000., argumentOfVelocityForPerihelion);        // {m per s, degrees}

            inline constexpr double mass = 1.;  // Earth masses

            inline constexpr double realR = 6371.0;  // km
            inline constexpr float pixelRadius = 15.f;
            inline constexpr float minPixelRadius = 2.f;

            inline constexpr sf::Color color(107, 147, 214);
        }

        namespace Mars {
            inline const std::string name = "Mars";

            inline constexpr double aphelion = 1.666;      // au
            inline constexpr double perihelion = 1.381;    // au
            inline constexpr double semiMajorAxis = 1.52;  // au (circular orbit)

            inline constexpr double eccentricity = 0.0934;
            inline const sf::Angle inclination = sf::degrees(1.85);  // i
            inline const sf::Angle longitudeAscendingNode = sf::degrees(49.56);  // big omega
            inline const sf::Angle argumentOfPericenter = sf::degrees(286.48); // little omega
            inline const sf::Angle trueAnomaly = sf::degrees(23.40);  // nu
            inline const sf::Angle argumentOfLatitude = argumentOfPericenter + trueAnomaly; // u

            inline const double polarRadius = calculatePolarRadius(semiMajorAxis, eccentricity, trueAnomaly);
            inline const sf::Vector2<double> heliocentricEclipticCoords = calculateEclipticCoords(polarRadius, longitudeAscendingNode, argumentOfLatitude, inclination);

            // heliocentric rectangular coordinate system
            inline const double startBaseRealX = heliocentricEclipticCoords.x;  // au
            inline const double startBaseRealY = heliocentricEclipticCoords.y;  // au

            // heliocentric polar coordinate system
            inline const sf::Angle trueLongitude = sf::degrees(355.45);   // degrees, L
            inline const sf::Angle longitudeAphelion = sf::degrees(156.04);                                     // degrees
            inline const sf::Angle longitudePerihelion = sf::degrees(normalizeDegrees(longitudeAphelion.asDegrees() - 180.));  // degrees, varpi

            inline const sf::Angle argumentOfVelocityForTrueLongitude = argumentOfVelocityAtTrueLongitude(trueLongitude, eccentricity, longitudeAscendingNode, inclination, argumentOfPericenter);
            inline const sf::Angle argumentOfVelocityForAphelion = argumentOfVelocityAtTrueLongitude(longitudeAphelion, eccentricity, longitudeAscendingNode, inclination, argumentOfPericenter);
            inline const sf::Angle argumentOfVelocityForPerihelion = argumentOfVelocityAtTrueLongitude(longitudePerihelion, eccentricity, longitudeAscendingNode, inclination, argumentOfPericenter);

            inline const sf::Vector2<double> trueVelocity = sf::Vector2<double>(26.33 * 1000., argumentOfVelocityForTrueLongitude);          // {m per s, degrees}
            inline const sf::Vector2<double> aphelionVelocity = sf::Vector2<double>(22.0 * 1000., argumentOfVelocityForAphelion);             // {m per s, degrees}
            inline const sf::Vector2<double> perihelionVelocity = sf::Vector2<double>(26.5 * 1000., argumentOfVelocityForPerihelion);         // {m per s, degrees}

            inline constexpr double mass = 0.107;  // Earth masses

            inline constexpr double realR = 3389.5;  // km
            inline constexpr float pixelRadius = 12.f;
            inline constexpr float minPixelRadius = 2.f;

            inline constexpr sf::Color color(193, 68, 14);
        }

        // gas giants
        namespace Jupiter {
            inline const std::string name = "Jupiter";

            inline constexpr double aphelion = 5.4570;       // au
            inline constexpr double perihelion = 4.9506;     // au
            inline constexpr double semiMajorAxis = 5.2038;  // au (circular orbit)

            inline constexpr double eccentricity = 0.0489;
            inline const sf::Angle inclination = sf::degrees(1.31);  // i
            inline const sf::Angle longitudeAscendingNode = sf::degrees(100.45);  // big omega
            inline const sf::Angle argumentOfPericenter = sf::degrees(274.30); // little omega
            inline const sf::Angle trueAnomaly = sf::degrees(21.62);  // nu
            inline const sf::Angle argumentOfLatitude = argumentOfPericenter + trueAnomaly; // u

            inline const double polarRadius = calculatePolarRadius(semiMajorAxis, eccentricity, trueAnomaly);
            inline const sf::Vector2<double> heliocentricEclipticCoords = calculateEclipticCoords(polarRadius, longitudeAscendingNode, argumentOfLatitude, inclination);

            // heliocentric rectangular coordinate system
            inline const double startBaseRealX = heliocentricEclipticCoords.x;  // au
            inline const double startBaseRealY = heliocentricEclipticCoords.y;  // au

            // heliocentric polar coordinate system
            inline const sf::Angle trueLongitude = sf::degrees(36.37);   // degrees, L
            inline const sf::Angle longitudeAphelion = sf::degrees(194.33);                                    // degrees
            inline const sf::Angle longitudePerihelion = sf::degrees(normalizeDegrees(longitudeAphelion.asDegrees() - 180.));  // degrees, varpi

            inline const sf::Angle argumentOfVelocityForTrueLongitude = argumentOfVelocityAtTrueLongitude(trueLongitude, eccentricity, longitudeAscendingNode, inclination, argumentOfPericenter);
            inline const sf::Angle argumentOfVelocityForAphelion = argumentOfVelocityAtTrueLongitude(longitudeAphelion, eccentricity, longitudeAscendingNode, inclination, argumentOfPericenter);
            inline const sf::Angle argumentOfVelocityForPerihelion = argumentOfVelocityAtTrueLongitude(longitudePerihelion, eccentricity, longitudeAscendingNode, inclination, argumentOfPericenter);

            inline const sf::Vector2<double> trueVelocity = sf::Vector2<double>(13.66 * 1000., argumentOfVelocityForTrueLongitude);          // {m per s, degrees}
            inline const sf::Vector2<double> aphelionVelocity = sf::Vector2<double>(12.44 * 1000., argumentOfVelocityForAphelion);             // {m per s, degrees}
            inline const sf::Vector2<double> perihelionVelocity = sf::Vector2<double>(13.71 * 1000., argumentOfVelocityForPerihelion);         // {m per s, degrees}

            inline constexpr double mass = 317.8;  // Earth masses

            inline constexpr double realR = 69886;  // km
            inline constexpr float pixelRadius = 20.f;
            inline constexpr float minPixelRadius = 3.f;

            inline constexpr sf::Color color(201, 144, 57);
        }
        namespace Saturn {
            inline const std::string name = "Saturn";

            inline constexpr double aphelion = 10.1238;      // au
            inline constexpr double perihelion = 9.0412;     // au
            inline constexpr double semiMajorAxis = 9.5826;  // au (circular orbit)

            inline constexpr double eccentricity = 0.0542;
            inline const sf::Angle inclination = sf::degrees(2.48);  // i
            inline const sf::Angle longitudeAscendingNode = sf::degrees(113.67);  // big omega
            inline const sf::Angle argumentOfPericenter = sf::degrees(338.77); // little omega
            inline const sf::Angle trueAnomaly = sf::degrees(313.12);  // nu
            inline const sf::Angle argumentOfLatitude = argumentOfPericenter + trueAnomaly; // u

            inline const double polarRadius = calculatePolarRadius(semiMajorAxis, eccentricity, trueAnomaly);
            inline const sf::Vector2<double> heliocentricEclipticCoords = calculateEclipticCoords(polarRadius, longitudeAscendingNode, argumentOfLatitude, inclination);

            // heliocentric rectangular coordinate system
            inline const double startBaseRealX = heliocentricEclipticCoords.x;  // au
            inline const double startBaseRealY = heliocentricEclipticCoords.y;  // au

            // heliocentric polar coordinate system
            inline const sf::Angle trueLongitude = sf::degrees(45.56);   // degrees, L
            inline const sf::Angle longitudeAphelion = sf::degrees(272.43);                                    // degrees
            inline const sf::Angle longitudePerihelion = sf::degrees(normalizeDegrees(longitudeAphelion.asDegrees() - 180.));  // degrees, varpi

            inline const sf::Angle argumentOfVelocityForTrueLongitude = argumentOfVelocityAtTrueLongitude(trueLongitude, eccentricity, longitudeAscendingNode, inclination, argumentOfPericenter);
            inline const sf::Angle argumentOfVelocityForAphelion = argumentOfVelocityAtTrueLongitude(longitudeAphelion, eccentricity, longitudeAscendingNode, inclination, argumentOfPericenter);
            inline const sf::Angle argumentOfVelocityForPerihelion = argumentOfVelocityAtTrueLongitude(longitudePerihelion, eccentricity, longitudeAscendingNode, inclination, argumentOfPericenter);

            inline const sf::Vector2<double> trueVelocity = sf::Vector2<double>(10.02 * 1000., argumentOfVelocityForTrueLongitude);          // {m per s, degrees}
            inline const sf::Vector2<double> aphelionVelocity = sf::Vector2<double>(9.13 * 1000., argumentOfVelocityForAphelion);             // {m per s, degrees}
            inline const sf::Vector2<double> perihelionVelocity = sf::Vector2<double>(10.22 * 1000., argumentOfVelocityForPerihelion);         // {m per s, degrees}

            inline constexpr double mass = 95.2;  // Earth masses

            inline constexpr double realR = 58232;  // km
            inline constexpr float pixelRadius = 20.f;
            inline constexpr float minPixelRadius = 3.f;

            inline constexpr sf::Color color(234, 214, 184);
        }

        // ice giants
        namespace Uranus {
            inline const std::string name = "Uranus";

            inline constexpr double aphelion = 20.0965;      // au
            inline constexpr double perihelion = 18.2861;     // au
            inline constexpr double semiMajorAxis = 19.1913;  // au (circular orbit)

            inline constexpr double eccentricity = 0.0472;
            inline const sf::Angle inclination = sf::degrees(0.77);  // i
            inline const sf::Angle longitudeAscendingNode = sf::degrees(74.01);  // big omega
            inline const sf::Angle argumentOfPericenter = sf::degrees(96.96); // little omega
            inline const sf::Angle trueAnomaly = sf::degrees(145.42);  // nu
            inline const sf::Angle argumentOfLatitude = argumentOfPericenter + trueAnomaly; // u

            inline const double polarRadius = calculatePolarRadius(semiMajorAxis, eccentricity, trueAnomaly);
            inline const sf::Vector2<double> heliocentricEclipticCoords = calculateEclipticCoords(polarRadius, longitudeAscendingNode, argumentOfLatitude, inclination);

            // heliocentric rectangular coordinate system
            inline const double startBaseRealX = heliocentricEclipticCoords.x;  // au
            inline const double startBaseRealY = heliocentricEclipticCoords.y;  // au

            // heliocentric polar coordinate system
            inline const sf::Angle trueLongitude = sf::degrees(316.39);   // degrees, L
            inline const sf::Angle longitudeAphelion = sf::degrees(350.96);                                    // degrees
            inline const sf::Angle longitudePerihelion = sf::degrees(normalizeDegrees(longitudeAphelion.asDegrees() - 180.));  // degrees, varpi

            inline const sf::Angle argumentOfVelocityForTrueLongitude = argumentOfVelocityAtTrueLongitude(trueLongitude, eccentricity, longitudeAscendingNode, inclination, argumentOfPericenter);
            inline const sf::Angle argumentOfVelocityForAphelion = argumentOfVelocityAtTrueLongitude(longitudeAphelion, eccentricity, longitudeAscendingNode, inclination, argumentOfPericenter);
            inline const sf::Angle argumentOfVelocityForPerihelion = argumentOfVelocityAtTrueLongitude(longitudePerihelion, eccentricity, longitudeAscendingNode, inclination, argumentOfPericenter);

            inline const sf::Vector2<double> trueVelocity = sf::Vector2<double>(-6.54 * 1000., argumentOfVelocityForTrueLongitude);          // {m per s, degrees}
            inline const sf::Vector2<double> aphelionVelocity = sf::Vector2<double>(-6.49 * 1000., argumentOfVelocityForAphelion);            // {m per s, degrees}
            inline const sf::Vector2<double> perihelionVelocity = sf::Vector2<double>(-7.14 * 1000., argumentOfVelocityForPerihelion);        // {m per s, degrees}

            inline constexpr double mass = 14.5;  // Earth masses

            inline constexpr double realR = 25362;  // km
            inline constexpr float pixelRadius = 20.f;
            inline constexpr float minPixelRadius = 2.f;

            inline constexpr sf::Color color(217, 221, 244);
        }
        namespace Neptune {
            inline const std::string name = "Neptune";

            inline constexpr double aphelion = 30.33;      // au
            inline constexpr double perihelion = 29.81;     // au
            inline constexpr double semiMajorAxis = 30.07;  // au (circular orbit)

            inline constexpr double eccentricity = 0.0086;
            inline const sf::Angle inclination = sf::degrees(1.77);  // i
            inline const sf::Angle longitudeAscendingNode = sf::degrees(131.78);  // big omega
            inline const sf::Angle argumentOfPericenter = sf::degrees(273.19); // little omega
            inline const sf::Angle trueAnomaly = sf::degrees(258.94);  // nu
            inline const sf::Angle argumentOfLatitude = argumentOfPericenter + trueAnomaly; // u

            inline const double polarRadius = calculatePolarRadius(semiMajorAxis, eccentricity, trueAnomaly);
            inline const sf::Vector2<double> heliocentricEclipticCoords = calculateEclipticCoords(polarRadius, longitudeAscendingNode, argumentOfLatitude, inclination);

            // heliocentric rectangular coordinate system
            inline const double startBaseRealX = heliocentricEclipticCoords.x;  // au
            inline const double startBaseRealY = heliocentricEclipticCoords.y;  // au

            // heliocentric polar coordinate system
            inline const sf::Angle trueLongitude = sf::degrees(303.91);   // degrees, L
            inline const sf::Angle longitudeAphelion = sf::degrees(224.97);                                    // degrees
            inline const sf::Angle longitudePerihelion = sf::degrees(normalizeDegrees(longitudeAphelion.asDegrees() - 180.));  // degrees, varpi

            inline const sf::Angle argumentOfVelocityForTrueLongitude = argumentOfVelocityAtTrueLongitude(trueLongitude, eccentricity, longitudeAscendingNode, inclination, argumentOfPericenter);
            inline const sf::Angle argumentOfVelocityForAphelion = argumentOfVelocityAtTrueLongitude(longitudeAphelion, eccentricity, longitudeAscendingNode, inclination, argumentOfPericenter);
            inline const sf::Angle argumentOfVelocityForPerihelion = argumentOfVelocityAtTrueLongitude(longitudePerihelion, eccentricity, longitudeAscendingNode, inclination, argumentOfPericenter);

            inline const sf::Vector2<double> trueVelocity = sf::Vector2<double>(5.42 * 1000., argumentOfVelocityForTrueLongitude);          // {m per s, degrees}
            inline const sf::Vector2<double> aphelionVelocity = sf::Vector2<double>(5.40 * 1000., argumentOfVelocityForAphelion);             // {m per s, degrees}
            inline const sf::Vector2<double> perihelionVelocity = sf::Vector2<double>(5.50 * 1000., argumentOfVelocityForPerihelion);         // {m per s, degrees}

            inline constexpr double mass = 17.1;  // Earth masses

            inline constexpr double realR = 24622;  // km
            inline constexpr float pixelRadius = 20.f;
            inline constexpr float minPixelRadius = 3.f;

            inline constexpr sf::Color color(63, 84, 186);
        }
        // dwarf planet
        namespace Pluto {
            inline const std::string name = "Pluto";

            inline constexpr double aphelion = 49.305;      // au
            inline constexpr double perihelion = 29.658;     // au
            inline constexpr double semiMajorAxis = 39.482;  // au (circular orbit)

            inline constexpr double eccentricity = 0.2488;
            inline const sf::Angle inclination = sf::degrees(17.14);  // i
            inline const sf::Angle longitudeAscendingNode = sf::degrees(110.30);  // big omega
            inline const sf::Angle argumentOfPericenter = sf::degrees(113.76); // little omega
            inline const sf::Angle trueAnomaly = sf::degrees(25.18);  // nu
            inline const sf::Angle argumentOfLatitude = argumentOfPericenter + trueAnomaly; // u

            inline const double polarRadius = calculatePolarRadius(semiMajorAxis, eccentricity, trueAnomaly);
            inline const sf::Vector2<double> heliocentricEclipticCoords = calculateEclipticCoords(polarRadius, longitudeAscendingNode, argumentOfLatitude, inclination);

            // heliocentric rectangular coordinate system
            inline const double startBaseRealX = heliocentricEclipticCoords.x;  // au
            inline const double startBaseRealY = heliocentricEclipticCoords.y;  // au

            // heliocentric polar coordinate system
            inline const sf::Angle trueLongitude = sf::degrees(249.24);   // degrees, L
            inline const sf::Angle longitudeAphelion = sf::degrees(44.07);                                     // degrees
            inline const sf::Angle longitudePerihelion = sf::degrees(normalizeDegrees(longitudeAphelion.asDegrees() - 180.));  // degrees, varpi

            inline const sf::Angle argumentOfVelocityForTrueLongitude = argumentOfVelocityAtTrueLongitude(trueLongitude, eccentricity, longitudeAscendingNode, inclination, argumentOfPericenter);
            inline const sf::Angle argumentOfVelocityForAphelion = argumentOfVelocityAtTrueLongitude(longitudeAphelion, eccentricity, longitudeAscendingNode, inclination, argumentOfPericenter);
            inline const sf::Angle argumentOfVelocityForPerihelion = argumentOfVelocityAtTrueLongitude(longitudePerihelion, eccentricity, longitudeAscendingNode, inclination, argumentOfPericenter);

            inline const sf::Vector2<double> trueVelocity = sf::Vector2<double>(6.02 * 1000., argumentOfVelocityForTrueLongitude);          // {m per s, degrees}
            inline const sf::Vector2<double> aphelionVelocity = sf::Vector2<double>(3.71 * 1000., argumentOfVelocityForAphelion);            // {m per s, degrees}
            inline const sf::Vector2<double> perihelionVelocity = sf::Vector2<double>(6.11 * 1000., argumentOfVelocityForPerihelion);        // {m per s, degrees}

            inline constexpr double mass = 0.0022;  // Earth masses

            inline constexpr double realR = 1188.3;  // km
            inline constexpr float pixelRadius = 20.f;
            inline constexpr float minPixelRadius = 1.f;

            inline constexpr sf::Color color(255, 241, 213);
        }

        // moons
        namespace Moon {
            inline const std::string name = "Moon";

            inline constexpr double apogee = 0.00271;     // au
            inline constexpr double perigee = 0.00243;      // au
            inline constexpr double semiMajorAxis = 0.00257;  // au (circular orbit)

            inline constexpr double eccentricity = 0.0549;  // e
            inline const sf::Angle inclination = sf::degrees(5.145f);  // i
            inline const sf::Angle longitudeAscendingNode = sf::degrees(125.0445f);  // big omega
            inline const sf::Angle argumentOfPericenter = sf::degrees(318.31f);  // little omega
            inline const sf::Angle trueAnomaly = sf::degrees(139.2047f);  // nu
            inline const sf::Angle argumentOfLatitude = argumentOfPericenter + trueAnomaly; // u

            inline const double polarRadius = calculatePolarRadius(semiMajorAxis, eccentricity, trueAnomaly);
            inline const sf::Vector2<double> geocentricEclipticCoords = calculateEclipticCoords(polarRadius, longitudeAscendingNode, argumentOfLatitude, inclination);

            // heliocentric rectangular coordinate system
            inline const double startBaseRealX = Earth::startBaseRealX + geocentricEclipticCoords.x;  // au
            inline const double startBaseRealY = Earth::startBaseRealY + geocentricEclipticCoords.y;  // au

            // geocentric polar coordinate system
            inline constexpr double longitudeApogee = 263.353;                                   // degrees
            inline const double longitudePerigee = normalizeDegrees(longitudeApogee - 180.);     // degrees, varpi
            inline const double trueLongitude = longitudePerigee + trueAnomaly.asDegrees();      // degrees, L

            inline const sf::Angle argumentOfVelocityForTrueLongitude = argumentOfVelocityAtTrueLongitude(trueLongitude, eccentricity, longitudePerigee);
            inline const sf::Angle argumentOfVelocityForApogee = argumentOfVelocityAtTrueLongitude(longitudeApogee, eccentricity, longitudePerigee);
            inline const sf::Angle argumentOfVelocityForPerigee = argumentOfVelocityAtTrueLongitude(longitudePerigee, eccentricity, longitudePerigee);

            // speed relative to the Earth!
            inline const sf::Vector2<double> trueVelocity = sf::Vector2<double>(0.978 * 1000., argumentOfVelocityForTrueLongitude);           // {m per s, degrees}
            inline const sf::Vector2<double> apogeeVelocity = sf::Vector2<double>(0.97 * 1000., argumentOfVelocityForApogee);                 // {m per s, degrees}
            inline const sf::Vector2<double> perigeeVelocity = sf::Vector2<double>(1.082 * 1000., argumentOfVelocityForPerigee);              // {m per s, degrees}

            inline const sf::Vector2<double> trueHeliocentricVelocity = sf::Vector2<double>(
                Earth::trueVelocity.x + Moon::trueVelocity.x,
                Earth::trueVelocity.y + Moon::trueVelocity.y
            );

            inline constexpr double mass = 0.0123;  // Earth masses

            inline constexpr double realR = 1737.4;  // km
            inline constexpr float pixelRadius = 5.f;
            inline constexpr float minPixelRadius = 1.f;

            inline constexpr sf::Color color(180, 180, 180);
        }
    }

    namespace Camera {
        inline constexpr double targetPixels = 200.;  // between Sun and Mercury, default=200.
        inline const double scale = targetPixels / (Config::CB::Mercury::semiMajorAxis * Config::Coefs::AU_TO_M);  //  px/m (m to px)
        inline constexpr float minRelScale = 0.007f;  // 0.4f
        inline constexpr float maxRelScale = 35.f;
    }
}