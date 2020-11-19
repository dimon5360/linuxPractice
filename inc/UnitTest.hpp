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
    ERR_QUEUE_EXCHANGE_FAILED,
    ERR_DB_CONNECTION_FAILED,
    ERR_SERVER_START_FAILED,

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
#if UNIT_TEST_DATA_PROCESSOR_QUEUE
    void test_DataProcessorQueueExchange();
#endif /* UNIT_TEST_DATA_PROCESSOR_QUEUE */

#if UNIT_TEST_DATA_BASE_QUEUE
    void test_DataBaseQueueExchange();
#endif /* UNIT_TEST_DATA_BASE_QUEUE */

#if UNIT_TEST_DATA_BASE_CONNECTION
    void test_DataBasePgConnection();
#endif /* UNIT_TEST_DATA_PROCESSOR_QUEUE */

#if UNIT_TEST_WEBSOCKET_SERVER
    void test_WebSocketServer();
#endif /* UNIT_TEST_WEBSOCKET_SERVER */

#if UNIT_TEST_JSON_HANDLER
    void test_JsonHandler();
#endif /* UNIT_TEST_JSON_HANDLER */

};

extern void StartUnitTesting(void);