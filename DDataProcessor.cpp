/*********************
 * @file DDataprocessor.hpp
 * @brief Derived from SService class for data processing.
 *
 *  @author Kalmykov Dmitry
 *
 *  @version 0.1
 *  @date 30.05.2020
 */

/* local headers */
#include "main.h"
#include "config.h"
#include "DDataProcessor.hpp"

/* boost c++ lib heades */
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>

/* Static private funtions declarations ------------------------------------ */

/* Reverse string for test output of data */
static void RevString(std::string &origString);


/* Class methods implementaions -------------------------------------------- */

/**
 * @brief SServer class constructor
 */
DDataProcessor::DDataProcessor() {
    /* start thread for main handler */
    _th = boost::thread(boost::bind(&DDataProcessor::handle, this));
    _th.detach();
}

/**
 * @brief SServer class destructor
 */
DDataProcessor::~DDataProcessor() {
    // TODO: also need to check, does queue need clear?
    _th.~thread();
}

/*** 
 *  @brief  Main data processor class handler
 */
void DDataProcessor::handle() {
    while(true) {

        if(!isInQueueEmpty()) {
            std::string req = pullInQueue();   
            RevString(req);         
            pushOutQueue(req);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(THREAD_TIMEOUT));
    }
}

/***
 *  @brief  Push the output data to queue
 */
void DDataProcessor::pushOutQueue(const std::string & resp) {
    
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
void DDataProcessor::pushInQueue(const std::string & req) {

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
std::string DDataProcessor::pullOutQueue(void) {

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
    }
    return resp;
}

/***
 *  @brief  Get input data from queue
 */
std::string DDataProcessor::pullInQueue(void) {

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
    }
    return req;
}

/*** 
 *  @brief  Check that input data queue is empty 
 */
bool DDataProcessor::isInQueueEmpty(void) {
    return inQueueRequest.empty();
}

/*** 
 *  @brief  Check that output data queue is empty 
 */
bool DDataProcessor::isOutQueueEmpty(void) {
    return outQueueResponse.empty();
}

/* Static private functions implementations -------------------------------- */

/*** 
 *  @brief  Reverse string for test output of data
 */
static void RevString(std::string &origString) {
    std::reverse(origString.begin(), origString.end());
}