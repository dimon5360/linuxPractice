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
#include "DDatabase.hpp"

/* Boost C++ headers */
#include <boost/format.hpp>

/* std C++ headers */
#include <iostream>

/**
 * @brief Data base class constructor
 */
DDatabase::DDatabase() {
#if DATA_BASE_CALLED_FUNCTION
    std::cout << __func__ << "()" << std::endl;
#endif /* DATA_BASE_CALLED_FUNCTION */

    std::cout << "Object of DDatabase class created." << std::endl;

    boost::thread(boost::bind(&DDatabase::handle, this));
}

/**
 * @brief Data base class destructor
 */
DDatabase::~DDatabase() {
#if DATA_BASE_CALLED_FUNCTION
    std::cout << __func__ << "()" << std::endl;
#endif /* DATA_BASE_CALLED_FUNCTION */
    
    std::cout << "Object of DDatabase class removed." << std::endl;    
}

/** 
 * @brief Data base main handler 
 * @note Function calls in single thread
 */
void DDatabase::handle() {
// #if DATA_BASE_CALLED_FUNCTION
    std::cout << __func__ << "()" << std::endl;
// #endif /* DATA_BASE_CALLED_FUNCTION */
    while(true) {
        std::cout << "." << std::endl;
        boost::this_thread::sleep_for(boost::chrono::milliseconds(THREAD_TIMEOUT));
    }
}