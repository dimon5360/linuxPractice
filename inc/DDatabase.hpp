/*********************
 * @file DDatabase.hpp
 * @brief Derived from SService class for data base exchange.
 * 
 * @author kalmykov Dmitry
 * 
 * @version 0.0.1 
 * @date 01.06.2020
 */

#pragma once

/* local headers */
#include "SService.hpp"

/* std C++ headers */
#include <thread>

class DDatabase: SService {
private:
    std::thread mainDatabasethread;

public:
    /* data base class constructor */
    DDatabase();
    /* data base class destructor */
    ~DDatabase();
    /* data base main handler */
    void handle();
};