/**
 *  @file   SWebSockServer.hpp
 *  @brief  Declarations of Web socket server Class
 *
 *  @author Kalmykov Dmitry
 *
 *  @version 0.1
 *  @date   09.08.2020
 */

#pragma once

/* local headers */
#include "SService.hpp"

/* boost c++ lib heades */
#include <boost/thread/mutex.hpp>

class SWebSockServer final : SService {
    
private:

    boost::mutex _mtx;
    boost::thread _th;

    std::queue<std::string> inQueueRequest;
    std::queue<std::string> outQueueResponse;

public:

    SWebSockServer();
    ~SWebSockServer();

    /* interfaces for work with queue -------------------------------------- */
    /* Push the output data to queue */
    void pushOutQueue(const std::string &) override;
    /* Get input data from queue */
    std::string pullInQueue(void) override;
    /* Check that input data queue is empty */
    bool isInQueueEmpty(void) override;  
    /* Push the input data to queue */
    void pushInQueue(const std::string &) override;
    /* Get output data from queue */
    std::string pullOutQueue(void) override;
    /* Check that output data queue is empty */
    bool isOutQueueEmpty(void) override;
};