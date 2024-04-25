#pragma once
#include "rec/robotino/api2/all.h"
#include <iostream>

namespace my {

class Com : public rec::robotino::api2::Com {
  public:
    Com();
    void errorEvent(const char *error) override;
    void connectedEvent() override;
    void connectionClosedEvent() override;
};

} // namespace my
