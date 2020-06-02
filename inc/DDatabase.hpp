/*********************
 * @file SService.hpp
 * @brief Parent class header for other classes based on it.
 * 
 * @author kalmykov Dmitry
 * 
 * @version 0.0.1 
 * @date 01.06.2020
 */

#pragma once

#include "SService.hpp"

class DDatabase: SService {

public:
    /* data base class constructor */
    DDatabase();
    /* data base class destructor */
    ~DDatabase();
};