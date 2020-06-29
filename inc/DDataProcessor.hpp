/*********************
 * @file DDataprocessor.hpp
 * @brief Derived from SService class for data processing.
 * 
 * @author kalmykov Dmitry
 * 
 * @version 0.0.1 
 * @date 29.06.2020
 */

#pragma once

/* local headers */
#include "SService.hpp"

/* boost c++ lib heades */
#include <boost/thread.hpp>

/* std C++ lib headers */
#include <thread>
#include <queue>
#include <string> 

class DDataProcessor: SService {
private:

    std::queue<std::string> inQueueRequest;
    std::queue<std::string> outQueueResponse;
 
    /* data processor main handler */
    void handle();

    /* private interfaces for work with queue ------------------------------ */
    /* Get input data from queue */
    std::string pullInQueue(void);
    /* Push the output data to queue */
    void pushOutQueue(std::string);
    /* Check that input data queue is empty */
    bool isInQueueEmpty(void);  

public:

    /* data base class constructor */
    DDataProcessor();
    /* data base class destructor */
    ~DDataProcessor();

    /* public interfaces for work with queue ------------------------------- */
    /* Push the input data to queue */
    void pushInQueue(std::string);
    /* Get output data from queue */
    std::string pullOutQueue(void);
    /* Check that output data queue is empty */
    bool isOutQueueEmpty(void);
};