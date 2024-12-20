#include "move/movements.h"

extern my::Com com;
extern my::Bumper bumper;
extern robotino::OmniDrive omniDrive;

/**
 * Установка скорости в заданном направлении в ГСК
 */
void setVelocity(cv::Point2f &start, cv::Point2f &end, float speed) {
    float angle = getAngleFromImage() + ADDITIONAL_ANGLE;
    cv::Mat rotation({2, 2}, {
        cos(angle), sin(angle),
        -sin(angle), cos(angle)
    });
    cv::Mat position({2, 1}, {
        end.x - start.x,
        end.y - start.y
    });
    cv::Mat localCoordinates = rotation * position;
    float dir[2] = {
        localCoordinates.at<float>(0),
        localCoordinates.at<float>(0)
    };

    auto len = sqrt(dir[0]*dir[0] + dir[1]*dir[1]);

    float vel[2] = {
        dir[0] / len * speed,
        dir[1] / len * speed
    };
    omniDrive.setVelocity(vel[0], vel[1], 0);
}

float distance(cv::Point2f &start, cv::Point2f &end) {
    auto x = (end.x - start.x);
    auto y = (end.y - start.y);
    return sqrt(x * x + y * y);
}