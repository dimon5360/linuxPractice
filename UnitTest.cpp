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
#include "config.h"
#include "main.h"

/* user classes */
#include "UnitTest.hpp"
#include "SServer.hpp"
#include "DDatabase.hpp"

/* C++ std lib headers */
#include <memory>

/* utils for unit test class ----------------------------------------------- */
/**
 * @brief Print unit tests result 
 */
void UUnitTest::PrintUnitTestErrorCode(void) {
    static std::string head = "Unit test result failed with error ";
    std::cout << head << boost::format("%u") % unitTestResult << std::endl;
}

/**
 * @brief Get unit test result 
 */
uint32_t UUnitTest::GetUnitTestResult(void) {
    return unitTestResult;
}

/* start of unit testing  -------------------------------------------------- */
void StartUnitTesting(void) {
    uint32_t errCode = ERR_OK;
    std::shared_ptr<UUnitTest> unittest = std::make_shared<UUnitTest>();

    // unit test for async print data to console
    unittest->TestAsyncConsoleOutput();
    if((errCode = unittest->GetUnitTestResult()) != ERR_OK) {
        unittest->PrintUnitTestErrorCode();            
        return;
    }

    std::cout << "Unit testing result succed." << std::endl;
}

/* unit tests -------------------------------------------------------------- */
/**
 * @brief Static function which muse be called for async print data in console
 */
static void AsyncOutData(void) {

}

/**
 * @brief Unit test of asynchronous output data to console
 */
void UUnitTest::TestAsyncConsoleOutput(void) {

    boost::asio::io_context io;

    boost::asio::steady_timer t(io, boost::asio::chrono::seconds(5));

    t.wait();

    std::cout << "Test finished." << std::endl;

    unitTestResult = ERR_OK;
}

