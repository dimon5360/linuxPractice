/**
 *  @file main.cpp
 *  @brief Main module in uTrainProject
 *
 *  @author Kalmykov Dmitry
 *
 *  @version 0.1
 *  @date 01.06.2020
 */

/* local headers */
#include "config.h"
#include "main.h"
#include "UnitTest.hpp"

/* std C++ headers */
#include <iostream>
#include <ctime>


using namespace boost::asio;

typedef boost::shared_ptr<ip::tcp::socket> socket_ptr;

/* Print application information */
static void PrintAppInfo(void);

int main() {

    PrintAppInfo();

#if UNIT_TESTS_ENABLE
    StartUnitTesting();
#endif /* UNIT_TESTS_ENABLE */
    

    /* TODO: need to realize server class */
    return 0;
}

static void PrintAppInfo(void) {
    std::cout << "Application version " << 
    boost::format("%u.%u.%u") % MAJOR % MINOR % BUILD << std::endl;

    const std::time_t result = std::time(nullptr);
    std::cout << std::asctime(std::localtime(&result)) << std::endl;

    std::cout << "Application started." << std::endl;
    std::cout << "===================================\n" << std::endl;
}