#include <api/Com.h>
#include <iostream>

int main() {
    std::cout << "START OF THE PROGRAM" << std::endl;

    std::string ipAddress = "192.168.0.1";
    my::Com com;

    std::cout << "Connect to " << ipAddress << std::endl;
    com.setAddress(ipAddress.c_str());
    try {
        com.connectToServer();
    } catch (const std::exception &e) {
        std::cerr << "Unable to connect to " << com.address() << '\n';
        std::cerr << e.what() << std::endl;
        rec::robotino::api2::shutdown();
        exit(1);
    }
    std::cout << "Connected successfully!" << std::endl;

    std::cout << "Disconnect from server." << std::endl;
    com.disconnectFromServer();
    rec::robotino::api2::shutdown();
    return 0;
}