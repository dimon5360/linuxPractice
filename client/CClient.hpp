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

/* C++ local headers */
#include "DDataProcessor.hpp"

/* C++ std lib headers */
#include <cstdint>
#include <iostream>
#include <string_view>
#include <string>

/* C++ boost lib headers */
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/thread/mutex.hpp>

using tcp = boost::asio::ip::tcp;
namespace websocket = boost::beast::websocket;  // from <boost/beast/websocket.hpp>

class CClient final : SService {
    
public:
    /* constructor */
    CClient(const uint32_t &cliendId, tcp::socket&&ws);
    /* destructor */
    ~CClient() {
        std::cout << "Client with ID #" << id << " removed.\n";
    }

    const uint32_t GetUserId() noexcept {
        return id;
    } 

private:
    uint32_t id = 0;
    websocket::stream<tcp::socket> ws;

    /*************************************************************
     *  @brief      Client connection handler
     *  @param[in]  Reference to data processor class object
     */
    void handle(std::unique_ptr<DDataProcessor> &&);

    /*************************************************************
    *  @brief      Processor for input JSON request from client
    * 
    *  @param[in]  req Input JSON request in string
    *  @return     Client request structure (alias cliReq)
    */
    const std::string &PrepareResponse() noexcept;

    /*************************************************************
     *  @brief      Processor for input JSON request from client
     * 
     *  @param[in]  req Input JSON request in string
     *  @return     Client request structure (alias cliReq)
     */
    void ProcessRequest(std::string &&) noexcept;

};