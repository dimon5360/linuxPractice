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
enum err_type_ut {
    ERR_OK = 0,

    ERR_ALL_CODES_MOUNT
};

/* unit test class --------------------------------------------------------- */
class UUnitTest {
private: 
    uint32_t unitTestResult;

public:
    /* unit test class constructor */
    UUnitTest() {
        std::cout << "Unit test class object created." << std::endl;
        unitTestResult = ERR_OK;
    }  
    /* unit test class destructor */ 
    ~UUnitTest() {
        std::cout << "Unit test class object removed." << std::endl;
    }

    /* unit test utils ----------------------------------------------------- */
    /* get unit tests result */
    uint32_t GetUnitTestResult(void);
    /* print unit tests result */
    void PrintUnitTestErrorCode(void);

    /* unit tests ---------------------------------------------------------- */
    void TestAsyncTcpServerInput(void);
};

extern void StartUnitTesting(void);