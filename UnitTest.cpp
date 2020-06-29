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

/* C++ std lib headers */
#include <memory>
#include <thread>
#include <string>

/* utils for unit test class ----------------------------------------------- */
/**
 * @brief Print unit tests result 
 */
void UUnitTest::PrintUnitTestErrorCode(void) {
    static std::string head = "Unit test result failed with error ";
    std::cout << head << boost::format("%u") % static_cast<uint32_t>(unitTestResult) << std::endl;
}

UUnitTest::UUnitTest() {
    std::cout << "Unit test class object created." << std::endl;
    unitTestResult = err_type_ut::ERR_OK;

    {        
        test_DataProcessorQueueExchange();
        if(unitTestResult != err_type_ut::ERR_OK) {
            PrintUnitTestErrorCode();
            return;
        }

        std::cout << "Unit testing result succed." << std::endl;
    }
}  

/* start of unit testing  -------------------------------------------------- */

void UUnitTest::test_DataProcessorQueueExchange() {
    std::shared_ptr<DDataProcessor> d = std::make_shared<DDataProcessor>();

    d->pushInQueue("adcdefg");
    while(true) {
        std::cout << "unit test ." << std::endl;
        if(!d->isOutQueueEmpty()) {
            d->pullOutQueue();
            unitTestResult = err_type_ut::ERR_OK;
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(THREAD_TIMEOUT));
    }
    
    std::cout << "Exit from the test." << std::endl;
}

