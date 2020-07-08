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

/* Push the output data to queue */
void DDatabase::pushOutQueue(const std::string & resp) {
    std::cout << "Response to queue: " << resp << std::endl; 
    outQueueResponse.push(resp);
}

/* Push the input data to queue */
void DDatabase::pushInQueue(const std::string & req) {
    std::cout << "Request to queue: " << req << std::endl; 
    inQueueRequest.push(req);
}

/* Get output data from queue */
std::string DDatabase::pullOutQueue(void) {
    std::string resp;
    if(!isOutQueueEmpty()) {
        resp = outQueueResponse.front();
        outQueueResponse.pop();
        std::cout << "Response from queue: " << resp << std::endl; 
    }
    return resp;
}

/* Get input data from queue */
std::string DDatabase::pullInQueue(void) {
    std::string req;
    if(!isInQueueEmpty()) {
        req = inQueueRequest.front();
        inQueueRequest.pop();
        std::cout << "Request from queue: " << req << std::endl; 
    }
    return req;
}

/* Check that input data queue is empty */
bool DDatabase::isInQueueEmpty(void) {
    return inQueueRequest.empty();
}

/* Check that output data queue is empty */
bool DDatabase::isOutQueueEmpty(void) {
    return outQueueResponse.empty();
}