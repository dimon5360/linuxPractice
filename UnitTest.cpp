/**
 *  @file UnitTest.cpp
 *  @brief  Unit test class
 *
 *  @author Kalmykov Dmitry
 *
 *  @version 0.1
 *  @date 02.06.2020
 */

/* local headers */
#include "main.h"
#include "config.h"

/* user classes */
#include "UnitTest.hpp"
#include "DDataProcessor.hpp"
#include "DDataBase.hpp"

/* C++ std lib headers */
#include <memory>
#include <thread>
#include <string>

/* external lib for postgres database */
#include <postgresql/libpq-fe.h>

/* utils for unit test class ----------------------------------------------- */
/**
 * @brief Print unit tests result 
 */
void UUnitTest::PrintUnitTestErrorCode(void) {
#if UNIT_TEST_CALLED_FUNCTION
    std::cout << __func__ << "()" << std::endl;
#endif /* UNIT_TEST_CALLED_FUNCTION */

#if UNIT_TEST_DEBUG_INFO
    static std::string head = "Unit test result failed with error ";
    std::cout << head << boost::format("%u") % 
                static_cast<uint32_t>(unitTestResult) << std::endl;
#endif /* UNIT_TEST_DEBUG_INFO */
}

UUnitTest::UUnitTest() {
#if UNIT_TEST_CALLED_FUNCTION
    std::cout << __func__ << "()" << std::endl;
#endif /* UNIT_TEST_CALLED_FUNCTION */
    unitTestResult = err_type_ut::ERR_OK;

    {        
        test_DataProcessorQueueExchange();
        if(unitTestResult != err_type_ut::ERR_OK) {
            PrintUnitTestErrorCode();
            return;
        }

        test_DataBaseQueueExchange();
        if(unitTestResult != err_type_ut::ERR_OK) {
            PrintUnitTestErrorCode();
            return;
        }

        test_DataBaseConnection();
        if(unitTestResult != err_type_ut::ERR_OK) {
            PrintUnitTestErrorCode();
            return;
        }

#if UNIT_TEST_DEBUG_INFO
        std::cout << "Unit testing result succed." << std::endl;
#endif /* UNIT_TEST_DEBUG_INFO */
    }
}  

/* start of unit testing  -------------------------------------------------- */

/***
 *  @brief  Test an exchange of data using std::queue
 */
void UUnitTest::test_DataProcessorQueueExchange() {
#if UNIT_TEST_CALLED_FUNCTION
    std::cout << __func__ << "()" << std::endl;
#endif /* UNIT_TEST_CALLED_FUNCTION */
    std::unique_ptr<DDataProcessor> d = std::make_unique<DDataProcessor>();

    d->pushInQueue("abcdefg");
    while(true) {
        if(!d->isOutQueueEmpty()) {
            d->pullOutQueue();
            unitTestResult = err_type_ut::ERR_OK;
            return;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(THREAD_TIMEOUT));
    }
    unitTestResult = err_type_ut::ERR_QUEUE_EXCHANGE_FAILED;
}

/***
 *  @brief  Test a data exchange through std::queue
 */
void UUnitTest::test_DataBaseQueueExchange() {
#if UNIT_TEST_CALLED_FUNCTION
    std::cout << __func__ << "()" << std::endl;
#endif /* UNIT_TEST_CALLED_FUNCTION */
    std::unique_ptr<DDatabase> db = std::make_unique<DDatabase>();

    db->pushInQueue("123456789");
    while(true) {
        if(!db->isOutQueueEmpty()) {
            db->pullOutQueue();
            unitTestResult = err_type_ut::ERR_OK;
            return;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(THREAD_TIMEOUT));
    }
    unitTestResult = err_type_ut::ERR_QUEUE_EXCHANGE_FAILED;
}


/***
 *  @brief  Test the connection to main db
 */
void UUnitTest::test_DataBaseConnection() {
#if UNIT_TEST_CALLED_FUNCTION
    std::cout << __func__ << "()" << std::endl;
#endif /* UNIT_TEST_CALLED_FUNCTION */

    PGconn *conn;
    std::string req = "dbname=users_db host=localhost port=5432 user=admin password=admin1234";
    conn = PQconnectdb(req.c_str());

    if(PQstatus(conn) != CONNECTION_OK) {
        unitTestResult = err_type_ut::ERR_DB_CONNECTION_FAILED;
        std::cout << "Connection statis is " << PQerrorMessage(conn) << std::endl;
        PQfinish(conn);
    } else {
        unitTestResult = err_type_ut::ERR_OK;
    }
}