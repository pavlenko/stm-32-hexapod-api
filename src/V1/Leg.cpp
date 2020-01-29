//
// Created by master on 29.01.20.
//

#include "Leg.h"

#include <cmath>

#include "config.h"

Hexapod::Leg::Leg(Point3D &mount): _mount(mount) {}

void Hexapod::Leg::_fwdKinematics(const float *angles, Point3D &target)
{
    float radian[3];

    for (int i = 0; i < 3; i++) {
        radian[i] = DEG_TO_RAD(angles[i]);
    }

    float x = kLegJoint1ToJoint2 + std::cos(radian[1]) * kLegJoint2ToJoint3 + std::cos(radian[1] + radian[2] - hpi) * kLegJoint3ToTip;

    target.x = kLegRootToJoint1 + std::cos(radian[0]) * x;
    target.y = std::sin(radian[0]) * x;
    target.z = std::sin(radian[1]) * kLegJoint2ToJoint3 + std::sin(radian[1] + radian[2] - hpi) * kLegJoint3ToTip;
}

//void leg_point_to_angles(leg_point_t *point, leg_angles_t *angles)
//{
//    /* Calculate horizontal distance in millimeters */
//    float h_distance = hypot((*point).x, (*point).y);
//
//    /* Calculate coxa angle in radians */
//    float c_angle = atan((*point).y / (*point).x) + M_PI_2;
//
//    /* Calculate vertical distance in millimeters */
//    float v_distance = sqrt(SQR(h_distance - S_THICKNESS) + SQR(hp_body_height - (*point).z));
//
//    /* Calculate femur add angle from z to v_distance axis in radians */
//    float f_add_angle = atan((h_distance - S_THICKNESS) / (hp_body_height - (*point).z));
//
//    /* Calculate femur angle in radians */
//    float f_angle = acos((SQR(F_LENGTH) + SQR(v_distance) - SQR(T_LENGTH)) / (2 * F_LENGTH * v_distance)) + f_add_angle;
//
//    /* Calculate tiba angle in radians */
//    float t_angle = acos((SQR(T_LENGTH) + SQR(F_LENGTH) - SQR(v_distance)) / (2 * T_LENGTH * F_LENGTH));
//
//    (*angles).c = (uint16_t) RAD_TO_DEG(c_angle);
//    (*angles).f = (uint16_t) RAD_TO_DEG(f_angle);
//    (*angles).t = (uint16_t) RAD_TO_DEG(t_angle);
//}
void Hexapod::Leg::_invKinematics(const Point3D &target, float *angles)
{
    float x = to.x_ - kLegRootToJoint1;
    float y = to.y_;

    angles[0] = RAD_TO_DEG(std::atan2(y, x));

    x = std::sqrt(x*x + y*y) - kLegJoint1ToJoint2;
    y = to.z_;
    float ar = std::atan2(y, x);
    float lr2 = x*x + y*y;
    float lr = std::sqrt(lr2);
    float a1 = std::acos((lr2 + kLegJoint2ToJoint3*kLegJoint2ToJoint3 - kLegJoint3ToTip*kLegJoint3ToTip)/(2*kLegJoint2ToJoint3*lr));
    float a2 = std::acos((lr2 - kLegJoint2ToJoint3*kLegJoint2ToJoint3 + kLegJoint3ToTip*kLegJoint3ToTip)/(2*kLegJoint3ToTip*lr));

    angles[1] = RAD_TO_DEG((ar + a1));
    angles[2] = 90 - RAD_TO_DEG((a1 + a2));
}
