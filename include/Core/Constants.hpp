#pragma once
#include <SFML/Graphics.hpp>
#include "Core/BaseFunctions.hpp"
#include <vector>

namespace Config {

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
        inline constexpr float startTimeAcceleration = 1E6;

        inline constexpr float minTimeAcceleraion = 1.f;
        inline constexpr float maxTimeAcceleraion = 25E6;

        // deprecated functions
        float auToPixels();
        float pixelsToAu();
        float pixelsToKm();
        float kmToPixels();
        float auToKm();
        float kmToAu();
        float emToKg();
        float kgToEm();
    }

    namespace CB {
        namespace Sun {
            inline const std::string name = "Sun";
            
            // heliocentric rectangular coordinate system
            inline constexpr double startBaseRealX = 0.;   // au
            inline constexpr double startBaseRealY = 0.;   // au

            // heliocentric ecliptic coordinate system
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

            inline constexpr double eccentricity = 0.205630;

            // heliocentric rectangular coordinate system
            inline constexpr double startBaseRealX = 0.;
            inline constexpr double startBaseRealY = semiMajorAxis;  // au

            // heliocentric ecliptic coordinate system
            inline constexpr double longitudeAphelion = 348.7;                                     // degrees
            inline const double longitudePerihelion = normalizeDegrees(longitudeAphelion - 180.);  // degrees
            inline constexpr double longitudeSemiMajorAxis = 180.;                                 // degrees


            inline const sf::Angle argumentOfVelocityForAphelion = argumentOfVelocityAtTrueAnomaly(longitudeAphelion, eccentricity, longitudePerihelion);
            inline const sf::Angle argumentOfVelocityForPerihelion = argumentOfVelocityAtTrueAnomaly(longitudePerihelion, eccentricity, longitudePerihelion);
            inline const sf::Angle argumentOfVelocityForSemiMajorAxis = argumentOfVelocityAtTrueAnomaly(longitudeSemiMajorAxis, eccentricity, longitudePerihelion);


            inline const sf::Vector2<double> aphelionVelocity = sf::Vector2<double>(38.7 * 1000., argumentOfVelocityForAphelion);            // {m per s, degrees}
            inline const sf::Vector2<double> perihelionVelocity = sf::Vector2<double>(56.6 * 1000., argumentOfVelocityForPerihelion);        // {m per s, degrees}
            inline const sf::Vector2<double> semiMajorAxisVelocity = sf::Vector2<double>(47.36 * 1000., argumentOfVelocityForSemiMajorAxis); // {m per s, degrees}

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

            inline constexpr double eccentricity = 0.006772;

            // heliocentric rectangular coordinate system
            inline constexpr double startBaseRealX = 0.;
            inline constexpr double startBaseRealY = semiMajorAxis;  // au

            // heliocentric ecliptic coordinate system
            inline constexpr double longitudeAphelion = 311.3;                                     // degrees
            inline const double longitudePerihelion = normalizeDegrees(longitudeAphelion - 180.);  // degrees
            inline constexpr double longitudeSemiMajorAxis = 180.;                                 // degrees

            inline const sf::Angle argumentOfVelocityForAphelion = argumentOfVelocityAtTrueAnomaly(longitudeAphelion, eccentricity, longitudePerihelion);
            inline const sf::Angle argumentOfVelocityForPerihelion = argumentOfVelocityAtTrueAnomaly(longitudePerihelion, eccentricity, longitudePerihelion);
            inline const sf::Angle argumentOfVelocityForSemiMajorAxis = argumentOfVelocityAtTrueAnomaly(longitudeSemiMajorAxis, eccentricity, longitudePerihelion);

            inline const sf::Vector2<double> aphelionVelocity = sf::Vector2<double>(35.78 * 1000., argumentOfVelocityForAphelion);            // {m per s, degrees}
            inline const sf::Vector2<double> perihelionVelocity = sf::Vector2<double>(35.26 * 1000., argumentOfVelocityForPerihelion);        // {m per s, degrees}
            inline const sf::Vector2<double> semiMajorAxisVelocity = sf::Vector2<double>(35.02 * 1000., argumentOfVelocityForSemiMajorAxis);  // {m per s, degrees}
            
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

            // heliocentric rectangular coordinate system
            inline constexpr double startBaseRealX = 0.;
            inline constexpr double startBaseRealY = semiMajorAxis;  // au

            // heliocentric ecliptic coordinate system
            inline constexpr double longitudeAphelion = 283.0;                                     // degrees
            inline const double longitudePerihelion = normalizeDegrees(longitudeAphelion - 180.);  // degrees
            inline constexpr double longitudeSemiMajorAxis = 180.;                                 // degrees

            inline const sf::Angle argumentOfVelocityForAphelion = argumentOfVelocityAtTrueAnomaly(longitudeAphelion, eccentricity, longitudePerihelion);
            inline const sf::Angle argumentOfVelocityForPerihelion = argumentOfVelocityAtTrueAnomaly(longitudePerihelion, eccentricity, longitudePerihelion);
            inline const sf::Angle argumentOfVelocityForSemiMajorAxis = argumentOfVelocityAtTrueAnomaly(longitudeSemiMajorAxis, eccentricity, longitudePerihelion);

            inline const sf::Vector2<double> aphelionVelocity = sf::Vector2<double>(29.29 * 1000., argumentOfVelocityForAphelion);            // {m per s, degrees}
            inline const sf::Vector2<double> perihelionVelocity = sf::Vector2<double>(30.29 * 1000., argumentOfVelocityForPerihelion);        // {m per s, degrees}
            inline const sf::Vector2<double> semiMajorAxisVelocity = sf::Vector2<double>(29.76 * 1000., argumentOfVelocityForSemiMajorAxis);  // {m per s, degrees}
            
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

            // heliocentric rectangular coordinate system
            inline constexpr double startBaseRealX = 0.;
            inline constexpr double startBaseRealY = semiMajorAxis;  // au

            // heliocentric ecliptic coordinate system
            inline constexpr double longitudeAphelion = 336.1;                                     // degrees
            inline const double longitudePerihelion = normalizeDegrees(longitudeAphelion - 180.);  // degrees
            inline constexpr double longitudeSemiMajorAxis = 180.;                                 // degrees

            inline const sf::Angle argumentOfVelocityForAphelion = argumentOfVelocityAtTrueAnomaly(longitudeAphelion, eccentricity, longitudePerihelion);
            inline const sf::Angle argumentOfVelocityForPerihelion = argumentOfVelocityAtTrueAnomaly(longitudePerihelion, eccentricity, longitudePerihelion);
            inline const sf::Angle argumentOfVelocityForSemiMajorAxis = argumentOfVelocityAtTrueAnomaly(longitudeSemiMajorAxis, eccentricity, longitudePerihelion);

            inline const sf::Vector2<double> aphelionVelocity = sf::Vector2<double>(22.0 * 1000., argumentOfVelocityForAphelion);             // {m per s, degrees}
            inline const sf::Vector2<double> perihelionVelocity = sf::Vector2<double>(26.5 * 1000., argumentOfVelocityForPerihelion);         // {m per s, degrees}
            inline const sf::Vector2<double> semiMajorAxisVelocity = sf::Vector2<double>(24.13 * 1000., argumentOfVelocityForSemiMajorAxis);  // {m per s, degrees}

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

            // heliocentric rectangular coordinate system
            inline constexpr double startBaseRealX = 0.;
            inline constexpr double startBaseRealY = semiMajorAxis;  // au

            // heliocentric ecliptic coordinate system
            inline constexpr double longitudeAphelion = 194.33;                                    // degrees
            inline const double longitudePerihelion = normalizeDegrees(longitudeAphelion - 180.);  // degrees
            inline constexpr double longitudeSemiMajorAxis = 180.;                                 // degrees

            inline const sf::Angle argumentOfVelocityForAphelion = argumentOfVelocityAtTrueAnomaly(longitudeAphelion, eccentricity, longitudePerihelion);
            inline const sf::Angle argumentOfVelocityForPerihelion = argumentOfVelocityAtTrueAnomaly(longitudePerihelion, eccentricity, longitudePerihelion);
            inline const sf::Angle argumentOfVelocityForSemiMajorAxis = argumentOfVelocityAtTrueAnomaly(longitudeSemiMajorAxis, eccentricity, longitudePerihelion);

            inline const sf::Vector2<double> aphelionVelocity = sf::Vector2<double>(12.44 * 1000., argumentOfVelocityForAphelion);             // {m per s, degrees}
            inline const sf::Vector2<double> perihelionVelocity = sf::Vector2<double>(13.71 * 1000., argumentOfVelocityForPerihelion);         // {m per s, degrees}
            inline const sf::Vector2<double> semiMajorAxisVelocity = sf::Vector2<double>(13.06 * 1000., argumentOfVelocityForSemiMajorAxis);  // {m per s, degrees}

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

            inline constexpr double eccentricity = 0.0565;

            // heliocentric rectangular coordinate system
            inline constexpr double startBaseRealX = 0.;
            inline constexpr double startBaseRealY = semiMajorAxis;  // au

            // heliocentric ecliptic coordinate system
            inline constexpr double longitudeAphelion = 272.43;                                    // degrees
            inline const double longitudePerihelion = normalizeDegrees(longitudeAphelion - 180.);  // degrees
            inline constexpr double longitudeSemiMajorAxis = 180.;                                 // degrees

            inline const sf::Angle argumentOfVelocityForAphelion = argumentOfVelocityAtTrueAnomaly(longitudeAphelion, eccentricity, longitudePerihelion);
            inline const sf::Angle argumentOfVelocityForPerihelion = argumentOfVelocityAtTrueAnomaly(longitudePerihelion, eccentricity, longitudePerihelion);
            inline const sf::Angle argumentOfVelocityForSemiMajorAxis = argumentOfVelocityAtTrueAnomaly(longitudeSemiMajorAxis, eccentricity, longitudePerihelion);

            inline const sf::Vector2<double> aphelionVelocity = sf::Vector2<double>(9.13 * 1000., argumentOfVelocityForAphelion);             // {m per s, degrees}
            inline const sf::Vector2<double> perihelionVelocity = sf::Vector2<double>(10.22 * 1000., argumentOfVelocityForPerihelion);         // {m per s, degrees}
            inline const sf::Vector2<double> semiMajorAxisVelocity = sf::Vector2<double>(9.68 * 1000., argumentOfVelocityForSemiMajorAxis);  // {m per s, degrees}

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

            // heliocentric rectangular coordinate system
            inline constexpr double startBaseRealX = 0.;
            inline constexpr double startBaseRealY = semiMajorAxis;  // au

            // heliocentric ecliptic coordinate system
            inline constexpr double longitudeAphelion = 350.96;                                    // degrees
            inline const double longitudePerihelion = normalizeDegrees(longitudeAphelion - 180.);  // degrees
            inline constexpr double longitudeSemiMajorAxis = 180.;                                 // degrees

            inline const sf::Angle argumentOfVelocityForAphelion = argumentOfVelocityAtTrueAnomaly(longitudeAphelion, eccentricity, longitudePerihelion);
            inline const sf::Angle argumentOfVelocityForPerihelion = argumentOfVelocityAtTrueAnomaly(longitudePerihelion, eccentricity, longitudePerihelion);
            inline const sf::Angle argumentOfVelocityForSemiMajorAxis = argumentOfVelocityAtTrueAnomaly(longitudeSemiMajorAxis, eccentricity, longitudePerihelion);

            inline const sf::Vector2<double> aphelionVelocity = sf::Vector2<double>(-6.49 * 1000., argumentOfVelocityForAphelion);            // {m per s, degrees}
            inline const sf::Vector2<double> perihelionVelocity = sf::Vector2<double>(-7.14 * 1000., argumentOfVelocityForPerihelion);        // {m per s, degrees}
            inline const sf::Vector2<double> semiMajorAxisVelocity = sf::Vector2<double>(-6.80 * 1000., argumentOfVelocityForSemiMajorAxis);  // {m per s, degrees}

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

            inline constexpr double eccentricity = 0.0087;

            // heliocentric rectangular coordinate system
            inline constexpr double startBaseRealX = 0.;
            inline constexpr double startBaseRealY = semiMajorAxis;  // au

            // heliocentric ecliptic coordinate system
            inline constexpr double longitudeAphelion = 224.97;                                    // degrees
            inline const double longitudePerihelion = normalizeDegrees(longitudeAphelion - 180.);  // degrees
            inline constexpr double longitudeSemiMajorAxis = 180.;                                 // degrees

            inline const sf::Angle argumentOfVelocityForAphelion = argumentOfVelocityAtTrueAnomaly(longitudeAphelion, eccentricity, longitudePerihelion);
            inline const sf::Angle argumentOfVelocityForPerihelion = argumentOfVelocityAtTrueAnomaly(longitudePerihelion, eccentricity, longitudePerihelion);
            inline const sf::Angle argumentOfVelocityForSemiMajorAxis = argumentOfVelocityAtTrueAnomaly(longitudeSemiMajorAxis, eccentricity, longitudePerihelion);

            inline const sf::Vector2<double> aphelionVelocity = sf::Vector2<double>(5.40 * 1000., argumentOfVelocityForAphelion);             // {m per s, degrees}
            inline const sf::Vector2<double> perihelionVelocity = sf::Vector2<double>(5.50 * 1000., argumentOfVelocityForPerihelion);         // {m per s, degrees}
            inline const sf::Vector2<double> semiMajorAxisVelocity = sf::Vector2<double>(5.45 * 1000., argumentOfVelocityForSemiMajorAxis);  // {m per s, degrees}

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

        // heliocentric rectangular coordinate system
        inline constexpr double startBaseRealX = 0.;
        inline constexpr double startBaseRealY = semiMajorAxis;  // au

        // heliocentric ecliptic coordinate system
        inline constexpr double longitudeAphelion = 44.07;                                     // degrees
        inline const double longitudePerihelion = normalizeDegrees(longitudeAphelion - 180.);  // degrees
        inline constexpr double longitudeSemiMajorAxis = 180.;                                 // degrees

        inline const sf::Angle argumentOfVelocityForAphelion = argumentOfVelocityAtTrueAnomaly(longitudeAphelion, eccentricity, longitudePerihelion);
        inline const sf::Angle argumentOfVelocityForPerihelion = argumentOfVelocityAtTrueAnomaly(longitudePerihelion, eccentricity, longitudePerihelion);
        inline const sf::Angle argumentOfVelocityForSemiMajorAxis = argumentOfVelocityAtTrueAnomaly(longitudeSemiMajorAxis, eccentricity, longitudePerihelion);

        inline const sf::Vector2<double> aphelionVelocity = sf::Vector2<double>(3.71 * 1000., argumentOfVelocityForAphelion);            // {m per s, degrees}
        inline const sf::Vector2<double> perihelionVelocity = sf::Vector2<double>(6.11 * 1000., argumentOfVelocityForPerihelion);        // {m per s, degrees}
        inline const sf::Vector2<double> semiMajorAxisVelocity = sf::Vector2<double>(4.74 * 1000., argumentOfVelocityForSemiMajorAxis);  // {m per s, degrees}

        inline constexpr double mass = 0.0022;  // Earth masses

        inline constexpr double realR = 1188.3;  // km
        inline constexpr float pixelRadius = 20.f;
        inline constexpr float minPixelRadius = 1.f;

        inline constexpr sf::Color color(255, 241, 213);
        }
    }

    namespace Camera {
        inline constexpr double targetPixels = 200.;  // between Sun and Mercury
        inline const double scale = targetPixels / (Config::CB::Mercury::semiMajorAxis * Config::Coefs::AU_TO_M);  //  px/m (m to px)
        inline constexpr float minRelScale = 0.007f;  // 0.4f
        inline constexpr float maxRelScale = 35.f;
    }
}