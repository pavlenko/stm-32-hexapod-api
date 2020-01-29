//
// Created by master on 29.01.20.
//

#ifndef CONFIG_H
#define CONFIG_H

// For circular body:
// radius: 170mm
// h = sqrt(170*170 - 85*85) = sqrt(28900 - 7225) = sqrt(21675) = 147,22


namespace Hexapod {
    // Mount for front left leg
    const float LEG_MOUNT_FL_X = -85.0;
    const float LEG_MOUNT_FL_Y = 147.2;
    const float LEG_MOUNT_FL_Z = 0.0;

    // Mount for front right leg
    const float LEG_MOUNT_FR_X = 85.0;
    const float LEG_MOUNT_FR_Y = 147.2;
    const float LEG_MOUNT_FR_Z = 0.0;

    // Mount for middle left leg
    const float LEG_MOUNT_ML_X = -170.0;
    const float LEG_MOUNT_ML_Y = 0.0;
    const float LEG_MOUNT_ML_Z = 0.0;

    // Mount for middle right leg
    const float LEG_MOUNT_MR_X = 170.0;
    const float LEG_MOUNT_MR_Y = 0.0;
    const float LEG_MOUNT_MR_Z = 0.0;

    // Mount for rear left leg
    const float LEG_MOUNT_RL_X = -85.0;
    const float LEG_MOUNT_RL_Y = -147.2;
    const float LEG_MOUNT_RL_Z = 0.0;

    // Mount for rear left leg
    const float LEG_MOUNT_RR_X = 85.0;
    const float LEG_MOUNT_RR_Y = -147.2;
    const float LEG_MOUNT_RR_Z = 0.0;

    //TODO measure real values
    const float LEG_LENGTH_COXA  = 12.0;
    const float LEG_LENGTH_FEMUR = 80.0;
    const float LEG_LENGTH_TIBA  = 80.0;
}

#endif //CONFIG_H
