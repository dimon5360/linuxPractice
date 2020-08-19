/**
 *  @file SServer.cpp
 *  @brief Class of TCP server
 *
 *  @author Kalmykov Dmitry
 *
 *  @version 0.1
 *  @date 30.05.2020
 */

/* local headers */
#include "main.h"
#include "config.h"
#include "SServer.hpp"

/* Boost C++ headers */
#include <boost/format.hpp>

/* std C++ headers */
#include <iostream>

using namespace boost::asio;

typedef boost::shared_ptr<ip::tcp::socket> socket_ptr;

/* Handler for client session */
static void client_session(socket_ptr sock);

/**
 * @brief This data must be transfered first
 */
std::string make_datetime_string(void) {

    using namespace std;
    time_t now = time(0);
    return ctime(&now);
}


/**
 * @brief SServer class constructor
 */
SServer::SServer() {
#if TCP_SERVER_CALLED_FUNCTION
    std::cout << __func__ << "()" << std::endl;
#endif /* TCP_SERVER_CALLED_FUNCTION */

    try {

        std::cout << "Object of SServer class created." << std::endl;
        
        // initialize io service
        io_service service;
        // listen port 40400 ipV4
        ip::tcp::endpoint ep(ip::address::from_string("127.0.0.1"), 40401);
        // create an acceptor
        ip::tcp::acceptor acc(service, ep);

        std::stringstream ss;

        while(true) {
            // create new socket obj and put in reference
            socket_ptr sock(new ip::tcp::socket(service));
            // accept a connection for new client
            acc.accept(*sock);

            std::cout << "Client accepted.\n"; 

            std::string message = make_datetime_string();
            

            ss  << "HTTP/1.1 200 OK" << message;

            std::cout << "Connection time: " << ss.str() << std::endl; 

            boost::system::error_code ignored_code;

            boost::asio::write(*sock, boost::asio::buffer(ss.str()), ignored_code);

            // create single thread for new client connection
            // boost::thread(boost::bind(client_session, sock));
            // std::cout << "Client accepted\n";
            
            boost::this_thread::sleep_for(boost::chrono::milliseconds(THREAD_TIMEOUT));
        }
    }
    catch(std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

/**
 * @brief SServer class destructor
 */
SServer::~SServer() {
#if TCP_SERVER_CALLED_FUNCTION
    std::cout << __func__ << "()" << std::endl;
#endif /* TCP_SERVER_CALLED_FUNCTION */
    
    std::cout << "Object of SServer class removed." << std::endl;
    
}

static void client_session(socket_ptr sock) {
    std::cout << __func__ << "()" << std::endl;
    char data[1024];
    
    while(true) {
        // TODO: realize async readingc
        // try {
        //     size_t len = sock->read_some(buffer(data));
        //     if (len > 0) {
        //         std::cout << std::string(data) << std::endl;
        //         write(*sock, buffer("ok", 2));
        //     }
        // }
        // catch (const std::exception& ex) {
        //     std::cout << ex.what() << std::endl;
        //     break;
        // }
        boost::this_thread::sleep_for(boost::chrono::milliseconds(THREAD_TIMEOUT));
    }
}