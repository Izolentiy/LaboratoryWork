#include "api/Bumper.h"
#include "api/Com.h"
#include "move/movements.h"
#include "util/logs.h"
#include "util/camera.h"
#include <rec/robotino/api2/RobotinoException.h>
#include <vector>

namespace robotino = rec::robotino::api2;
robotino::OmniDrive omniDrive;
my::Com com;
my::Bumper bumper;

uint32_t robotStartTime;
extern int pressedKey;

void squareMovementUsingCamera(std::ostream &log) {
    auto elapsed = 0;
    auto moveTimer = robotStartTime;

    cv::Point2f points[4] = {
        cv::Point2f(200, 200),
        cv::Point2f(200, 400),
        cv::Point2f(400, 400),
        cv::Point2f(400, 200)
    };
    auto i = 0;
    auto end = points[i];
    processCameraImage();
    auto start = getCoordinatesFromImage();
    
    while (!bumper.value() && com.isConnected() && pressedKey != ESCAPE_KEY) {
        elapsed = com.msecsElapsed() - moveTimer;
        if (elapsed > VELOCITY_UPDATE_LATENCY) {
            processCameraImage();
            start = getCoordinatesFromImage();
            
            std::cout << "Robot position: " << start << '\n';
            if (distance(start, end) < 3) {
                end = points[i];
                if (++i == 4) i = 0;
            }
            setVelocity(start, end, 0.1f);
            logRobotinoState(log);
            elapsed = 0;
            moveTimer = com.msecsElapsed();
        }
    }
}

int main() {
    std::cout << "START OF THE PROGRAM" << std::endl;

    std::string ipAddress = "192.168.0.1";
    std::ofstream log(getLogPath());

    try {
        std::cout << "Connect to " << ipAddress << std::endl;
        com.setAddress(ipAddress.c_str());
        com.connectToServer();
        robotStartTime = com.msecsElapsed();

        squareMovementUsingCamera(log);

        std::cout << "Disconnect from " << ipAddress << std::endl;
        com.disconnectFromServer();
    } catch (const robotino::RobotinoException &e) {
        std::cerr << "Unable to connect to " << com.address() << '\n';
        std::cerr << e.what() << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << '\n';
    }

    log.close();
    robotino::shutdown();

    return 0;
}