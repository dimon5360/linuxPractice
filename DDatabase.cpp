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
#if TCP_SERVER_CALLED_FUNCTION
    std::cout << __func__ << "()" << std::endl;
#endif /* TCP_SERVER_CALLED_FUNCTION */

    std::cout << "Object of DDatabase class created." << std::endl;
}

/**
 * @brief Data base class destructor
 */
DDatabase::~DDatabase() {
#if TCP_SERVER_CALLED_FUNCTION
    std::cout << __func__ << "()" << std::endl;
#endif /* TCP_SERVER_CALLED_FUNCTION */
    
    std::cout << "Object of DDatabase class removed." << std::endl;
    
}