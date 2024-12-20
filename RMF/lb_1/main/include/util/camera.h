#pragma once
#include <opencv2/opencv.hpp>

#define ESTIMATE_POSE false
#define CAMERA_INDEX 0
#define CAMERA_DELAY 0
#define MARKER_LENGTH 0.1766f
#define PROGRAM_NAME "Summer practice"
#define IMAGE_PATH "C:\\Users\\Admin\\Pictures\\Camera Roll\\WIN_20240712_15_20_46_Pro.jpg"
#define ESCAPE_KEY 27

void processCameraImage();
cv::Point2f getCoordinatesFromImage();
float getAngleFromImage();