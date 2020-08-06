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

#if UNIT_TESTS_ENABLE

/* user classes */
#include "UnitTest.hpp"
#include "DDataProcessor.hpp"
#include "DDataBase.hpp"

/* C++ std lib headers */
#include <memory>
#include <thread>
#include <string>

/* utils for unit test class ----------------------------------------------- */
/**
 * @brief Print unit tests result 
 */
void UUnitTest::PrintUnitTestErrorCode(void) {
#if UNIT_TEST_CALLED_FUNCTION
    std::cout << std::endl << __func__ << "()" << std::endl;
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
#if UNIT_TEST_DATA_PROCESSOR_QUEUE  
        test_DataProcessorQueueExchange();
        if(unitTestResult != err_type_ut::ERR_OK) {
            PrintUnitTestErrorCode();
            return;
        }
#endif /* UNIT_TEST_DATA_PROCESSOR_QUEUE */

#if UNIT_TEST_DATA_BASE_QUEUE
        test_DataBaseQueueExchange();
        if(unitTestResult != err_type_ut::ERR_OK) {
            PrintUnitTestErrorCode();
            return;
        }
#endif /* UNIT_TEST_DATA_BASE_QUEUE */

#if UNIT_TEST_DATA_BASE_CONNECTION
        test_DataBasePgConnection();
        if(unitTestResult != err_type_ut::ERR_OK) {
            PrintUnitTestErrorCode();
            return;
        }
#endif /* UNIT_TEST_DATA_BASE_CONNECTION */

#if UNIT_TEST_WEBSOCKET_SERVER
        test_WebSocketServer();
        if(unitTestResult != err_type_ut::ERR_OK) {
            PrintUnitTestErrorCode();
            return;
        }
#endif /* UNIT_TEST_WEBSOCKET_SERVER */
#if UNIT_TEST_DEBUG_INFO
        std::cout << "Unit testing result succed." << std::endl;
#endif /* UNIT_TEST_DEBUG_INFO */
    }
}  

/* start of unit testing  -------------------------------------------------- */

//-----------------------------------------------------------------------------
#if UNIT_TEST_DATA_PROCESSOR_QUEUE
/***
 *  @brief  Test an exchange of data using std::queue
 */
void UUnitTest::test_DataProcessorQueueExchange() {
#if UNIT_TEST_CALLED_FUNCTION
    std::cout << std::endl << __func__ << "()" << std::endl;
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
#endif /* UNIT_TEST_DATA_PROCESSOR_QUEUE */

//-----------------------------------------------------------------------------
#if UNIT_TEST_DATA_BASE_QUEUE
/***
 *  @brief  Test a data exchange through std::queue
 */
void UUnitTest::test_DataBaseQueueExchange() {
#if UNIT_TEST_CALLED_FUNCTION
    std::cout << std::endl << __func__ << "()" << std::endl;
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
#endif /* UNIT_TEST_DATA_BASE_QUEUE */

//-----------------------------------------------------------------------------
#if UNIT_TEST_DATA_BASE_CONNECTION
/***
 *  @brief  Test the connection to main db
 */
void UUnitTest::test_DataBasePgConnection() {
#if UNIT_TEST_CALLED_FUNCTION
    std::cout << std::endl << __func__ << "()" << std::endl;
#endif /* UNIT_TEST_CALLED_FUNCTION */

    std::unique_ptr<DDatabase> db = std::make_unique<DDatabase>();

    if(db->GetConnectionStatus()) {
        unitTestResult = err_type_ut::ERR_OK;
    } else {
        unitTestResult = err_type_ut::ERR_DB_CONNECTION_FAILED;
    }
}
#endif /* UNIT_TEST_DATA_BASE_CONNECTION */

//------------------------------------------------------------------------------
#if UNIT_TEST_WEBSOCKET_SERVER
/* C++ boost lib headers */
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <cstdlib>
#include <functional>

using tcp = boost::asio::ip::tcp;               // from <boost/asio/ip/tcp.hpp>
namespace websocket = boost::beast::websocket;  // from <boost/beast/websocket.hpp>

// Echoes back all received WebSocket messages
void do_session(tcp::socket& socket)
{
    try
    {
        // Construct the stream by moving in the socket
        websocket::stream<tcp::socket> ws{std::move(socket)};

        // Accept the websocket handshake
        ws.accept();

        for(;;)
        {
            // This buffer will hold the incoming message
            boost::beast::multi_buffer buffer;

            // Read a message
            ws.read(buffer);

            // Echo the message back
            ws.text(ws.got_text());
            ws.write(buffer.data());
        }
    }
    catch(boost::system::system_error const& se)
    {
        // This indicates that the session was closed
        if(se.code() != websocket::error::closed)
            std::cerr << "Error: " << se.code().message() << std::endl;
    }
    catch(std::exception const& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

/***
 *  @brief  Test creatition of WebSocket server
 */
void UUnitTest::test_WebSocketServer() {
#if UNIT_TEST_CALLED_FUNCTION
    std::cout << std::endl << __func__ << "()" << std::endl;
#endif /* UNIT_TEST_CALLED_FUNCTION */

    try {

        auto const address = boost::asio::ip::make_address("0.0.0.0");
        auto const port = static_cast<unsigned short>(std::atoi("40400"));

        // The io_context is required for all I/O
        boost::asio::io_context ioc{1};

        // The acceptor receives incoming connections
        tcp::acceptor acceptor{ioc, {address, port}};
        for(;;)
        {
            // This will receive the new connection
            tcp::socket socket{ioc};

            // Block until we get a connection
            acceptor.accept(socket);

            // Launch the session, transferring ownership of the socket
            std::thread{std::bind(
                &do_session,
                std::move(socket))}.detach();
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;    
        unitTestResult = err_type_ut::ERR_SERVER_START_FAILED;
    }
    
    unitTestResult = err_type_ut::ERR_OK;
}
#endif /* UNIT_TEST_WEBSOCKET_SERVER */

#endif /* UNIT_TESTS_ENABLE */