#include "util/camera.h"

using cv::aruco::ArucoDetector;
using cv::aruco::DICT_6X6_50;
using cv::aruco::getPredefinedDictionary;
ArucoDetector arucoDetector(getPredefinedDictionary(DICT_6X6_50));

float cameraIntrisics[9] = {
    15505.12f, 0.0f,    540.0f,
    0.0f,    15505.12f, 960.0f,
    0.0f,    0.0f,    1.0f
};
float distortionCoefs[4] = {
    -0.43948f, 0.18514f, 0.0f, 0.0f
};
cv::Vec3f objectPoints[4] = {
    cv::Vec3f(-MARKER_LENGTH / 2, MARKER_LENGTH / 2, 0),
    cv::Vec3f(MARKER_LENGTH / 2, MARKER_LENGTH / 2, 0),
    cv::Vec3f(MARKER_LENGTH / 2, -MARKER_LENGTH / 2, 0),
    cv::Vec3f(-MARKER_LENGTH / 2, -MARKER_LENGTH / 2, 0)
};

cv::VideoCapture video(CAMERA_INDEX, cv::CAP_DSHOW);
cv::Mat image;
cv::Mat camMatrix(3, 3, CV_32F, cameraIntrisics);
cv::Mat distCoeffs(4, 1, CV_32F, distortionCoefs);
cv::Mat objPoints(4, 1, CV_32FC3, objectPoints);
std::vector<std::vector<cv::Point2f>> corners;
std::vector<int> ids;

bool windowOpened = false;
int pressedKey = 0;

void processCameraImage() {
    bool windowWasOpened = windowOpened;
    auto flag = cv::WindowPropertyFlags::WND_PROP_VISIBLE;
    windowOpened = cv::getWindowProperty(PROGRAM_NAME, flag);

    if (windowWasOpened && !windowOpened) {
        throw std::runtime_error("Window was closed");
    } else if (!windowWasOpened) {
        cv::namedWindow(PROGRAM_NAME, cv::WINDOW_KEEPRATIO);
        windowOpened = true;
    }
    if (!video.read(image)) throw std::runtime_error("Unable to read image");
    
    auto initImage = image;
    arucoDetector.detectMarkers(image, corners, ids, cv::noArray());

    size_t nMarkers = corners.size();
    if (ids.empty()) {
        cv::imshow(PROGRAM_NAME, initImage);
        pressedKey = cv::waitKey(CAMERA_DELAY);
        return;
    }
    cv::aruco::drawDetectedMarkers(image, corners, ids);

    if (ESTIMATE_POSE) {
        std::vector<cv::Vec3f> rvecs(nMarkers), tvecs(nMarkers);
        for (size_t i = 0; i < nMarkers; ++i) {
            cv::solvePnP(
                objPoints, corners[i],
                camMatrix, distCoeffs,
                rvecs[i], tvecs[i]
            );
            cv::drawFrameAxes(
                image, 
                camMatrix, distCoeffs,
                rvecs[i], tvecs[i],
                MARKER_LENGTH * 1.5f, 2
            );
        }
    }
    
    cv::imshow(PROGRAM_NAME, image);
    pressedKey = cv::waitKey(CAMERA_DELAY);
}

float getAngleFromImage() {
    if (ids.empty()) {
        float nan = std::nanf("0");
        return nan;
    }
    auto cor = corners[0];
    float dx = cor[1].y - cor[0].y;
    float dy = cor[1].x - cor[0].x;
    return atan2f(dy, dx);
}

cv::Point2f getCoordinatesFromImage() {
    if (ids.empty()) {
        float nan = std::nanf("0");
        return cv::Point2f(nan, nan);
    }
    auto cor = corners[0];
    float centerX = (cor[0].y + cor[1].y + cor[2].y + cor[3].y) / 4;
    float centerY = (cor[0].x + cor[1].x + cor[2].x + cor[3].x) / 4;
    return cv::Point2f(centerX, centerY);    
}