#pragma once
#include "rec/robotino/api2/all.h"
#include <iostream>

namespace my {

class Bumper : public rec::robotino::api2::Bumper {
  public:
    Bumper();
    void bumperEvent(bool hasContact) override;

    bool bumped = false;
};

} // namespace my