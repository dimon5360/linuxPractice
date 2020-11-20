/**
 *  @file SWebSockServer.cpp
 *  @brief  Definitions of Web socket server Class
 *
 *  @author Kalmykov Dmitry
 *
 *  @version 0.2
 *  @date   20.11.2020
 */

/* C++ local headers */
#include "main.h"
#include "config.h"
#include "SWebSockServer.hpp"
#include "CClient.hpp"

/* C++ boost lib headers */
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/ip/tcp.hpp>

/* C++ std lib headers */
#include <cstdlib>
#include <algorithm>
#include <functional>
#include <string>
#include <unordered_map>
#include <memory>

using tcp = boost::asio::ip::tcp;               // from <boost/asio/ip/tcp.hpp>
namespace websocket = boost::beast::websocket;  // from <boost/beast/websocket.hpp>

#define DEFAULT_USER_ID     10

std::map<const uint32_t, const std::unique_ptr<CClient>> userPull;

// Echoes back all received WebSocket messages
void do_session(tcp::socket& socket, const uint32_t clientId)
{
    userPull.emplace(std::pair(clientId, std::make_unique<CClient>(clientId, std::move(socket))));
}

/**
 * @brief SWebSockServer class constructor
 */
SWebSockServer::SWebSockServer(std::string s_port) {


    std::cout << "Object of SWebSockServer class created." << std::endl;

    uint32_t user_id = DEFAULT_USER_ID;    

    try {

        auto addr = "0.0.0.0";
        auto const address = boost::asio::ip::make_address("0.0.0.0");
        auto const port = static_cast<unsigned short>(std::atoi(s_port.c_str()));

        std::cout << "Start listening " << addr << ":" << s_port << std::endl;

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
                std::move(socket), user_id)}.detach();
            user_id++;
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;    
    }        
}

/**
 * @brief SWebSockServer class destructor
 */
SWebSockServer::~SWebSockServer() {
    std::cout << "Object of SWebSockServer class removed." << std::endl;
    
}
