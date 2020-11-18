/**
 *  @file SWebSockServer.cpp
 *  @brief  Definitions of Web socket server Class
 *
 *  @author Kalmykov Dmitry
 *
 *  @version 0.1
 *  @date 09.08.2020
 */

/* local headers */
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
    // try
    // {
        // Construct the stream by moving in the socket
        // websocket::stream<tcp::socket> ws{std::move(socket)};
        userPull.emplace(std::pair(clientId, std::make_unique<CClient>(clientId, std::move(socket))));

        // Accept the websocket handshake
        // ws.accept();
        // std::cout << "New Client with ID #" << clientId << " accepted\n";

        // for(;;)
        // {
        //     // This buffer will hold the incoming message
        //     boost::beast::multi_buffer buffer;

        //     // Read a message
        //     ws.read(buffer);

        //     if(ws.got_text()) {
        //         // Echo the message back
        //         ws.text(ws.got_text());
        //         std::string str = buffers_to_string(buffer.data()); 
        //         std::transform(str.begin(), str.end(), str.begin(), ::tolower);
                
        //         std::cout << "Client msg: \"" << str << "\"\n";
        //         ws.write(boost::asio::buffer(str));
        //     }
        // }
    // }
    // catch(boost::system::system_error const& se)
    // {
    //     // This indicates that the session was closed
    //     if(se.code() != websocket::error::closed) {
    //         std::cerr << "Error 1: " << se.code().message() << std::endl;
    //     }
    // }
    // catch(std::exception const& e)
    // {
    //     std::cerr << "Error 2: " << e.what() << std::endl;
    // }
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
                std::move(socket), user_id++)}.detach();
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


/***
 *  @brief  Push the output data to queue
 */
void SWebSockServer::pushOutQueue(const std::string & resp) {
    /* lock mutex for pushing data */
    try {
        boost::lock_guard<boost::mutex> lock(_mtx);
    } catch(std::exception ex) {
        std::cout << ex.what() << std::endl;
    }
    outQueueResponse.push(resp);
}

/***
 *  @brief  Push the input data to queue
 */
void SWebSockServer::pushInQueue(const std::string & req) {    
    /* lock mutex for pushing data */
    try {
        boost::lock_guard<boost::mutex> lock(_mtx);
    } catch(std::exception ex) {
        std::cout << ex.what() << std::endl;
    }
    inQueueRequest.push(req);
}

/***
 *  @brief  Get output data from queue
 */
std::string SWebSockServer::pullOutQueue(void) {

    /* lock mutex for pushing data */
    try {
        boost::lock_guard<boost::mutex> lock(_mtx);
    } catch(std::exception ex) {
        std::cout << ex.what() << std::endl;
    }
    std::string resp;

    if(!isOutQueueEmpty()) {
        resp = outQueueResponse.front();
        outQueueResponse.pop();
    }
    return resp;
}

/***
 *  @brief  Get input data from queue
 */
std::string SWebSockServer::pullInQueue(void) {

    /* lock mutex for pushing data */
    try {
        boost::lock_guard<boost::mutex> lock(_mtx);
    } catch(std::exception ex) {
        std::cout << ex.what() << std::endl;
    }

    std::string req;

    if(!isInQueueEmpty()) {
        req = inQueueRequest.front();
        inQueueRequest.pop();
    }
    return req;
}

/*** 
 *  @brief  Check that input data queue is empty 
 */
bool SWebSockServer::isInQueueEmpty(void) {
    return inQueueRequest.empty();
}

/*** 
 *  @brief  Check that output data queue is empty 
 */
bool SWebSockServer::isOutQueueEmpty(void) {
    return outQueueResponse.empty();
}
