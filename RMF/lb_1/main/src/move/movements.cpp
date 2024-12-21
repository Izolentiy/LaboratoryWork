#include "move/movements.h"

extern my::Com com;
extern my::Bumper bumper;
extern robotino::OmniDrive omniDrive;

/**
 * Установка скорости в заданном направлении в ГСК
 */
void setVelocity(cv::Point2f &start, cv::Point2f &end, float speed) {
    float angle = getAngleFromImage() - PI / 6;
    auto dx = end.x - start.x;
    auto dy = end.y - start.y;
    auto x =  cos(angle) * dx + sin(angle) * dy;
    auto y = -sin(angle) * dx + cos(angle) * dy;

    auto len = sqrt(x * x + y * y);

    float vel[2] = {
        x / len * speed,
        y / len * speed
    };
    omniDrive.setVelocity(vel[0], vel[1], 0);
}

float distance(cv::Point2f &start, cv::Point2f &end) {
    auto x = (end.x - start.x);
    auto y = (end.y - start.y);
    return sqrt(x * x + y * y);
}