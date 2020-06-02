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
 * @brief SServer class constructor
 */
SServer::SServer() {
#if TCP_SERVER_CALLED_FUNCTION
    std::cout << __func__ << "()" << std::endl;
#endif /* TCP_SERVER_CALLED_FUNCTION */

    std::cout << "Object of SServer class created." << std::endl;

    // todo: remove return ****************************************************************
    return;
    
    io_service service;
    ip::tcp::endpoint ep(ip::address::from_string("0.0.0.0"), 40400);

    ip::tcp::acceptor acc(service, ep);

    // wait a client
    while(true) {
        // create new socket obj and put in reference
        socket_ptr sock(new ip::tcp::socket(service));
        // accept a connection for new client
        acc.accept(*sock);
        // create single thread for new client connection
        boost::thread(boost::bind(client_session, sock));
        std::cout << "Client accepted\n";
        
        boost::this_thread::sleep_for(boost::chrono::milliseconds(THREAD_TIMEOUT));
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
    char data[1024];
    
    while(true) {
        try {
            size_t len = sock->read_some(buffer(data));
            if (len > 0) {
                std::cout << std::string(data) << std::endl;
                write(*sock, buffer("ok", 2));
            }
        }
        catch (const std::exception& ex) {
            std::cout << ex.what() << std::endl;
            break;
        }
        boost::this_thread::sleep_for(boost::chrono::milliseconds(THREAD_TIMEOUT));
    }
}