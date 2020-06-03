
#include "UnitTest.hpp"

#include "SServer.hpp"
#include "DDatabase.hpp"

#include <memory>

int StartUnitTesting(void) {

    std::shared_ptr<SServer> tcpServer = std::make_shared<SServer>();

    std::shared_ptr<DDatabase> database = std::make_shared<DDatabase>();

    return 0;
}