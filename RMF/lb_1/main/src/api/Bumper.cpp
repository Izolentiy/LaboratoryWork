#include <api/Bumper.h>

my::Bumper::Bumper() : rec::robotino::api2::Bumper() {}

void my::Bumper::bumperEvent(bool hasContact) {
    this->bumped |= hasContact;
    std::cout << "Bumper has " << (hasContact ? "contact" : "no contact") << std::endl;
}