#include <api/Com.h>

my::Com::Com() : rec::robotino::api2::Com() {}

void my::Com::errorEvent(const char *error) {
    std::cerr << "Error: " << error << std::endl;
}

void my::Com::connectedEvent() {
    std::cout << "Connected." << std::endl;
}

void my::Com::connectionClosedEvent() {
    std::cout << "Connection closed." << std::endl;
}
