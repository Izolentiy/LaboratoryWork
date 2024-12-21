#pragma once
#include "api/Com.h"
#include "api/Bumper.h"
#include "util/camera.h"
#include <rec/robotino/api2/OmniDrive.h>
#include <rec/robotino/api2/utils.h>
#include <opencv2/opencv.hpp>

#define PI 3.14159265
#define VELOCITY_UPDATE_LATENCY 100

void setVelocity(cv::Point2f &start, cv::Point2f &end, float speed);
float distance(cv::Point2f &start, cv::Point2f &end);