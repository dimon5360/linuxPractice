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

#include <queue>
#include <string>
#include <iostream>

/* basic class for microservices */
class SService
{
public:

    /* interfaces for work with queue -------------------------------------- */
    /* Push the output data to queue */
    virtual void pushOutQueue(const std::string&) { /* ... */ };
    /* Push the input data to queue */
    virtual void pushInQueue(const std::string&) { /* ... */ };
    /* Get output data from queue */
    virtual std::string pullOutQueue(void) { /* ... */ };
    /* Get input data from queue */
    virtual std::string pullInQueue(void) { /* ... */ };
    /* Check that input data queue is empty */
    virtual bool isInQueueEmpty(void) { /* ... */ };
    /* Check that output data queue is empty */
    virtual bool isOutQueueEmpty(void) { /* ... */ };
};


