#include <api/Com.h>
#include <iostream>

int main() {
    std::cout << "START OF THE PROGRAM" << std::endl;

    std::string ipAddress = "192.168.0.1";
    my::Com com;

    try {
        std::cout << "Connect to " << ipAddress << std::endl;
        com.setAddress(ipAddress.c_str());
        com.connectToServer();

        std::cout << "Connected successfully!" << std::endl;
        // some work here

        std::cout << "Disconnect from server." << std::endl;
        com.disconnectFromServer();
    } catch (const rec::robotino::api2::RobotinoException &e) {
        std::cerr << "Unable to connect to " << com.address() << '\n';
        std::cerr << e.what() << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << '\n';
    }

    rec::robotino::api2::shutdown();
    return 0;
}