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
#include <iostream>
#include <string>

class JJsonHandler {

public:
    JJsonHandler();
    ~JJsonHandler() { std::cout << "JJsonHandler class removed." << std::endl; };

private:
    void PrintJson(const std::string &json);
};