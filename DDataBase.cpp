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
#include "DDataBase.hpp"

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

    /* TODO: code below commented to test async realization 
     of data base class instead multithread */

    // thread for handling io woth db
    boost::thread(boost::bind(&DDatabase::handle, this));
}

/**
 * @brief Data base class destructor
 */
DDatabase::~DDatabase() {
#if DATA_BASE_CALLED_FUNCTION
    std::cout << __func__ << "()" << std::endl;
#endif /* DATA_BASE_CALLED_FUNCTION */  
}

/** 
 * @brief Data base main handler 
 * @note Function calls in single thread
 */
void DDatabase::handle() {
#if DATA_BASE_CALLED_FUNCTION
    std::cout << __func__ << "()" << std::endl;
#endif /* DATA_BASE_CALLED_FUNCTION */
    while(true) {
        std::cout << "." << std::endl;
        boost::this_thread::sleep_for(boost::chrono::milliseconds(THREAD_TIMEOUT));
    }
}

/***
 *  @brief  Push the output data to queue 
 */
void DDatabase::pushOutQueue(const std::string & resp) {
#if DATA_BASE_DEBUG_INFO
    std::cout << "Response to queue: " << resp << std::endl; 
#endif /* DATA_BASE_DEBUG_INFO */

    outQueueResponse.push(resp);
}

/***
 *  @brief  Push the input data to queue
 */
void DDatabase::pushInQueue(const std::string & req) {
#if DATA_BASE_DEBUG_INFO
    std::cout << "Request to queue: " << req << std::endl; 
#endif /* DATA_BASE_DEBUG_INFO */

    inQueueRequest.push(req);
}

/***
 *  @brief  Get output data from queue
 */
std::string DDatabase::pullOutQueue(void) {
    std::string resp;
    if(!isOutQueueEmpty()) {
        resp = outQueueResponse.front();
        outQueueResponse.pop();

#if DATA_BASE_DEBUG_INFO
        std::cout << "Response from queue: " << resp << std::endl; 
#endif /* DATA_BASE_DEBUG_INFO */
    }
    return resp;
}

/***
 *  @brief  Get input data from queue
 */
std::string DDatabase::pullInQueue(void) { 
    std::string req;
    if(!isInQueueEmpty()) {
        req = inQueueRequest.front();
        inQueueRequest.pop();

#if DATA_BASE_DEBUG_INFO
        std::cout << "Request from queue: " << req << std::endl; 
#endif /* DATA_BASE_DEBUG_INFO */
    }
    return req;
}

/***
 *  @brief  Check that input data queue is empty
 */
bool DDatabase::isInQueueEmpty(void) {
    return inQueueRequest.empty();
}

/***
 *  @brief  Check that output data queue is empty
 */
bool DDatabase::isOutQueueEmpty(void) {
    return outQueueResponse.empty();
}