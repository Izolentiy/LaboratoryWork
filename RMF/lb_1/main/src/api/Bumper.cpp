#include "api/Bumper.h"

my::Bumper::Bumper() : robotino::Bumper() {}

my::Bumper::Bumper(const robotino::ComId &id) : robotino::Bumper(id) {}

void my::Bumper::bumperEvent(bool hasContact) {
    std::cout << "Bumper has " << (hasContact ? "contact" : "no contact") << std::endl;
}