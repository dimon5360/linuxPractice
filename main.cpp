/* user libs  ------------------------------------------------------ */
#include "main.h"
#include <iostream>

// #include <boost/asio.hpp>
#include <boost/format.hpp>

/* Print application information */
static void PrintAppInfo(void);

int main() {

    PrintAppInfo();

    return 0;
}

static void PrintAppInfo(void) {
    std::cout << "Application version " << 
    boost::format("%u.%u.%u") % MAJOR % MINOR % BUILD << std::endl;
}