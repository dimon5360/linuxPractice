/*********************
 * @file UnitTest.hpp
 * @brief Class for unit tests
 * 
 * @author kalmykov Dmitry
 * 
 * @version 0.0.1 
 * @date 02.06.2020
 */

#pragma once

/* C++ std lib headers */
#include <iostream>

/* error codes for unit tests ---------------------------------------------- */
enum class err_type_ut {
    ERR_OK = 0,
    ERR_QUEUE_EXCHANGE_FAILED = 1,

    ERR_ALL_CODES_MOUNT
};

/* unit test class --------------------------------------------------------- */
class UUnitTest {
private: 
    err_type_ut unitTestResult;

public:
    /* unit test class constructor */
    UUnitTest();
    /* unit test class destructor */ 
    ~UUnitTest() {
        std::cout << "Unit test class object removed." << std::endl;
    }

    /* unit test utils ----------------------------------------------------- */
    /* print unit tests result */
    void PrintUnitTestErrorCode(void);

    /* unit tests ---------------------------------------------------------- */
    void test_DataProcessorQueueExchange();
};

extern void StartUnitTesting(void);