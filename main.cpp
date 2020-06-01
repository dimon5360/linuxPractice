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
    
    int res = 0;
    res = StartUnitTesting();
    std::cout << "Unit testing result is " << res << std::endl;

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