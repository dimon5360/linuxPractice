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
#include <queue>

class DDatabase final : SService {

private:

    boost::mutex _mtx;
    boost::thread _th;

    std::queue<std::string> inQueueRequest;
    std::queue<std::string> outQueueResponse;

    /* data base main handler */
    void handle();

    /* private interfaces for work with queue ------------------------------ */
    /* Push the output data to queue */
    void pushOutQueue(const std::string &) override;
    /* Get input data from queue */
    std::string pullInQueue(void) override;
    /* Check that input data queue is empty */
    bool isInQueueEmpty(void) override;  

public:

    /* data base class constructor */
    DDatabase();
    /* data base class destructor */
    ~DDatabase();

    /* public interfaces for work with queue ------------------------------- */
    /* Push the input data to queue */
    void pushInQueue(const std::string &) override;
    /* Get output data from queue */
    std::string pullOutQueue(void) override;
    /* Check that output data queue is empty */
    bool isOutQueueEmpty(void) override;
};