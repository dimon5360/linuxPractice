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
#include "DDataProcessor.hpp"

#include <thread>

/**
 * @brief SServer class constructor
 */
DDataProcessor::DDataProcessor() {
    std::cout << "Data processor constructor " << std::endl;

    // boost::thread(boost::bind(&DDataProcessor::handle, this));
    std::thread t(&DDataProcessor::handle, this);
    t.detach();
}

/**
 * @brief SServer class destructor
 */
DDataProcessor::~DDataProcessor() {
    std::cout << "Data processor destructor " << std::endl;
    
}

/* Push the output data to queue */
void DDataProcessor::pushOutQueue(std::string resp) {
    std::cout << "Response to queue: " << resp << std::endl; 
    outQueueResponse.push(resp);
}

/* Push the input data to queue */
void DDataProcessor::pushInQueue(std::string req) {
    std::cout << "Request to queue: " << req << std::endl; 
    inQueueRequest.push(req);
}

/* Get output data from queue */
std::string DDataProcessor::pullOutQueue(void) {
    std::string resp;
    if(!isOutQueueEmpty()) {
        resp = outQueueResponse.front();
        outQueueResponse.pop();
        std::cout << "Response from queue: " << resp << std::endl; 
    }
    return resp;
}

/* Get input data from queue */
std::string DDataProcessor::pullInQueue(void) {
    std::string req;
    if(!isInQueueEmpty()) {
        req = inQueueRequest.front();
        inQueueRequest.pop();
        std::cout << "Request from queue: " << req << std::endl; 
    }
    return req;
}

/* Check that input data queue is empty */
bool DDataProcessor::isInQueueEmpty(void) {
    return inQueueRequest.empty();
}

/* Check that output data queue is empty */
bool DDataProcessor::isOutQueueEmpty(void) {
    return outQueueResponse.empty();
}


std::string RevString(std::string origString);

void DDataProcessor::handle() {

    while(true) {
        std::cout << "data proc ." << std::endl;
        if(!isInQueueEmpty()) {
            std::cout << "Queue has a request." << std::endl;
            std::string req = pullInQueue();
            req = "gfedcba";
            pushOutQueue(req);
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(THREAD_TIMEOUT));
    }
}

std::string RevString(std::string origString) {
    std::string revString;

    size_t size_ = origString.length();
    for(size_t i = size_ - 1; i >= 0; i--) {
        revString += origString[i];
    }
    return revString;
}