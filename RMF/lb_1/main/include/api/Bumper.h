#pragma once
#include <rec/robotino/api2/Bumper.h>
#include <rec/robotino/api2/ComId.h>
#include <iostream>

namespace robotino = rec::robotino::api2;
namespace my {

class Bumper : public robotino::Bumper {
  public:
    Bumper();
    Bumper(const robotino::ComId &id);
    void bumperEvent(bool hasContact) override;
};

} // namespace my