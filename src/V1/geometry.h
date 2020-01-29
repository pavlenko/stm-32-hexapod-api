//
// Created by master on 29.01.20.
//

#ifndef POINT3D_H
#define POINT3D_H

#define DEG_TO_RAD(_value_) (M_PI * _value_ / 180)
#define RAD_TO_DEG(_value_) (_value_ * 180 / M_PI)

class Point3D
{
public:
    float x;
    float y;
    float z;
public:
    /**
     * Default constructor
     */
    Point3D() = default;

    /**
     * Configurable constructor
     *
     * @param x
     * @param y
     * @param z
     */
    Point3D(float x, float y, float z): x(x), y(y), z(z) {}
};


#endif //POINT3D_H
