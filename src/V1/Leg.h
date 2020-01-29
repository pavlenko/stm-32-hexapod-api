//
// Created by master on 29.01.20.
//

#ifndef LEG_H
#define LEG_H

#include "geometry.h"

namespace Hexapod {
    class Leg {
    private:
        Point3D _mount;

    private:
        /**
         * Convert angles to target point
         *
         * @param angles
         * @param target
         */
        static void _fwdKinematics(const float angles[3], Point3D &target);

        /**
         * Convert target point to angles
         *
         * @param target
         * @param angles
         */
        static void _invKinematics(const Point3D &target, float angles[3]);

    public:
        /**
         * Configurable constructor
         *
         * @param mount
         */
        Leg(Point3D &mount);
    };
}

#endif //LEG_H
