/*********************
 * @file jjson_parser.hpp
 * @brief Class JSON parser declaration
 * 
 * @author kalmykov Dmitry
 * 
 * @version 0.0.1 
 * @date 18.11.2020
 */

#pragma once

/* std C++ lib */
#include <string>

using cliReq = struct ClientRequest  {
    std::string request_type;
    std::string request_data; 
};


class JJsonHandler {



};