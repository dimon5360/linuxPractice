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


/* Public methods implementaions ------------------------------------------- */
/**
 *  @brief  Data base class constructor
 */
DDatabase::DDatabase() {
#if DATA_BASE_CALLED_FUNCTION
    std::cout << __func__ << "()" << std::endl;
#endif /* DATA_BASE_CALLED_FUNCTION */

    /* start thread for main handler */
    _th = boost::thread(boost::bind(&DDatabase::handle, this));
    _th.detach();
}

/**
 *  @brief  Data base class destructor
 */
DDatabase::~DDatabase() {
#if DATA_BASE_CALLED_FUNCTION
    std::cout << __func__ << "()" << std::endl;
#endif /* DATA_BASE_CALLED_FUNCTION */  
    // TODO: also need to check, does queue need clear?
    _th.~thread();
}

/** 
 *  @brief  Data base main handler 
 *  @note   Function calls in single thread
 */
void DDatabase::handle() {
#if DATA_BASE_CALLED_FUNCTION
    std::cout << __func__ << "()" << std::endl;
#endif /* DATA_BASE_CALLED_FUNCTION */
    while(true) {

        if(!isInQueueEmpty()) {

#if DATA_PROC_DEBUG_INFO
            std::cout << "Queue has a request." << std::endl;
#endif /* DATA_PROC_DEBUG_INFO */

            std::string req = pullInQueue();   
            std::reverse(req.begin(), req.end());         
            pushOutQueue(req);
        }
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

    /* lock mutex for pushing data */
    try {
        boost::lock_guard<boost::mutex> lock(_mtx);
    } catch(std::exception ex) {
        std::cout << ex.what() << std::endl;
    }
    outQueueResponse.push(resp);
}

/***
 *  @brief  Push the input data to queue
 */
void DDatabase::pushInQueue(const std::string & req) {
#if DATA_BASE_DEBUG_INFO
    std::cout << "Request to queue: " << req << std::endl; 
#endif /* DATA_BASE_DEBUG_INFO */

    /* lock mutex for pushing data */
    try {
        boost::lock_guard<boost::mutex> lock(_mtx);
    } catch(std::exception ex) {
        std::cout << ex.what() << std::endl;
    }
    inQueueRequest.push(req);
}

/***
 *  @brief  Get output data from queue
 */
std::string DDatabase::pullOutQueue(void) {
    /* lock mutex for pushing data */
    try {
        boost::lock_guard<boost::mutex> lock(_mtx);
    } catch(std::exception ex) {
        std::cout << ex.what() << std::endl;
    }

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
    /* lock mutex for pushing data */
    try {
        boost::lock_guard<boost::mutex> lock(_mtx);
    } catch(std::exception ex) {
        std::cout << ex.what() << std::endl;
    }
    
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