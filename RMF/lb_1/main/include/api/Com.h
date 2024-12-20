#pragma once
#include <rec/robotino/api2/Com.h>
#include <iostream>

namespace robotino = rec::robotino::api2;
namespace my {

class Com : public robotino::Com {
  public:
    Com();
    void errorEvent(const char *error) override;
    void connectedEvent() override;
    void connectionClosedEvent() override;
};

} // namespace my
