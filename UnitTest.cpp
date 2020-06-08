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
 * @brief Static function which must be called for async print data in console
 */
void AsyncOutData(const boost::system::error_code& /*e*/) {
    std::cout << __func__ << "()" << std::endl;
}

void AsyncOutData0(const boost::system::error_code& /*e*/,
    boost::asio::steady_timer* t, int* count) {
    std::cout << __func__ << "()" << std::endl;
    if (*count > 0)
    {
        std::cout << *count << std::endl;
        --(*count);

        t->expires_at(t->expiry() + boost::asio::chrono::seconds(1));
        t->async_wait(boost::bind(AsyncOutData0,
            boost::asio::placeholders::error, t, count));
    }
}

void AsyncOutData1(const boost::system::error_code& /*e*/,
    boost::asio::steady_timer* t, int* count) {
    std::cout << __func__ << "()" << std::endl;
    if (*count < 5)
    {
        std::cout << *count << std::endl;
        ++(*count);

        t->expires_at(t->expiry() + boost::asio::chrono::seconds(1));
        t->async_wait(boost::bind(AsyncOutData1,
            boost::asio::placeholders::error, t, count));
    }
}

class printer {
public:
    /* default constructor */
    // printer(boost::asio::io_context& io)
    //     : timer_(io, boost::asio::chrono::seconds(1)),
    //       count_(0) {
    //         timer_.async_wait(boost::bind(&printer::print, this));
    // }

    /* overloaded constructor */
    printer(boost::asio::io_context& io)
        : strand_(boost::asio::make_strand(io)),
          timer1_(io, boost::asio::chrono::seconds(1)),
          timer2_(io, boost::asio::chrono::seconds(1)),

          count_(0) {

            timer1_.async_wait(boost::asio::bind_executor(strand_,
            boost::bind(&printer::print1, this)));

            timer2_.async_wait(boost::asio::bind_executor(strand_,
            boost::bind(&printer::print2, this)));
    }

    ~printer() {
        std::cout << "Final count is " << count_ << std::endl;
    }

    // void print() {
    //     if(count_ < 5) {
    //         std::cout << count_ << std::endl;
    //         ++count_;
            
    //         timer_.expires_at(timer_.expiry() + boost::asio::chrono::seconds(1));
    //         timer_.async_wait(boost::bind(&printer::print, this));
    //     }
    // }

    void print1()
    {
        if (count_ < 10)
        {
        std::cout << "Timer 1: " << count_ << std::endl;
        ++count_;

        timer1_.expires_at(timer1_.expiry() + boost::asio::chrono::seconds(1));

        timer1_.async_wait(boost::asio::bind_executor(strand_,
                boost::bind(&printer::print1, this)));
        }
    }

    void print2()
    {
        if (count_ < 10)
        {
        std::cout << "Timer 2: " << count_ << std::endl;
        ++count_;

        timer2_.expires_at(timer2_.expiry() + boost::asio::chrono::seconds(1));

        timer2_.async_wait(boost::asio::bind_executor(strand_,
                boost::bind(&printer::print2, this)));
        }
    }

private:
    boost::asio::strand<boost::asio::io_context::executor_type> strand_;
    boost::asio::steady_timer timer1_;
    boost::asio::steady_timer timer2_;
    // boost::asio::steady_timer timer_;
    int count_;
}; 

/**
 * @brief Unit test of asynchronous output data to console
 */
void UUnitTest::TestAsyncConsoleOutput(void) {
 
    boost::asio::io_context io;

    printer p(io);
    
    boost::thread t(boost::bind(&boost::asio::io_context::run, &io));

    io.run();

    t.join();

    std::cout << "Test finished." << std::endl;

    unitTestResult = ERR_OK;
}

