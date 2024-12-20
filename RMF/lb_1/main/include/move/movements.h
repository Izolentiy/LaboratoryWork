#pragma once
#include "api/Com.h"
#include "api/Bumper.h"
#include "util/camera.h"
#include <rec/robotino/api2/OmniDrive.h>
#include <rec/robotino/api2/utils.h>
#include <opencv2/opencv.hpp>

// ADDITIONAL_ANGLE = PI / 3
#define ADDITIONAL_ANGLE 1.0471975512
#define VELOCITY_UPDATE_LATENCY 100

void setVelocity(cv::Point2f &start, cv::Point2f &end, float speed);
float distance(cv::Point2f &start, cv::Point2f &end);