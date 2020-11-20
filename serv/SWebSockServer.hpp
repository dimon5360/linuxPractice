/**
 *  @file   SWebSockServer.hpp
 *  @brief  Declarations of Web socket server Class
 *
 *  @author Kalmykov Dmitry
 *
 *  @version 0.2
 *  @date   20.11.2020
 */

#pragma once

/* C++ local headers */
#include "SService.hpp"

class SWebSockServer final : SService {
    
public:

    SWebSockServer(std::string);
    ~SWebSockServer();
};