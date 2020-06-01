
#include "UnitTest.hpp"

#include "SServer.hpp"

#include <memory>

int StartUnitTesting(void) {

    std::shared_ptr<SServer> tcpServer = std::make_shared<SServer>();

    return 0;
}