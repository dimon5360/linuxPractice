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
#include "config.h"
#include "SService.hpp"

/* std C++ lib headers */
#include <thread>
#include <queue>
#include <string> 

#include <boost/thread/mutex.hpp>

class DDataProcessor final :  SService {

private:

    boost::mutex _mtx;

    std::queue<std::string> inQueueRequest;
    std::queue<std::string> outQueueResponse;
 
    /* data processor main handler */
    void handle();

    /* private interfaces for work with queue ------------------------------ */
    /* Push the output data to queue */
    void pushOutQueue(const std::string &&) /* override */;    
    /* Get input data from queue */
    std::string pullInQueue(void) override;
    /* Check that input data queue is empty */
    bool isInQueueEmpty(void) override;  
    
public:

    /* data base class constructor */
    DDataProcessor();
    /* data base class destructor */
    ~DDataProcessor();

    /* public interfaces for work with queue ------------------------------- */
    /* Push the input data to queue */
    void pushInQueue(const std::string &&) /* override */;
    /* Get output data from queue */
    std::string pullOutQueue(void) override;
    /* Check that output data queue is empty */
    bool isOutQueueEmpty(void) override;

};