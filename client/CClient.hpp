/*********************
 * @file CClient.hpp
 * @brief Class CClient reclaration
 * 
 * @author kalmykov Dmitry
 * 
 * @version 0.0.1 
 * @date 12.06.2020
 */

#pragma once

/* std C++ lib */
#include <cstdint>
#include <iostream>
#include <string>

/* C++ boost lib headers */
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/ip/tcp.hpp>

using tcp = boost::asio::ip::tcp;
namespace websocket = boost::beast::websocket;  // from <boost/beast/websocket.hpp>

class CClient {
    
public:
    CClient(const uint32_t &cliendId, tcp::socket&&ws);
    ~CClient() {
        std::cout << "Client with ID #" << id << " removed.\n";
    }

    const uint32_t GetUserId() noexcept {
        return id;
    } 

private:
    uint32_t id = 0;
    websocket::stream<tcp::socket> ws;
    std::string input_buffer_;

    void WaitConnection();




};