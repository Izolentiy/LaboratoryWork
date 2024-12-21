#include "util/logs.h"

bool headerInited = false;
extern my::Com com;
extern uint32_t robotStartTime;
rec::robotino::api2::Motor motor[MOTOR_COUNT];

std::filesystem::path getLogPath() {
    using std::filesystem::path;
    using std::filesystem::exists;

    path rootPath(ROOT_LOG_PATH);
    constexpr size_t dateSize = std::size("yyyy-mm-dd");
    constexpr size_t timeSize = std::size("hh-mm-ss");
    char folderName[dateSize], timeString[timeSize];
    std::time_t time = std::time({});

    std::strftime(folderName, dateSize, "%F", std::localtime(&time));
    std::strftime(timeString, timeSize, "%H-%M-%S", std::localtime(&time));
    std::string fileName = std::string(timeString) + ".csv";

    path folderPath = rootPath / folderName;
    if (!exists(folderPath)) {
        std::filesystem::create_directory(folderPath);
    }
    return folderPath / fileName;
}

void logRobotinoState(std::ostream &log) {
    if (!headerInited) {
        headerInited = true;
        log << LOG_HEADER;
        for (int i = 0; i < MOTOR_COUNT; ++i) {
            motor[i].setMotorNumber(i);
        }
    }
    unsigned time = com.msecsElapsed();
    log << time - robotStartTime << ';';
    for (int i = 0; i < MOTOR_COUNT; ++i) {
        log << motor[i].actualPosition() << ';';
    }
    for (int i = 0; i < MOTOR_COUNT; ++i) {
        log << motor[i].actualVelocity() << ';';
    }
    for (int i = 0; i < MOTOR_COUNT; ++i) {
        log << motor[i].motorCurrent() << ';';
    }
    log << '\n';
}